#include <stdio.h>
#include "jacobi_paralelo.h"
#include "jacobi_sequencial.h"

int main(){
    double A[N][N], b[N], x[N];
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    //fread(A, sizeof(double), N*N, fp);
    //fread(b, sizeof(double), N, fp);
    
    for (int i = 0; i < N; i++) {
        x[i] = 0.0;
    }
    fclose(fp);
    return 0;
  //size é o tamanho da matriz quadrada
  //está definido aqui como constante somente para testes
  //int size = 3;
  //double **A, b[size];

  //A =  (double **)malloc(size * sizeof(double*));

  //for(int i=0;i<size;i++) {
  //      A[i] = (double *)malloc(size * sizeof(double));
  //  }
 
  //return 0;
}
