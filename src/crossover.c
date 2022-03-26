#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "crossover.h"

#define MAX(X, Y) ((X) > (Y)) ? (X) : (Y)
#define MIN(X, Y) ((X) < (Y)) ? (X) : (Y)

static bool exists(const char *str, char target)
{
  const char *result = strchr(str, target);
  return result;
}

static size_t chrpos(const char *str, char target)
{
  const char *result = strchr(str, target);
  assert(result);
  return result - str;
}

void pmx(const char *p1, const char *p2, char *f1, size_t length)
{
  size_t  rand1 = rand() % length,
          rand2 = rand() % length,
          from = MIN(rand1, rand2),
          to = MAX(rand1, rand2),
          i = 0u,
          i1 = 0u,
          i2 = 0u;

  memset(f1, '*', length);
  f1[length] = '\0';

  /* Copy random sequence from P1 to C */
  for(i = from; i <= to; ++i)
  {
    f1[i] = p1[i];
  }

  /* Map elements between P1 and P2 */
  for(i1 = 0u, i2 = 0u; i2 < length; ++i2)
  {
    /* Do not map inside range; skip */
    if (i1 >= from && i1 <= to)
      i1 = to + 1;

    /* If element from P2 does not already exits, add it at index i1 */
    if (!exists(f1, p2[i2]))
    {
      f1[i1] = p2[i2];
      ++i1;
    }
  }
}

void ox(const char *p1, const char *p2, char *f1, size_t length)
{
  size_t  rand1 = rand() % length,
          rand2 = rand() % length,
          from = MIN(rand1, rand2),
          to = MAX(rand1, rand2),
          i = 0u,
          i1 = 0u,
          i2 = 0u;

  memset(f1, '*', length);
  f1[length] = '\0';

  /* Copy random sequence from P1 to C */
  for(i = from; i <= to; ++i)
  {
    f1[i] = p1[i];
  }

  /* Copy remaining elements from P2 in the order they appear */
  for(i1 = i2 = to + 1; i1 != from; i2 = (i2 + 1) % length)
  {
    /* Add new element from P2 if does not already exist */
    if (!exists(f1, p2[i2]))
    {
      f1[i1] = p2[i2];
      i1 = (i1 + 1) % length;
    }
  }
}

void cx(const char *p1, const char *p2, char *f1, size_t length)
{
  size_t i = 0u;

  memset(f1, '*', length);
  f1[length] = '\0';

  /* Copy from elements from P2 where they appear in P1 */
  while(f1[i] == '*')
  {
    f1[i] = p1[i];
    i = chrpos(p1, p2[i]);
  }

  /* Copy the remaining elements from P2 */
  for(i = 0u; i < length; ++i)
  {
    if (f1[i] == '*')
      f1[i] = p2[i];
  }
}
