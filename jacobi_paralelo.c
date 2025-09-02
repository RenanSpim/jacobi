#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define N 2000
#define CRITERIO_PARADA 1e-5
#define MAX_ITER 10000

typedef enum {
    STATIC,
    DYNAMIC,
    GUIDED
} ScheduleType;

void lendo(double **A, double *B) {
  FILE *file = fopen("../assets/gemini10.dat", "r");

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
}

int jacobi_paralelo(double A[N][N], double *b, double *x, ScheduleType type, int chunk_size, int num_threads) {
    double *x_new = malloc(N * sizeof(double));
    int iterations = 0;
    double error = CRITERIO_PARADA + 1.0;
    struct timespec inicio, fim;

    omp_sched_t kind;
    switch (type)
    {
        case STATIC: kind = omp_sched_static; break;
        case GUIDED: kind = omp_sched_guided; break;
        case DYNAMIC: kind = omp_sched_dynamic; break;
        default: 
            printf("Digite um tipo correto\n");
            free(x_new); 
            return 0;
            break;
    }
    omp_set_num_threads(num_threads);
    omp_set_schedule(kind, chunk_size);

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    while (iterations++ < MAX_ITER && error > CRITERIO_PARADA) {
        error = 0.0;
        #pragma omp parallel for schedule(runtime) reduction(max:error)
        for (int i = 0; i < N; i++) {
            double sigma = 0.0;

            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                sigma += A[i][j] * x[j];
            }
            x_new[i] = (b[i] - sigma) / A[i][i];
            double local_error = fabs(x_new[i] - x[i]);
            error = local_error > error ? local_error : error;
        }
        
        for (int i = 0; i < N; i++) {
            x[i] = x_new[i];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    printf("Tempo de execução: %f segundos\n", tempo);

    FILE *file = fopen("resultado_paralelo.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        free(x_new); 
        return 0; 
    }

    fprintf(file, "Resultado final do vetor x:\n");
    for (int i = 0; i < N; i++) {
        fprintf(file, "x[%d] = %f\n", i, x[i]);
    }

    fclose(file);
    free(x_new);
    return 1;
}

int main() {
  double **A = (double **)malloc(N * sizeof(double *));
  double *B = (double *)malloc(N * sizeof(double));
  double *x = (double *)malloc(N * sizeof(double));

  for(int i=0;i<N;i++)
    A[i] = (double *)malloc(N*sizeof(double));

  lendo(A, B);
  jacobi_paralelo(A, B, x, STATIC, 1, 4);
  return 0;
}
