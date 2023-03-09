#include "balanceada.hpp"

void intercalacao_balanceada(int qtd, int situacao, int metodo, bool parametro) {

    // Arquivo de entrada
    FILE *in;
    if(situacao == 1) {
        if((in = fopen("entrada/PROVAO_ORDENADO.txt", "r")) == NULL) {
            printf("\nErro ao abrir arquivo PROVAO_ORDENADO.txt");
            return;
        }
    } else if (situacao == 2) {
        if((in = fopen("entrada/PROVAO_INVERSAMENTE.txt", "r")) == NULL) {
            printf("\nErro ao abrir arquivo PROVAO_INVERSAMENTE.txt");
            return;
        }
    } else if (situacao == 3) {
        if((in = fopen("entrada/PROVAO.txt", "r")) == NULL) {
            printf("\nErro ao abrir arquivo PROVAO.txt");
            return;
        }
    } else {
        printf("Situacao de arquivo desconhecida.");
        return;
    }

    // Fitas de entrada e saída
    FILE *fin[FITAS], *fout[FITAS];

    // Abro todas as fitas de saída e entrada
    openFitas(fin, fout);

    // Gerando blocos inicialmente ordenados
    if(metodo == 1) blocos(in, fin, fout, qtd, parametro);
    else if(metodo == 2) blocosSelecao(in, fin, fout, qtd, parametro);

    // Parâmetros de análise do algoritmo
    int comparacoes = 0, tleitura = 0, tescrita = 0; double time;

    // Inicializamos as variáveis de auxílio a captar o tempo de execução
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int ready = 0, i = 2;
    do{
        ready = 0;
        // Variavel ready ira continuar com valor 0 se apenas uma fita for preenchida

        rewindFitas(fin, FITAS); rewindFitas(fout, FITAS);

        // Vou intercalando as fitas de entrada como saida e saida como entrada
        if(i%2 == 0) intercalacao(fin, fout, &ready, &comparacoes, &tleitura, &tescrita);
        else intercalacao(fout, fin, &ready, &comparacoes, &tleitura, &tescrita);
        
        // i irá tomar valores pares e ímpares intercaladamente => 2, 3, 4, 5, 6...
        i++;
    } while(ready != 0);

    // Clock é parado e o tempo de execução é retornado em double
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    time = cpu_time_used;

    rewindFitas(fin, FITAS); rewindFitas(fout, FITAS);

    // Se i for par no final, a fita ordenada final é a 21
    // Se i for ímpar no final, a fita ordenada final é a 1
    if(parametro) mostrarDados(in, qtd, situacao, i%2 == 0 ? fin[0] : fout[0]);

    // Impressão dos resultados
    std::cout<<color::rize( "                       RESULTADOS INTERCALACAO                    ", "Black" , "Light Cyan" )<<endl;
    printf(ANSI_COLOR_BLUE "\nCOMPARACOES: \t\t\t\t %d" ANSI_COLOR_RESET, comparacoes);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE LEITURA: \t\t %d" ANSI_COLOR_RESET, tleitura);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE ESCRITA: \t\t %d" ANSI_COLOR_RESET, tescrita);
    printf(ANSI_COLOR_BLUE "\nTEMPO TOTAL: \t\t\t\t %lf segundos" ANSI_COLOR_RESET, time);
    printf(ANSI_COLOR_BLUE "\n\nFITA FINAL: %d" ANSI_COLOR_RESET, i%2 == 0 ? 1 : FITAS+1);
    printf("\n");

    // Todas as fitas são fechadas
    closeFitas(fin, FITAS); closeFitas(fout, FITAS);

    return;
}

void mostrarDados(FILE *arq, int qtd, int situacao, FILE *fitaFinal) {
    Item leitura;
    
    FILE *in;
    if(situacao == 1) {
        if((in = fopen("entrada/PROVAO_ORDENADO.txt", "r")) == NULL) {
            printf("\nErro ao abrir arquivo PROVAO_ORDENADO.txt");
            return;
        }
    } else if (situacao == 2) {
        if((in = fopen("entrada/PROVAO_INVERSAMENTE.txt", "r")) == NULL) {
            printf("\nErro ao abrir arquivo PROVAO_INVERSAMENTE.txt");
            return;
        }
    } else if (situacao == 3) {
        if((in = fopen("entrada/PROVAO.txt", "r")) == NULL) {
            printf("\nErro ao abrir arquivo PROVAO.txt");
            return;
        }
    }
    
    printf("\n\n");
    printf("                       ARQUIVO ORIGINAL:                   \n");

    for(int i = 0; i < qtd; i++) {
        fscanf(in, "%ld %lf %[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
            &leitura.inscricao, &leitura.nota, leitura.estado, leitura.cidade, leitura.curso);

        printf("\n%li %.1lf %s %s %s", leitura.inscricao, leitura.nota, leitura.estado, leitura.cidade, leitura.curso);
    }

    printf("\n\n");
    printf("                       ARQUIVO GERADO:                   \n");
    for(int i = 0; i < qtd; i++) {
        fscanf(fitaFinal, "%ld %lf %[A-Z] %49[A-Z a-z] %[A-Z a-z] \n", 
            &leitura.inscricao, &leitura.nota, leitura.estado, leitura.cidade, leitura.curso);

        printf("\n%li %.1lf %s %s %s", leitura.inscricao, leitura.nota, leitura.estado, leitura.cidade, leitura.curso);
    }

    printf("\n\n");
}
