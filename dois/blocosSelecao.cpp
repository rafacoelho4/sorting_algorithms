#include "blocosSelecao.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Função responsável pela criação dos blocos por substituição por seleção.
// in = PROVAO.txt | fin = fitas de entrada | fout = fitas de saída
void blocosSelecao(FILE *in, FILE *fin[], FILE *fout[], int n, bool P){
    int leitura = 0, escrita = 0, comp = 0;
    double tempo;
    clock_t inicio = clock();
    Reg reg;

    // Dividindo os alunos em blocos e inserindo nas fitas
    FILE* aux = formata_arquivo(in, n);
    rewind(aux);
    gera_blocos(fin, aux, n, &comp, &escrita, &leitura); // TODO: manda fin ou fout?
    fimBloco(fin);

    printf("\n\n");

    tempo = ((double) (clock() - inicio))/CLOCKS_PER_SEC;

    cout<<color::rize( "                       RESULTADOS GERACAO DOS BLOCOS - SELECAO POR SUBSTITUIÇÃO                     ", "Black" , "Light Cyan" )<<endl;
    printf(ANSI_COLOR_BLUE "\nCOMPARACOES: \t\t\t\t %d" ANSI_COLOR_RESET, comp);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE LEITURA: \t\t %d" ANSI_COLOR_RESET, leitura);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE ESCRITA: \t\t %d" ANSI_COLOR_RESET, escrita);
    printf(ANSI_COLOR_BLUE "\nTEMPO TOTAL: \t\t\t\t %lf segundos" ANSI_COLOR_RESET, tempo);
    printf("\n"); 

    fclose(in);
    fclose(aux);
}

FILE* formata_arquivo(FILE* provao, int n){
    Item leitura;
    FILE* aux;
    if((aux = fopen("../auxiliar.txt", "w+")) == NULL){
        printf("Arquivo auxiliar não pode ser aberto :(");
    }
    for(int i = 0; i < n; i++) {
        fscanf(provao, "%ld %lf %[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
            &leitura.inscricao, &leitura.nota, leitura.estado, leitura.cidade, leitura.curso);
        fprintf(aux, "%ld %2lf %s %s %s\n", leitura.inscricao, leitura.nota, leitura.estado, leitura.cidade, leitura.curso);
    }

    return aux;
}

// Função que divide os alunos em blocos
void gera_blocos(FILE** fitas, FILE* provao, int quant, int* comp, int* escrita, int* leitura){
    bool primeira_vez = true;
    Heap heap = cria_heap(TAM);
    size_t checaEscrita;
    int fita = 0;
    bool termino = true;

    while(termino){
        Reg reg;
        Reg anterior;
        //fflush(provao);
        // Inserção na fila de prioridades (heap)
        if(!feof(provao)){
            if(!primeira_vez){
                checaEscrita = fscanf(provao,"%ld %lf %s %50[A-Z a-z] %30[A-Z a-z] \n", &reg.inscricao, &reg.nota,
            reg.estado, reg.cidade, reg.curso);
                
                reg.marcado = false;
                *leitura += 1;

                if(reg.nota < anterior.nota){
                    reg.marcado = true;
                }

                if(checaEscrita != 0){ 
                    inserir_heap(&heap, reg, comp);
                }

            } 
            else{ // Inserindo os primeiros 20 elementos
                int x = (quant < 20) ? quant : TAM;
                for(int i = 0; i < x; i++){
                    *leitura += 1;
                    checaEscrita = fscanf(provao,"%ld %lf %s %50[A-Z a-z] %30[A-Z a-z] \n", &reg.inscricao, &reg.nota,
            reg.estado, reg.cidade, reg.curso);
                    if(checaEscrita != 0){
                        reg.marcado = false;
                        inserir_heap(&heap, reg, comp);
                    }
                }
                primeira_vez = false;
            }
        }

        // Olha se primeiro item da fila está marcado 
        if(heap.itens[0].marcado){
            desmarca_heap(&heap); // Desmarca os outros itens da fila
            anterior = remove_minimo(&heap, comp); // Retira o primeiro item

            // Separação dos blocos
            fprintf(fitas[fita], "\n");
            separacaoBloco(fitas[fita]);
            fita++; // Próximo bloco será inserido na próxima fita

        } 
        else{
            anterior = remove_minimo(&heap, comp);
        }

        // Se chegou na última fita, volta para primeira
        if(fita == FITAS){ // TODO: == TAMANHO - 1 (19) OU FITAS - 1 (9)? 
            fita = 0;

            // Separação dos blocos
            fprintf(fitas[fita], "\n");
            separacaoBloco(fitas[fita]);
        }

        fprintf(fitas[fita], "%li %.2lf %s %s %s\n", anterior.inscricao, anterior.nota, anterior.estado, anterior.cidade, anterior.curso);
        //printf("\n%li %.1lf %s %s %s", anterior.inscricao, anterior.nota, anterior.estado, anterior.cidade, anterior.curso);

        *escrita += 1;

        // Fila vazia, todos os blocos estão nas fitas
        if(heap.tamanho == 0){
            termino = false;
        }
    }

    fclose(provao);
    deleta_heap(&heap);
}

