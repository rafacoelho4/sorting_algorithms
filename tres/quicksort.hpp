#ifndef QUICKSORT
#define QUICKSORT

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cfloat>
#include <time.h>
#include "../tipo.hpp"
#include "../color.hpp"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

using namespace std;

#define TAMANHO 20

typedef struct{
    FILE* leitura_inferior;
    FILE* leitura_superior;
    FILE* escrita_inferior;
    FILE* escrita_superior;
}Arquivo;

typedef struct{
    unsigned long long int leitura;
    unsigned long long int escrita;
    unsigned long long int comparacoes;
    double tempo;
}Metrica;

typedef Item Area;
Metrica inicializa_metrica();
void imprimindo_resultados( Metrica m );
void quick_sort_main(bool parametro, int quantidade);
void quick_sort_externo(Metrica* m, Arquivo* arquivo, int esquerda, int direita);
void particao(Metrica* m, Arquivo* arquivo, Area* area, int esquerda, int direita, int* i, int* j);
void ler_limite_inferior(unsigned long long int* leitura, FILE* arquivo, Item* ultimo_lido, int* li, bool* lido);
void ler_limite_superior(unsigned long long int* leitura, FILE* arquivo, Item* ultimo_lido, int* ls, bool* lido);
void escreve_max(unsigned long long int* escrita, FILE** arquivo, Item aux, int* es);
void escreve_min(unsigned long long int* escrita, FILE** arquivo, Item aux, int* ei);
void inserir_area(Area* area, Item* ultimo_lido, int* tamanho_area);
void retira_max(Area* area, Item* aux, int* tamanho_area);
void retira_min(Area* area, Item* aux, int* tamanho_area);
void ler_arquivo_texto(FILE* arquivo);
void inicializando_ponteiros(Arquivo* arquivo);
void retira_ultimo(Area* area, Item* ultimo);
void retira_primeiro(Area* area, Item* primeiro);
void quick_sort(Area* area, int esquerda, int direita);

#endif