#include "intercalacao.hpp"

using namespace std;

void intercalacao(FILE *fin[], FILE *fout[], int *ready, int *comparacoes, int *tleitura, int *tescrita) {

    // Guarda registros para achar menor item || Menor item dos selecionados de cada fita
    Item pag[FITAS]; Item menor;

    // Controlando quais fitas ja chegaram ao final
    int sair[FITAS];
    // Inicializando tudo com 0
    for(int m = 0; m < FITAS; m++) sair[m] = 0;

    // 'f' acompanha as fitas || 'fmenor' é a fita de onde veio o menor item
    int f = 0, fmenor;

    // Se eu fizer leitura e encontrar sinalização de fim de bloco
    int end;

    // r irá somar todos as posições do vetor 'sair' para ver se todas já estao com valor 1
    // x irá ajudar a checar se todas as fitas ja tiveram seus blocos lidos
    int r, x;

    // Lendo o primeiro item de cada fita de entrada
    lerFitas(pag, sair, fin, &end, tleitura);
    
    do {
        // Se fita ja foi lida por completo, coloco nota naquela posição como maxima para nao interferir na ordenação
        for(int k = 0; k < FITAS; k++) if(sair[k] == 1) pag[k].nota = INT_MAX;

        // Linha para checar se ja foram lidos os blocos inteiros de todas as fitas
        x = 0;
        for(int o = 0; o < FITAS; o++) x += (pag[o].nota == INT_MAX);

        // Se todas as fitas ja tiveram seus primeiros blocos lidos, eu vou pra proxima fita
        if(x == FITAS) {

            (*ready)++;

            // Agora vamos escrever na proxima fita
            // Se tiver chegado na minha última fita, volto a minha primeira
            if(f == FITAS - 1) {
                f = 0;
                // Separação de bloco
                separacaoBloco(fout);
            } else f = f + 1;

            // Voltando todos os valores de sair para 0
            for(int o = 0; o < FITAS; o++) sair[o] = 0;

            // Lendo proximo elemento de todas as fitas
            lerFitas(pag, sair, fin, &end, tleitura);
        }

        // Achar a menor chave
        menor = menorItem(pag, &fmenor, FITAS, comparacoes);

        // Escrevendo item de menor chave na fita de saída
        fprintf(fout[f], "%li %.1lf %2s %49s %29s\n", menor.inscricao, menor.nota, menor.estado, menor.cidade, menor.curso);
        (*tescrita)++;

        // Lendo proximo elemento da fita de onde saiu o menor elemento
        lerFita(pag, sair, fin, &end, tleitura, fmenor);

        r = 0;
        for(int o = 0; o < FITAS; o++) r += (sair[o] == 1);

    } while(r != FITAS);

    // Sinalizador de fim de todos os blocos da fita
    separacaoIntercalacao(fout);
    fimIntercalacao(fout);
}

void lerFitas(Item *pag, int *sair, FILE *fin[], int *end, int *tleitura) {
    // Leio um elemento de cada fita
    for(int g = 0; g < FITAS; g++) {

        fscanf(fin[g], "%ld %lf %2[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
            &pag[g].inscricao, &pag[g].nota, pag[g].estado, pag[g].cidade, pag[g].curso);
        
        (*tleitura)++;

        // Se nota for igual a -2, fim de todos os blocos do arquivo
        if(pag[g].inscricao == -2 || pag[g].nota == -2) {

            pag[g].nota = INT_MAX;
            sair[g]++;
            continue;
        }
        
        // Se nota for igual a -1, fim daquele bloco
        if(pag[g].inscricao == -1 || pag[g].nota == -1) {
            pag[g].nota = INT_MAX;
        }
    }
}

void lerFita(Item *pag, int *sair, FILE *fin[], int *end, int *tleitura, int fmenor) {

    fscanf(fin[fmenor], "%ld %lf %2[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
        &pag[fmenor].inscricao, &pag[fmenor].nota, pag[fmenor].estado, pag[fmenor].cidade, pag[fmenor].curso);
    
    (*tleitura)++;

    // Se nota for igual a -2, fim de todos os blocos do arquivo
    if(pag[fmenor].inscricao == -2 || pag[fmenor].nota == -2) {
        pag[fmenor].nota = INT_MAX;
        sair[fmenor]++;
        return;
    }
        
    // Se nota for igual a -1, fim daquele bloco
    if(pag[fmenor].inscricao == -1 || pag[fmenor].nota == -1) {
        pag[fmenor].nota = INT_MAX;
    }
}

Item menorItem(Item chaves[], int *fmenor, int n, int *comparacoes) {
    Item menor;
    menor = chaves[0];
    *fmenor = 0;

    for(int o = 1; o < n; o++) {
        if(menor.nota > chaves[o].nota) {
            (*comparacoes)++;
            menor = chaves[o];
            *fmenor = o;
        }
    }

    return menor;
}

void separacaoIntercalacao(FILE *fout[]) {
    Item sep;
    sep.inscricao = -2;
    sep.nota = -2.0;
    strcpy(sep.estado, "XX");
    strcpy(sep.cidade, "YYYYYYYY                                          ");
    strcpy(sep.curso, "ZZZZZZZZZZZZZ                 ");

    int fim; Item x;

    // Indicaçao de finalização dos blocos em cada fita
    for(int f = 0; f < FITAS; f++) {
        fprintf(fout[f], "%li %.1lf %s %s %s\n", sep.inscricao, sep.nota, sep.estado, sep.cidade, sep.curso);
        continue;
        fseek(fout[f], -sizeof(Item), SEEK_CUR);

        fim = fscanf(fout[f], "%ld %lf %2[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
            &x.inscricao, &x.nota, x.estado, x.cidade, x.curso);

        if(x.nota == -1 || x.inscricao == -1) { 
            fseek(fout[f], -sizeof(Item), SEEK_CUR);
            fprintf(fout[f], "\n");
        }
        
        fprintf(fout[f], "%li %.1lf %s %s %s\n", sep.inscricao, sep.nota, sep.estado, sep.cidade, sep.curso);
    }
}

void fimIntercalacao(FILE *fout[]) {

    Item x, bottom;

    bottom.inscricao = -2;
    bottom.nota = -2.0;
    strcpy(bottom.estado, "XX");
    strcpy(bottom.cidade, "YYYYYYYY                                          ");
    strcpy(bottom.curso, "ZZZZZZZZZZZZZ                 ");

    int fim;
    for(int f = 0; f < FITAS; f++) {

        fseek(fout[f], -sizeof(Item), SEEK_CUR);

        fim = fscanf(fout[f], "%ld %lf %2[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
            &x.inscricao, &x.nota, x.estado, x.cidade, x.curso);

        
        if(x.inscricao == -2 || x.nota == -2) {
            continue;
        }
            
        // Se nota for igual a -1, fim daquele bloco
        if(x.inscricao == -1 || x.nota == -1) {
            fseek(fout[f], -sizeof(Item), SEEK_CUR);
            fprintf(fout[f], "\n%li %.1lf %s %s %s\n", bottom.inscricao, bottom.nota, bottom.estado, bottom.cidade, bottom.curso);
        } else {
            fprintf(fout[f], "\n%li %.1lf %s %s %s\n", bottom.inscricao, bottom.nota, bottom.estado, bottom.cidade, bottom.curso);
            fprintf(fout[f], "%li %.1lf %s %s %s\n", bottom.inscricao, bottom.nota, bottom.estado, bottom.cidade, bottom.curso);

        }
    }
}