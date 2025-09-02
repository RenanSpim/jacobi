#include "../include/jacobi_sequencial.h"
#include <stdio.h>
#include <stdlib.h>
//#define tamanho N
#define tamanho 10

void lendo(double **A, double *B) {
  FILE *file = fopen("../assets/gemini10.dat", "r");

  for(int i=0;i<tamanho;i++) {
    for(int j=0;j<tamanho;j++) {
      fscanf(file, "%lf", &A[i][j]);
    }
  }
  int i=0;
  while(!feof(file)) {
    fscanf(file, "%lf", &B[i]);
    i++;
  }
}

void jacobi(double **A, double *B, double p) {
  double x0[tamanho] = {0};
  double x[tamanho] = {0};
  double erro = 0.1, erro_atual = -1, erro_max=0;
  struct timespec inicio, fim;
  
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  while(erro > p) {
    for(int i=0;i<tamanho;i++) {
      double aux=0;

      for(int j=0;j<tamanho;j++) {
        if(i==j) continue;
        //printf("\n%.4lf", A[i][j]);
        aux += A[i][j] * x0[j];
      }
      x[i] = (B[i] - aux)/A[i][i];
      erro_atual = fabs(x[i] - x0[i]);
      
      if(erro_atual > erro_max)
        erro = erro_atual;
    }
  
    for(int i=0;i<tamanho;i++) {
      //printf("\nx0=%.4lf -> x=%.4lf", x0[i], x[i]);
      x0[i] = x[i];
    }
  }
  clock_gettime(CLOCK_MONOTONIC, &fim);
  double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
  printf("\nTempo de execução: %f segundos\n", tempo);

  printf("Vetor de resultados: \n");
  for(int i=0;i<tamanho;i++)
    printf("\t[%f]", x0[i]);
}

int main(){
  double **A = (double **)malloc(tamanho * sizeof(double *));
  double *B = (double *)malloc(tamanho * sizeof(double));

  for(int i=0;i<tamanho;i++)
    A[i] = (double *)malloc(tamanho*sizeof(double));
  
  lendo(A, B);
  jacobi(A, B, CRITERIO_PARADA);
  return 0;
}
