# Projeto: Método de Jacobi - Sequencial vs. Paralelo com OpenMP

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Parallelism](https://img.shields.io/badge/Paralelismo-OpenMP-orange.svg)
![Status](https://img.shields.io/badge/Status-Concluído-green.svg)

Este projeto implementa duas versões do método iterativo de Jacobi para resolver sistemas de equações lineares: uma versão **sequencial** e uma versão **paralela** utilizando OpenMP. O objetivo é analisar e comparar o desempenho das duas abordagens em sistemas de diferentes tamanhos.

## Índice

- [Sobre o Problema](#1-sobre-o-problema)
- [Estrutura do Projeto](#2-estrutura-do-projeto)
- [Como Compilar e Executar](#3-como-compilar-e-executar)
- [Arquivos de Dados](#4-arquivos-de-dados)
- [Resultados](#5-resultados)

---

## 1. Sobre o Problema

O método de Jacobi é um algoritmo iterativo usado para encontrar soluções aproximadas de um sistema de equações lineares $Ax = b$. A fórmula de iteração para cada variável $x_i$ é:

$$x_i^{(k+1)} = \frac{1}{a_{ii}} \left( b_i - \sum_{j \neq i} a_{ij} x_j^{(k)} \right)$$

Onde $k$ representa a iteração atual. O processo continua até que a diferença máxima entre os vetores de solução de duas iterações consecutivas seja menor que uma tolerância definida ($10^{-5}$).

Para garantir a convergência, as matrizes de coeficientes utilizadas são **diagonalmente dominantes**.

## 2. Estrutura do Projeto

O projeto contém os seguintes arquivos:

### Arquivos de Código
- `jacobi_sequencial.c` - Implementação sequencial do método de Jacobi para sistemas 10x10
- `jacobi_paralelo.c` - Implementação paralela com OpenMP para sistemas 2000x2000

### Arquivos de Dados
- `gemini10.dat` - Sistema de 10 equações (matriz 10x10 + vetor b)
- `linear10.dat` - Sistema alternativo de 10 equações
- `linear2000.dat` - Sistema de 2000 equações (matriz 2000x2000 + vetor b)

### Características da Versão Paralela
- Suporte a diferentes políticas de escalonamento OpenMP:
  - `STATIC` - Distribuição estática das iterações
  - `DYNAMIC` - Distribuição dinâmica das iterações  
  - `GUIDED` - Distribuição guiada das iterações
- Configuração de número de threads
- Configuração de tamanho do chunk para escalonamento

## 3. Como Compilar e Executar

### Pré-requisitos
- Compilador GCC com suporte a OpenMP
- Sistema operacional Linux/Unix

### Compilação e Execução

#### Versão Sequencial
```bash
# Compilar
gcc -o jacobi_sequencial jacobi_sequencial.c -lm

# Executar
./jacobi_sequencial
```

#### Versão Paralela
```bash
# Compilar
gcc -o jacobi_paralelo jacobi_paralelo.c -lm -fopenmp

# Executar
./jacobi_paralelo
```

### Configuração da Versão Paralela

No arquivo `jacobi_paralelo.c`, você pode ajustar os parâmetros na função `main()`:

```c
jacobi_paralelo(A, B, x, STATIC, 1, 4);
//                    ^      ^  ^
//                    |      |  └─ Número de threads
//                    |      └─ Chunk size  
//                    └─ Política de escalonamento (STATIC, DYNAMIC, GUIDED)
```

## 4. Arquivos de Dados

### Formato dos Arquivos
Os arquivos de dados seguem o formato:
- Primeiras N linhas: elementos da matriz A (N×N)
- Última linha: elementos do vetor b (N×1)

### Tamanhos dos Sistemas
- **Sistema pequeno**: 10×10 (arquivos `gemini10.dat` e `linear10.dat`)
- **Sistema grande**: 2000×2000 (arquivo `linear2000.dat`)

**Nota**: A versão sequencial está configurada para sistemas 10×10, enquanto a versão paralela está otimizada para sistemas 2000×2000.

## 5. Resultados

### Arquivos de Saída
- `resultado_sequencial.txt` - Solução da versão sequencial
- `resultado_paralelo.txt` - Solução da versão paralela

### Métricas Coletadas
- **Tempo de execução**: Medido em segundos usando `clock_gettime()`
- **Número de iterações**: Limitado a 10.000 iterações máximas
- **Critério de parada**: Erro máximo menor que 10⁻⁵
- **Solução final**: Vetor x com os valores das variáveis

### Análise de Performance
A versão paralela permite comparar diferentes estratégias de paralelização:
- **Número de threads**: Impacto no speedup
- **Política de escalonamento**: Balanceamento de carga
- **Tamanho do chunk**: Granularidade da paralelização

---

## Tecnologias Utilizadas
- **Linguagem**: C
- **Paralelização**: OpenMP
- **Compilador**: GCC
- **Bibliotecas**: 
  - `math.h` - Funções matemáticas
  - `time.h` - Medição de tempo
  - `omp.h` - OpenMP

## Autor
Este projeto foi desenvolvido como parte dos estudos em programação concorrente e paralela.
