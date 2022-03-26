#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "selection.h"
#include "crossover.h"

static unsigned int DISTANCES[N_CITIES][N_CITIES] =
{
  {0},
  {94, 0},
  {76, 156, 0},
  {141, 231, 80, 0},
  {91, 64, 167, 229, 0},
  {60, 93, 133, 185, 49, 0},
  {120, 108, 142, 201, 163, 165, 0},
  {145, 68, 216, 96, 112, 71, 103, 0},
  {91, 37, 137, 216, 96, 112, 71, 103, 0},
  {74, 150, 114, 139, 114, 65, 194, 179, 160, 0},
  {90, 130, 154, 192, 76, 39, 203, 139, 151, 54, 0},
  {55, 57, 100, 178, 93, 91, 74, 123, 39, 127, 129, 0},
  {145, 223, 141, 113, 200, 151, 254, 265, 236, 86, 133, 199, 0},
  {108, 26, 161, 239, 91, 117, 90, 83, 25, 171, 155, 61, 251, 0},
  {41, 62, 116, 182, 51, 39, 127, 104, 75, 89, 78, 53, 171, 83, 0},
  {49, 140, 37, 92, 139, 99, 136, 194, 130, 77, 117, 91, 118, 151, 90, 0},
  {33, 61, 100, 171, 72, 61, 104, 116, 61, 99, 99, 30, 176, 75, 24, 80, 0},
  {151, 229, 169, 155, 185, 129, 269, 250, 239, 80, 11, 206, 46, 251, 168, 139, 179, 0},
  {69, 120, 49, 128, 148, 128, 75, 186, 95, 134, 159, 63, 182, 119, 99, 65, 76, 202, 0},
  {111, 57, 185, 251, 26, 75, 163, 39, 93, 140, 101, 101, 226, 81, 69, 159, 86, 211, 161, 0},
  {24, 109, 84, 137, 92, 49, 144, 152, 112, 50, 71, 78, 125, 127, 49, 50, 52, 128, 90, 115, 0},
};

static double fitness_fn(const struct element *);
static void shuffle(char *);
static void initialise(struct element *);
static struct element *fittest(struct element *);

int main(int argc, char **argv)
{
  struct element  population[POPULATION_SIZE]= {0},
                  *best = NULL;
  size_t i = 0u, j = 0u, gen = 0u;

  /* Mirror matrix of distances */
  for(i = 0u; i < N_CITIES; ++i)
  {
    for(j = i + 1; j < N_CITIES; ++j)
    {
      DISTANCES[i][j] = DISTANCES[j][i];
    }
  }

  srand((unsigned) time(NULL));
  initialise(population);

  /* Termination condition: 100 generations */
  for(gen = 0u; gen < 100u; ++gen)
  {

  }

  return EXIT_SUCCESS;
}

void initialise(struct element *population)
{
  size_t i = 0u;

  for(i = 0u; i < POPULATION_SIZE; ++i)
  {
    int city = 0;

    population[i].tour[N_CITIES - 1] = '\0';

    /* Fill with "ABCDEF..." */
    for(city = 0; city < N_CITIES - 1; ++city)
    {
      population[i].tour[city] = 'A' + city;
    }

    shuffle(population[i].tour);

    population[i].fitness = fitness_fn(&population[i]);
  }
}

double fitness_fn(const struct element *solution)
{
  unsigned int total_distance = 0u;
  size_t  i = 0u,
          from = 0u,
          to = 0u;

  for(i = 0u; i < N_CITIES - 1; ++i)
  {
    size_t to = solution->tour[i] - 'A' + 1u;
    total_distance += DISTANCES[from][to];
    from = to;
  }

  total_distance += DISTANCES[from][0];

  return 1.0 / total_distance;
}

struct element *fittest(struct element *population)
{
  size_t i = 1u;
  size_t best = 0u;

  for(i = 1u; i < POPULATION_SIZE; ++i)
  {
    if (population[i].fitness > population[best].fitness)
      best = i;
  }

  return population + best;
}

void shuffle(char *str)
{
  size_t  i = 0u,
          random = 0u,
          length = strlen(str);

  char temp = '\0';

  for (i = length - 1u; i > 0u; --i)
  {
      random = rand() % (i + 1u);
      temp = str[random];
      str[random] = str[i];
      str[i] = temp;
  }
}
