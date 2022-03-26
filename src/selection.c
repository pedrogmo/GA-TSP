#include <stdlib.h>
#include "selection.h"

struct element *rws(struct element *population)
{
  /* Random double from 0 to 1 */
  double random = (double) rand() / RAND_MAX;
  size_t i = 0u;

  while (random > 0)
  {
    random -= population[i++].probability;
  }
  --i;

  return population + i;
}

struct element *sus(struct element *population)
{
  return NULL;
}

struct element *tournament(struct element *population)
{
  return NULL;
}

struct element *truncation(struct element *population)
{
  return NULL;
}
