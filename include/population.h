#ifndef POPULATION_H
#define POPULATION_H

#define POPULATION_SIZE 1000
#define N_CITIES 21
#define MUTATION_RATE 0.01

struct element
{
  char tour[N_CITIES];
  double fitness;
};

#endif /* POPULATION_H */
