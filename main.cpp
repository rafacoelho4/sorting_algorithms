#include <iostream>
#include <string>

#include "balanceada.hpp"
#include "./tres/quicksort.hpp"
#include "./gerador/gerador.hpp"

using namespace std;

int main(int argc, char *argv[]) 
{
    int metodo = atoi(argv[1]);
    int qtd = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    
    bool parametro = false;
    if(argc > 4){
        string p = argv[4];
        if(p == "-P"){
            parametro = true;
        }
        else{
            cout<<"Parametro invalido\n";
            exit(1);
        }
    }

    if(metodo == 3) {
        // Metodo 3: Quicksort externo
        gera_arquivo_binario(situacao,qtd);
        quick_sort_main(parametro,qtd);
    }

    if(metodo == 1 || metodo == 2) {
        // Método 1: Geração de blocos ordenados usando método de ordenação interna bubblesort
        // Método 2: Geração de blocos ordenados por técnica de seleção por substituição
        intercalacao_balanceada(qtd, situacao, metodo, parametro);
    } 

    return 0;
}