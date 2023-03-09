#include "gerador.hpp"
void gera_arquivo_binario(int opcao, int tamanho){
    Item u;
    int cont = 0;
    int size = tamanho;
    const char* nome_arquivo = encontra_arquivo( opcao );
    FILE* arquivo;
    FILE* provao = fopen(nome_arquivo,"r+");
    if((arquivo = fopen("./entrada/PROVAO.bin", "w+b")) != NULL){

        printf("PROVAO.bin Aberto com Sucesso!\n");
        while ((fscanf(provao,"%ld %lf %s %50[A-Z a-z] %30[A-Z a-z] \n", &u.inscricao, &u.nota,
            u.estado, u.cidade,  u.curso)) != EOF && cont < size ){
            fwrite(&u, sizeof(Item), 1, arquivo);
            cont++;
        }
     }
}

const char* encontra_arquivo( int opcao ){
    if(opcao == 3 ){
        return "./entrada/PROVAO.txt";
    }else if( opcao == 1 ){
        return "./entrada/PROVAO_ORDENADO.txt";
    }else if(opcao == 2 ){
        return "./entrada/PROVAO_INVERSAMENTE.txt";
    }else{
        return "nada.txt";
    }
}