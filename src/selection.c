#include <stdlib.h>
#include "selection.h"

const struct element *rws(const struct element *population)
{
  /* Random double from 0 to 1 */
  double random = (double) rand() / RAND_MAX;
  size_t i = 0u;

  while (random > 0.0)
  {
    random -= population[i++].probability;
  }
  --i;

  return population + i;
}

const struct element *sus(const struct element *population)
{
  return NULL;
}

const struct element *tournament(const struct element *population)
{
  return NULL;
}

const struct element *truncation(const struct element *population)
{
  return NULL;
}
