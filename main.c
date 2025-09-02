#include <stdio.h>
#include "jacobi_paralelo.h"
#include "jacobi_sequencial.h"

int main(){
    double A[N][N], b[N], x[N];
    FILE *fp;
    fp = fopen("input.dat", "rb");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    // Verificar se leu corretamente
    size_t elementos_lidos_A = fread(A, sizeof(double), N*N, fp);
    if (elementos_lidos_A != N*N) {
        fprintf(stderr, "Erro: esperava %d elementos da matriz, leu %zu\n", N*N, elementos_lidos_A);
        fclose(fp);
        return 1;
    }
    
    size_t elementos_lidos_b = fread(b, sizeof(double), N, fp);
    if (elementos_lidos_b != N) {
        fprintf(stderr, "Erro: esperava %d elementos do vetor, leu %zu\n", N, elementos_lidos_b);
        fclose(fp);
        return 1;
    }
    
    printf("Matriz %dx%d e vetor de %d elementos carregados com sucesso!\n", N, N, N);
    
    for (int i = 0; i < N; i++) {
        x[i] = 0.0;
    }
    
    fclose(fp);
    return 0;
}
