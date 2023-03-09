#include "blocos.hpp"

using namespace std;

void blocos(FILE *in, FILE *fin[], FILE *fout[], int n, bool parametro) {

    // Parâmetros de análise do algoritmo
    int comparacoes = 0, tleitura = 0, tescrita = 0; double time;

    // Inicializamos as variáveis de auxílio a captar o tempo de execução
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Vetor de itens que irei ler e ordenar
    Item pag[LEITURA];
    
    // i = acompanhar leitura // f = acompanhar fitas // e = acompanha escrita
    int i = 0, f = 0, e = 0;

    // Contando as vezes que foi feita a leitura
    int qtd = 0;

    // Cálculo de quantos itens existem na última página
    int calc = n%LEITURA;

    // Enquanto não chego na minha quantidade desejada
    while (qtd < n) {

        // Se minha ultima pagina nao tiver cheia, nao devo ler ela inteira
        // Se (LEITURA % n) não for igual a 0, devo tratar para nao ler LEITURA itens mesmo assim
        int aux = LEITURA;
        if(qtd + LEITURA > n) aux = calc;

        // Lendo itens
        for(i = 0; i < LEITURA; i++) {
            // Se chegar ao final do arquivo antes de ler pagina
            if(feof(in) != 0) break;

            // Aux = tamanho da ultima pagina
            else if(i >= aux) {
                // Preencho o resto da pagina com notas maximas para o método de ordenação-
                // nao mexer com os valores antigos que estavam na pagina
                for(int o = i; o < LEITURA; o++) pag[o].nota = INT_MAX;
                break;
            }

            else {
                fscanf(in, "%ld %lf %2[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
                    &pag[i].inscricao, &pag[i].nota, pag[i].estado, pag[i].cidade, pag[i].curso);

                tleitura++;
                qtd++;
            }
        }

        // Ordenando bloco de acordo com nota
        bubbleSort(pag, LEITURA, &comparacoes);

        // Escrevendo itens ordenados na minha fita de saída
        for(e = 0; e < LEITURA; e++) {
            if(e >= aux) break;
            fprintf(fin[f], "%li %.1lf %s %s %s\n", pag[e].inscricao, pag[e].nota, pag[e].estado, pag[e].cidade, pag[e].curso);
            
            tescrita++;
        }

        // Separação dos blocos
        fprintf(fin[f], "\n");
        separacaoBloco(fin[f]);

        // Se tiver chegado na minha última fita, volto a minha primeira
        if(f == FITAS - 1) {
            f = 0;
        } else f++;
        // Proxima escrita é na próxima fita
    }

    // Clock é parado e o tempo de execução é retornado em double
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    time = cpu_time_used;

    printf("\n");
    std::cout<<color::rize( "                       RESULTADOS GERACAO DOS BLOCOS                    ", "Black" , "Light Cyan" )<<endl;
    printf(ANSI_COLOR_BLUE "\nCOMPARACOES: \t\t\t\t %d" ANSI_COLOR_RESET, comparacoes);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE LEITURA: \t\t %d" ANSI_COLOR_RESET, tleitura);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE ESCRITA: \t\t %d" ANSI_COLOR_RESET, tescrita);
    printf(ANSI_COLOR_BLUE "\nTEMPO TOTAL: \t\t\t\t %lf segundos" ANSI_COLOR_RESET, time);
    printf("\n");

    fclose(in);
    fimBloco(fin);
}

void separacaoBloco(FILE *fout[]) {
    Item sep;
    sep.inscricao = -1;
    sep.nota = -1.0;
    strcpy(sep.estado, "XX");
    strcpy(sep.cidade, "YYYYYYYY                                          ");
    strcpy(sep.curso, "ZZZZZZZZZZZZZ                 ");

    // Indicaçao de finalização dos blocos em cada fita
    for(int k = 0; k < FITAS; k++)
        fprintf(fout[k], "%li %.2lf %3s %50s %30s\n", sep.inscricao, sep.nota, sep.estado, sep.cidade, sep.curso);
}

void separacaoBloco(FILE *fout) {
    Item sep;
    sep.inscricao = -1;
    sep.nota = -1.0;
    strcpy(sep.estado, "XX");
    strcpy(sep.cidade, "YYYYYYYY                                          ");
    strcpy(sep.curso, "ZZZZZZZZZZZZZ                 ");

    // Indicaçao de finalização dos blocos em cada fita
    fprintf(fout, "%li %.2lf %3s %50s %30s\n", sep.inscricao, sep.nota, sep.estado, sep.cidade, sep.curso);
    
}

void fimBloco(FILE *fout[]) {
    Item sep;
    sep.inscricao = -2;
    sep.nota = -2.0;
    strcpy(sep.estado, "XX");
    strcpy(sep.cidade, "YYYYYYYY                                          ");
    strcpy(sep.curso, "ZZZZZZZZZZZZZ                 ");

    // Retirando a separação de bloco e escrevendo por cima fim dos blocos
    for(int k = 0; k < FITAS; k++) {
        fseek(fout[k], -sizeof(Item), SEEK_CUR);
        fprintf(fout[k], "\n");
        fprintf(fout[k], "%li %.1lf %3s %50s %30s\n", sep.inscricao, sep.nota, sep.estado, sep.cidade, sep.curso);
    }
}