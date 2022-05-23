#include "types.h"
#include "print.h"
/*-----------------------CORE FUNCTION------------------------------*/
/*-----------------------COMPUTE FORCES------------------------------*/
void compute_original(Atom atom, Neighbor neighbor, int me)
{
  //SETTING UP FORCES
  printf(" # Setting up force :\n");
  double cutforce = 2.5;
  int use_oldcompute = 0;
  int reneigh = 1;
  int ntypes = 4;
  double* cutforcesq = (double*) malloc(ntypes * ntypes * sizeof(double));
  double *epsilon = (double*) malloc(ntypes * ntypes * sizeof(double));
  double *sigma6 = (double*) malloc(ntypes * ntypes * sizeof(double));
  double *sigma = (double*) malloc(ntypes * ntypes * sizeof(double));

  for(int i = 0; i<ntypes*ntypes; i++) {
    cutforcesq[i] = 0.0;
    epsilon[i] = 1.0;
    sigma6[i] = 1.0;
    sigma[i] = 1.0;
  }

  double epsilon_f, sigma_f;
  epsilon_f=1.0;
  sigma_f=1.0;
  for(int i=0; i<ntypes*ntypes; i++) {
    epsilon[i] = epsilon_f;
    sigma[i] = sigma_f;
    sigma6[i] = sigma_f*sigma_f*sigma_f*sigma_f*sigma_f*sigma_f;
  }
  
  for(int i = 0; i<ntypes*ntypes; i++)
   cutforcesq[i] = cutforce * cutforce;
  
  printf("\t> epsilon: "); print_float(epsilon_f); printf("\n");
  printf("\t> sigma: "); print_float(sigma_f); printf("\n");
  printf("\t> cutforce: "); print_float(cutforce); printf("\n");
  

  //Setting up the parameters of the function
  int nlocal = atom.nlocal;
  int nall = atom.nlocal + atom.nghost;
  double* x = atom.x;
  double* f = atom.f;
  int* type = atom.type;

  double eng_vdwl = 0;
  double virial = 0;
  
  // clear force on own and ghost atoms
  for(int i = 0; i < nall; i++) {
    f[i * PAD + 0] = 0.0;
    f[i * PAD + 1] = 0.0;
    f[i * PAD + 2] = 0.0;
  }
  
  // loop over all neighbors of my atoms
  // store force on both atoms i and j
  for(int i = 0; i < nlocal; i++) {
    asm volatile("main_loop:\n");
    const int* const neighs = &neighbor.neighbors[i * neighbor.maxneighs];
    const int numneigh = neighbor.numneigh[i];
    const double xtmp = x[i * PAD + 0];
    const double ytmp = x[i * PAD + 1];
    const double ztmp = x[i * PAD + 2];
    const int type_i = type[i];
    for(int k = 0; k < numneigh; k++) {
      asm volatile("inner_loop:\n");
      const int j = neighs[k];
      const double delx = xtmp - x[j * PAD + 0];
      const double dely = ytmp - x[j * PAD + 1];
      const double delz = ztmp - x[j * PAD + 2];
      int type_j = type[j];
      const double rsq = delx * delx + dely * dely + delz * delz;
      const int type_ij = type_i*ntypes+type_j;
      if(rsq < cutforcesq[type_ij]) {
        const double sr2 = 1.0 / rsq;
        const double sr6 = sr2 * sr2 * sr2 * sigma6[type_ij];
        const double force = 48.0 * sr6 * (sr6 - 0.5) * sr2 * epsilon[type_ij];
        f[i * PAD + 0] += delx * force;
        f[i * PAD + 1] += dely * force;
        f[i * PAD + 2] += delz * force;
        f[j * PAD + 0] -= delx * force;
        f[j * PAD + 1] -= dely * force;
        f[j * PAD + 2] -= delz * force;

        //if(ENVFLAG) check was omitted here
        eng_vdwl += (4.0 * sr6 * (sr6 - 1.0)) * epsilon[type_ij];
        virial += (delx * delx + dely * dely + delz * delz) * force;
      }
    }
  }

  printf(" # End of computation\n");
  printf("\t>Eng_vdwl: "); print_float(eng_vdwl); printf("\n");
  printf("\t>Virial: "); print_float(virial); printf("\n");
  printf("\n---------------------------------------------------\n\n");

}