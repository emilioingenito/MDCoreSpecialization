typedef struct {
    int natoms;
    int nlocal, nghost;
    int nmax;

    double* x;
    double* v;
    double* f;

    int ntypes;
    int* type;
}Atom;