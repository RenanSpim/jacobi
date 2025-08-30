#include "../include/parser.h"

void read_file(const char *filename, double A[N][N], double B[N]){
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                perror("Erro ao ler o double");
                fclose(file);
                return;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(file, "%lf", &B[i]) != 1) {
            perror("Erro ao ler o double");
            fclose(file);
            return;
        }
    }

    fclose(file);
}

