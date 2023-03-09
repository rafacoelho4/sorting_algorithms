#ifndef BLOCOSSELECAO_HPP
#define BLOCOSSELECAO_HPP

#include <iostream>
#include <climits>
#include <time.h>
#include "../balanceada.hpp"
#include "../color.hpp"

#define TAM 20

typedef struct {
    long int inscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
    bool marcado;
} Reg;

typedef struct { // Heap minímo -> primeiro elemento é o menor!
    Reg* itens; // Lista de elementos dentro do heap
    int tamanhoMax; // Tamanho máximo de elementos no heap
    int tamanho; // Tamanho atual de elementos no heap
} Heap;

void blocosSelecao(FILE *in, FILE *fin[], FILE *fout[], int n, bool P);
void gera_blocos(FILE** fitas, FILE* provao, int quant, int* comp, int* escrita, int* leitura);
FILE* formata_arquivo(FILE* provao, int n);

// Funções refentes ao heap
Heap cria_heap(int max);
Reg reg_minimo(Heap* heap);
void inserir_heap(Heap* heap, Reg reg, int* compare);
void troca(Reg *x, Reg *y);
int nodo_pai(int i);
int nodo_esquerda(int i);
int nodo_direita(int i);
Reg remove_minimo(Heap* heap, int* compare);
void transforma_heap(Heap* heap, int i, int* compare);
void deleta_heap(Heap* heap);
void desmarca_heap(Heap* heap);

#endif