#ifndef SELECTION_H
#define SELECTION_H

#include "population.h"

#define K_SUS 2
#define K_TRUNC 50

extern const struct element *rws(const struct element *population);
extern const struct element *sus(const struct element *population);
extern const struct element *tournament(const struct element *population);
extern const struct element *truncation(const struct element *population);

#endif /* SELECTION_H */
