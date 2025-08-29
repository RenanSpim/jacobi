#include "jacobi_sequencial.h"

void jacobi(double **A, double b[], double p) {
  double x0[N] = {0};
  double x[N] = {0};
  double erro = 0.1, erro_atual = -1, erro_max=0;
  struct timespec inicio, fim;
  
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  while(erro > p) {
    for(int i=0;i<N;i++) {
      double aux=0;

      for(int j=0;j<N;j++) {
        if(i==j) continue;
        aux += A[i][j] * x0[j];
      }
      x[i] = (b[i] - aux)/A[i][i];
      erro_atual = fabs(x[i] - x0[i]);
      
      if(erro_atual > erro_max)
        erro = erro_atual;
    }
    
    for(int i=0;i<N;i++)
      x0[i] = x[i];
  }
  clock_gettime(CLOCK_MONOTONIC, &fim);
  double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
  printf("\nTempo de execução: %f segundos\n", tempo);

  printf("Vetor de resultados: \n");
  for(int i=0;i<N;i++)
    printf("\t[%f]", x0[i]);
}
