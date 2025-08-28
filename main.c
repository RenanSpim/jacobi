#include <stdio.h>
#include <stdlib.h>
#include "jacobi_paralelo.h"
#include "jacobi_sequencial.h"

int main(){
  //size é o tamanho da matriz quadrada
  //está definido aqui como constante somente para testes
  int size = 3;
  double **A, b[size];

  A =  (double **)malloc(size * sizeof(double*));

  for(int i=0;i<size;i++) {
        A[i] = (double *)malloc(size * sizeof(double));
    }
 
  return 0;
}
