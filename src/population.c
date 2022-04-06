#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "selection.h"
#include "crossover.h"

unsigned int DISTANCES[N_CITIES][N_CITIES] =
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

static int sort_probability(const void *a, const void *b)
{
  const struct element  *e1 = (const struct element *) a,
                        *e2 = (const struct element *) b;

  if (e1->probability > e2->probability)
    return 1;

  else if (e1->probability < e2->probability)
    return -1;

  return 0;
}

static void shuffle_string(char *str)
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

static void shuffle_elements(struct element *elements, size_t length)
{
  size_t  i = 0u,
          random = 0u;

  struct element temp;

  for (i = length - 1u; i > 0u; --i)
  {
      random = rand() % (i + 1u);
      temp = elements[random];
      elements[random] = elements[i];
      elements[i] = temp;
  }
}

static void mutate(struct element* child)
{
  /* Mutation: random swap */
  double random = (double) rand() / RAND_MAX;
  if (random <= MUTATION_RATE)
  {
    int i1 = rand() % (N_CITIES - 1),
        i2 = rand() % (N_CITIES - 1);
    char temp = '\0';

    temp = child->tour[i1];
    child->tour[i1] = child->tour[i2];
    child->tour[i2] = temp;
  }
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

    shuffle_string(population[i].tour);
  }
}

void reproduce_rws(struct element *population)
{
  size_t i = 0u;
  struct element  *p1 = NULL,
                  *p2 = NULL,
                  old_generation[POPULATION_SIZE];

  /* Sort population by fitness */
  qsort(population, POPULATION_SIZE, sizeof(*population), &sort_probability);

  /* Make a copy of population */
  memcpy(old_generation, population, POPULATION_SIZE * sizeof(*population));

  for (i = 0u; i < POPULATION_SIZE; ++i)
  {
    /* Select two parents using RWS */
    p1 = rws(old_generation);
    do
    {
      p2 = rws(old_generation);
    }
    while(p2 == p1);

    /* Crossover two parents making one child */
    pmx(p1->tour, p2->tour, population[i].tour, N_CITIES - 1);

    mutate(population + i);
  }
}

void reproduce_truncation(struct element *population)
{
  size_t i = 0u;
  struct element mating_pool[K_TRUNC];
  bool completed = false;

  /* Sort population by fitness */
  qsort(population, POPULATION_SIZE, sizeof(*population), &sort_probability);

  /* Put T% elements in the mating pool */
  memcpy(mating_pool, population, K_TRUNC * sizeof(*population));

  while(!completed)
  {
    size_t imate = 0u;

    shuffle_elements(mating_pool, K_TRUNC);

    for (imate = 0u; !completed && imate < K_TRUNC; imate += 2u)
    {
      /* Select two parents from mating pool */
      struct element  *p1 = mating_pool + imate,
                      *p2 = mating_pool + imate + 1u,
                      *f1 = population + i;

      /* Crossover two parents making one child */
      pmx(p1->tour, p2->tour, f1->tour, N_CITIES - 1u);

      mutate(f1);

      /* If last element, completed */
      if (i >= POPULATION_SIZE - 1u)
        completed = true;
      else
        ++i;
    }
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
    to = solution->tour[i] - 'A' + 1u;
    total_distance += DISTANCES[from][to];
    from = to;
  }

  total_distance += DISTANCES[from][0u];

  return 1.0 / total_distance;
}

void update_fit_prob(struct element *population)
{
  size_t i = 0u;
  double total_fitness = 0.0;

  for(i = 0u; i < POPULATION_SIZE; ++i)
  {
    population[i].fitness = fitness_fn(population + i);
    total_fitness += population[i].fitness;
  }

  for(i = 0u; i < POPULATION_SIZE; ++i)
  {
    population[i].probability = population[i].fitness / total_fitness;
  }
}
