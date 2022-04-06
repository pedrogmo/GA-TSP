#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "crossover.h"

#define PMX_METHOD 1

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

#if PMX_METHOD == 1
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
#elif PXM_METHOD == 2
  for(i1 = 0u, i2 = 0u; i1 < length; ++i1)
  {
    char corresp = '\0';

    if (i1 >= from && i1 <= to)
    {
      i1 = to + 1;
      if (i1 >= length)
        break;
    }

    i2 = chrpos(p1, p2[i2]);
    do
    {
      corresp = p2[i2];
      i2 = chrpos(p1, corresp);
    }
    while(exists(f1, corresp));

    f1[i1] = corresp;
  }
#endif
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
  for(i1 = i2 = (to + 1) % length;
      i1 != from;
      i2 = (i2 + 1) % length)
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

/*
#define BUFSIZE 1024

int main(int argc, char **argv)
{
  char  offspring[BUFSIZE],
        *parent1 = NULL,
        *parent2 = NULL,
        *method = NULL;;

  size_t  l1 = 0u,
          l2 = 0u,
          i = 0u;

  if (argc != 4)
  {
    fprintf(stderr, "usage: %s parent1 parent2 method\n", argv[0]);
    return EXIT_FAILURE;
  }

  *offspring = '\0';
  parent1 = argv[1];
  parent2 = argv[2];
  method = argv[3];

  l1 = strlen(parent1);
  l2 = strlen(parent2);

  // Strings have different lengths
  if (l1 != l2)
  {
    fprintf(stderr, "Parents should have the same length\n");
    return EXIT_FAILURE;
  }

  // Length exceeded buffer size
  if (l1 >= BUFSIZE)
  {
    fprintf(stderr, "The parents' length should not be over %i\n", BUFSIZE);
    return EXIT_FAILURE;
  }

  // Convert arguments to upper case
  for(i = 0u; i < l1; ++i)
  {
    parent1[i] = toupper(parent1[i]);
    parent2[i] = toupper(parent2[i]);
    method[i] = toupper(method[i]);
  }

  srand((unsigned) time(NULL));

  if (strncmp(method, "PMX", 3) == 0)
  {
    pmx(parent1, parent2, offspring, l1);
  }
  else if (strncmp(method, "OX", 2) == 0)
  {
    ox(parent1, parent2, offspring, l1);
  }
  else if (strncmp(method, "CX", 2) == 0)
  {
    cx(parent1, parent2, offspring, l1);
  }

  printf("Offspring: %s\n", offspring);
}
*/
