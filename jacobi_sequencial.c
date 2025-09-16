#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define N 2000
#define CRITERIO_PARADA 1e-5
#define MAX_ITER 10000

/*
void lendo(double **A, double *B) {
  FILE *file = fopen("sistlinear-dificil.dat", "r");

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
}*/

//VERSAO ATUALIZADA
// A função agora aceita o nome do arquivo como um parâmetro
void lendo(double **A, double *B, const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");

    // VERIFICAÇÃO DE SEGURANÇA: Checa se o arquivo foi aberto com sucesso.
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de entrada"); // perror imprime uma mensagem de erro detalhada
        exit(1); // Aborta o programa para evitar um crash
    }

    // Leitura da matriz A (seu laço aqui estava correto)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            // Adicionamos uma verificação aqui também por segurança
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Erro: arquivo de dados incompleto ou mal formatado na matriz.\n");
                exit(1);
            }
        }
    }
    
    // LEITURA CORRETA E SEGURA: Usa um laço for para ler exatamente N elementos.
    for (int i = 0; i < N; i++) {
        // Verifica se a leitura foi bem-sucedida
        if (fscanf(file, "%lf", &B[i]) != 1) {
            fprintf(stderr, "Erro: arquivo de dados incompleto ou mal formatado no vetor B.\n");
            exit(1);
        }
    }

    fclose(file);
}



/*
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
}*/


//VERSAO ATUALIZADA JACOBI
void jacobi(double **A, double *B, double p) {
    // --- PARTE 1: DECLARAÇÕES QUE ESTAVAM FALTANDO ---
    // Aloca x0 e x na heap para evitar stack overflow
    double *x0 = (double *)calloc(N, sizeof(double)); // calloc já inicializa com 0
    double *x  = (double *)malloc(N * sizeof(double));

    // Variáveis para o cálculo do erro
    double erro, erro_atual;
    int iteracoes = 0;

    // Variáveis para medir o tempo
    struct timespec inicio, fim;

    // --- PARTE 2: LÓGICA DE EXECUÇÃO CORRIGIDA ---
    clock_gettime(CLOCK_MONOTONIC, &inicio); // Inicia a contagem de tempo
    
    do {
        erro = 0.0; // Zera o erro máximo a cada nova iteração
        for (int i = 0; i < N; i++) {
            double aux = 0;
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                aux += A[i][j] * x0[j];
            }
            x[i] = (B[i] - aux) / A[i][i];
            erro_atual = fabs(x[i] - x0[i]);
            if (erro_atual > erro) {
                erro = erro_atual; // Encontra o maior erro desta iteração
            }
        }

        // Atualiza x0 para a próxima iteração
        for (int i = 0; i < N; i++) {
            x0[i] = x[i];
        }

        iteracoes++;
        // Opcional: imprimir o erro para depuração
        printf("Iteração %d, Erro: %f\n", iteracoes, erro);

    } while (erro > p && iteracoes < MAX_ITER);

    clock_gettime(CLOCK_MONOTONIC, &fim); // Finaliza a contagem de tempo
    
    // Calcula o tempo de execução
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    printf("\nConvergência alcançada em %d iterações.\n", iteracoes);
    printf("Tempo de execução: %f segundos\n", tempo);

    // --- PARTE 3: ESCRITA DO RESULTADO E LIMPEZA ---
    FILE *file = fopen("resultado_sequencial.txt", "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
    } else {
        fprintf(file, "Resultado final do vetor x:\n");
        for (int i = 0; i < N; i++) {
            fprintf(file, "x[%d] = %.4f\n", i, x[i]); // Adicionado .4 para 4 casas decimais
        }
        fclose(file);
    }

    // Libera a memória alocada DENTRO desta função
    free(x0);
    free(x);
}

int main(){
  double **A = (double **)malloc(N * sizeof(double *));
  double *B = (double *)malloc(N * sizeof(double));

  for(int i=0;i<N;i++)
    A[i] = (double *)malloc(N*sizeof(double));
  
  lendo(A, B, "sistlinear2k.dat");
  jacobi(A, B, CRITERIO_PARADA);

  // Libera a memória alocada
  for(int i=0; i < N; i++) {
    free(A[i]); // Libera cada linha da matriz
  }
  free(A); // Libera o ponteiro para as linhas
  free(B); // Libera o vetor B

  return 0;

}