// Função que cria o heap
Heap cria_heap(int max){
    Heap heap;

    heap.tamanho = 0;
    heap.tamanhoMax = max;
    heap.itens = (Reg*) calloc(max, sizeof(Reg));

    return heap;
}

// Função que retorna o menor elemento do heap (sem retirá-lo do heap em si)
Reg reg_minimo(Heap* heap){
    return heap->itens[0];
}

// Função que retorna o nodo pai
int nodo_pai(int i){
    return ((i - 1) / 2);
}

// Função que retorna o nodo filho à esquerda
int nodo_esquerda(int i){
    return ((2 * i) + 1);
}

// Função que retorna o nodo filho à direita
int nodo_direita(int i){
    return ((2 * i) + 2);
}

// Função que insere um elemento no heap
void inserir_heap(Heap* heap, Reg reg, int* comp){
    if (heap->tamanho == heap->tamanhoMax) {
        printf("Heap lotado! Impossível inserir o item\n");
        return;
    }

    // Inserindo o novo item no final do heap
    heap->tamanho++;
    int i = heap->tamanho - 1;
    heap->itens[i] = reg;

    // Confere se a propriedade* do heap está ok e resolve se não estiver
    // *Menor elemento é o primeiro no heap
    *comp += 1;
    while (i != 0 && heap->itens[nodo_pai(i)].nota > heap->itens[i].nota) {
        *comp += 1;
        troca(&heap->itens[i], &heap->itens[nodo_pai(i)]);
        i = nodo_pai(i);
   }
}

// Função que troca um item com outro
void troca(Reg *x, Reg *y){
    Reg aux = *x;
    *x = *y;
    *y = aux;
}

// Função que salva o valor de minimo em um auxiliar, remove o elemento do heap e depois retorna o auxiliar
Reg remove_minimo(Heap* heap, int* comp){
    if(heap->tamanho == 0){
        return heap->itens[0];
    }

    Reg aux = heap->itens[0];
    heap->itens[0] = heap->itens[heap->tamanho - 1];
    heap->tamanho--;

    transforma_heap(heap, 0, comp);

    return aux;
}

// Função que transforma uma subárvore em heap. Ou seja, rearranja o heap de modo a manter a propriedade
// Vai transformando/conferindo recursivamente as subárvores
void transforma_heap (Heap* heap, int i, int* comp){
    int l = nodo_esquerda(i);
    int r = nodo_direita(i);
    int menor = i; // A raiz/nó pai é i

    *comp += 1;
    // Olha se o menor elemento está no filho da esquerda ou da direita
    if (l < heap->tamanho && heap->itens[l].nota < heap->itens[i].nota)
        menor = l;

    *comp += 1;
    if (r < heap->tamanho && heap->itens[r].nota < heap->itens[menor].nota)
        menor = r;

    *comp += 1;
    if (menor != i) {
        troca(&heap->itens[i], &heap->itens[menor]);
        transforma_heap(heap, menor, comp);
    }
}

void deleta_heap (Heap* heap){
    free(heap->itens);
}

void desmarca_heap (Heap* heap){
    for (size_t i = 0; i < heap->tamanho; i++){
        heap->itens[i].marcado = false;
    }
        
}

