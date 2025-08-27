#include "jacobi_sequencial.h"

void *jacobi(double **A, double b[], double p) {
  double x0[N] = {0};
  double x[N] = {0};
  double erro = 0;

  while(erro > CRITERIO_PARADA) {
    for(int i=0;i<N;i++) {
      double aux=0;

      for(int j=0;j<N;j++) {
        if(i==j) continue;
        aux += A[i][j] * x0[j];
      }
      x[i] = (b[i] - aux)/A[i][i];
      erro = fabs(x[i] - x0[i]);
      
    }
  }
}
