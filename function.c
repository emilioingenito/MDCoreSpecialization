#include "function.h"
#include "atom.h"
#include "neighbor.h"

/*-----------------------FIRST FUNCTION------------------------------*/
/*-----------------------COMPUTE FORCES------------------------------*/
void compute_original(Atom atom, Neighbor neighbor, int me)
{
  //SETTING UP FORCES
  printf(" # Setting up force :\n");
  int cutforce = 2.5;
  int use_oldcompute = 0;
  int reneigh = 1;
  int ntypes = 4;
  MMD_float* cutforcesq = (MMD_float*) malloc(ntypes * ntypes * sizeof(MMD_float));
  MMD_float *epsilon = (MMD_float*) malloc(ntypes * ntypes * sizeof(MMD_float));
  MMD_float *sigma6 = (MMD_float*) malloc(ntypes * ntypes * sizeof(MMD_float));
  MMD_float *sigma = (MMD_float*) malloc(ntypes * ntypes * sizeof(MMD_float));

  for(int i = 0; i<ntypes*ntypes; i++) {
    cutforcesq[i] = 0.0;
    epsilon[i] = 1.0;
    sigma6[i] = 1.0;
    sigma[i] = 1.0;
  }

  MMD_float epsilon_f, sigma_f;
  epsilon_f=1.0;
  sigma_f=1.0;
  for(int i=0; i<ntypes*ntypes; i++) {
    epsilon[i] = epsilon_f;
    sigma[i] = sigma_f;
    sigma6[i] = sigma_f*sigma_f*sigma_f*sigma_f*sigma_f*sigma_f;
  }
  
  for(int i = 0; i<ntypes*ntypes; i++)
   cutforcesq[i] = cutforce * cutforce;
  
  printf("\t> epsilon: %f\n", epsilon_f);
  printf("\t> sigma: %f\n", sigma_f);
  printf("\t> cutforce: %f\n", cutforce);
  

  //Setting up the parameters of the function
  int nlocal = atom.nlocal;
  int nall = atom.nlocal + atom.nghost;
  MMD_float* x = atom.x;
  MMD_float* f = atom.f;
  int* type = atom.type;

  int eng_vdwl = 0;
  int virial = 0;
  
  // clear force on own and ghost atoms
  for(int i = 0; i < nall; i++) {
    f[i * PAD + 0] = 0.0;
    f[i * PAD + 1] = 0.0;
    f[i * PAD + 2] = 0.0;
  }
  
  // loop over all neighbors of my atoms
  // store force on both atoms i and j
  for(int i = 0; i < nlocal; i++) {
    const int* const neighs = &neighbor.neighbors[i * neighbor.maxneighs];
    const int numneigh = neighbor.numneigh[i];
    const MMD_float xtmp = x[i * PAD + 0];
    const MMD_float ytmp = x[i * PAD + 1];
    const MMD_float ztmp = x[i * PAD + 2];
    const int type_i = type[i];
    for(int k = 0; k < numneigh; k++) {
      const int j = neighs[k];
      const MMD_float delx = xtmp - x[j * PAD + 0];
      const MMD_float dely = ytmp - x[j * PAD + 1];
      const MMD_float delz = ztmp - x[j * PAD + 2];
      int type_j = type[j];
      const MMD_float rsq = delx * delx + dely * dely + delz * delz;
      const int type_ij = type_i*ntypes+type_j;
      if(rsq < cutforcesq[type_ij]) {
        const MMD_float sr2 = 1.0 / rsq;
        const MMD_float sr6 = sr2 * sr2 * sr2 * sigma6[type_ij];
        const MMD_float force = 48.0 * sr6 * (sr6 - 0.5) * sr2 * epsilon[type_ij];
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
  printf("\t>Eng_vdwl: %f\n", eng_vdwl);
  printf("\t>Virial: %f\n", virial);
  printf("\n---------------------------------------------------\n\n");

}