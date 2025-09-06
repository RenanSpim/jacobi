#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define N 10
#define CRITERIO_PARADA 1e-5
#define MAX_ITER 10000

void lendo(double **A, double *B) {
  FILE *file = fopen("gemini10.dat", "r");

  for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++) {
      fscanf(file, "%lf", &A[i][j]);
    }
  }
  int i=0;
  while(!feof(file)) {
    fscanf(file, "%lf", &B[i]);
    i++;
  }

  fclose(file);
}

void jacobi(double **A, double *B, double p) {
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
      x[i] = (B[i] - aux)/A[i][i];
      erro_atual = fabs(x[i] - x0[i]);
      
      if(erro_atual > erro_max)
        erro = erro_atual;
    }
  
    for(int i=0;i<N;i++) {
      x0[i] = x[i];
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &fim);
  double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
  printf("\nTempo de execução: %f segundos\n", tempo);

  FILE *file = fopen("resultado_sequencial.txt", "w");

  if (file == NULL) {
    printf("Erro ao abrir o arquivo para escrita!\n");
  }

  fprintf(file, "Resultado final do vetor x:\n");
  for (int i = 0; i < N; i++) {
    fprintf(file, "x[%d] = %f\n", i, x[i]);
  }

  fclose(file);
}

int main(){
  double **A = (double **)malloc(N * sizeof(double *));
  double *B = (double *)malloc(N * sizeof(double));

  for(int i=0;i<N;i++)
    A[i] = (double *)malloc(N*sizeof(double));
  
  lendo(A, B);
  jacobi(A, B, CRITERIO_PARADA);
  return 0;
}
