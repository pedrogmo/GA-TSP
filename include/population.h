#ifndef POPULATION_H
#define POPULATION_H

#define POPULATION_SIZE 500
#define N_CITIES 21
#define MUTATION_RATE 0.02

struct element
{
  char tour[N_CITIES];
  double fitness;
  double probability;
};

extern unsigned int DISTANCES[N_CITIES][N_CITIES];

extern double fitness_fn(const struct element *);
extern void initialise(struct element *);
extern void reproduce_rws(struct element *);
extern void reproduce_truncation(struct element *);
extern void update_fit_prob(struct element *);

#endif /* POPULATION_H */
