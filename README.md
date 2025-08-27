# Projeto: Método de Jacobi - Sequencial vs. Paralelo com OpenMP

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Parallelism](https://img.shields.io/badge/Paralelismo-OpenMP-orange.svg)
![Status](https://img.shields.io/badge/Status-Pendente-red.svg)

Este projeto consiste na implementação de duas versões do método iterativo de Jacobi para resolver sistemas de equações lineares: uma versão **sequencial** e uma versão **paralela** utilizando OpenMP. O objetivo principal é analisar e comparar o desempenho das duas abordagens.

## Índice

- [Sobre o Problema](#1-sobre-o-problema)
- [Como Compilar e Executar](#2-como-compilar-e-executar)

---

## 1. Sobre o Problema

O método de Jacobi é um algoritmo iterativo usado para encontrar soluções aproximadas de um sistema de equações lineares $Ax = b$. A fórmula de iteração para cada variável $x_i$ é:

$$x_i^{(k+1)} = \frac{1}{a_{ii}} \left( b_i - \sum_{j \neq i} a_{ij} x_j^{(k)} \right)$$

Onde $k$ representa a iteração atual. O processo continua até que a diferença máxima entre os vetores de solução de duas iterações consecutivas seja menor que uma tolerância definida. Neste projeto, a tolerância é $10^{-5}$ e o sistema tem **2000 equações**.

Para garantir a convergência, a matriz de coeficientes $A$ gerada é **diagonalmente dominante**.

## 2. Como Compilar e Executar

Para compilar e executar os programas, utilize os seguintes comandos no seu terminal.

### Compilação

```bash

# Versão sequencial
gcc -o sequencial jacobi_sequencial.c -lm
./sequencial

# Versão paralela
gcc -fopenmp -o paralela jacobi_paraleol.c -lm
./paralela (número de threads) (schedule) (chunk)
