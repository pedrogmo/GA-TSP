#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "population.h"

#define N_GENERATIONS 100u

static const struct element *fittest(const struct element *);
static void print_generation(const struct element *);

int main(int argc, char **argv)
{
  struct element population[POPULATION_SIZE] = {};
  const struct element *best = NULL;
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
  update_fit_prob(population);

  /* Termination condition: N generations */
  for(gen = 1u; gen <= N_GENERATIONS; ++gen)
  {
    reproduce_rws(population);
    update_fit_prob(population);

    /*printf("-------- Gen %zu --------\n", gen);
    print_generation(population);
    putchar('\n');*/
  }

  best = fittest(population);
  printf("Solution:\t%s\t%lf\t%lf%%\n", best->tour, best->fitness, best->probability * 100.0);

  return EXIT_SUCCESS;
}

const struct element *fittest(const struct element *population)
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

void print_generation(const struct element *population)
{
  const struct element  *end = population + POPULATION_SIZE,
                        *best = fittest(population);

  for(; population < end; ++population)
  {
    printf("%s\t%lf\t%lf%%", population->tour, population->fitness, population->probability * 100.0);
    if (best == population)
      puts(" (Fittest)");
    else
      putchar('\n');
  }
}
