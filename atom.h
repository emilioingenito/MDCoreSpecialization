#include "types.h"

typedef struct {
    int natoms;
    int nlocal, nghost;
    int nmax;

    MMD_float* x;
    MMD_float* v;
    MMD_float* f;

    int ntypes;
    int* type;
}Atom;