#ifndef SELECTION_H
#define SELECTION_H

#include "population.h"

#define K_SUS 2
#define K_TRUNC 50

extern struct element *rws(struct element *population);
extern struct element *sus(struct element *population);
extern struct element *tournament(struct element *population);
extern struct element *truncation(struct element *population);

#endif /* SELECTION_H */
