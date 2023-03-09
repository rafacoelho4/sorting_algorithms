#include <iostream>
#include <fstream>

#include "files.hpp"

using namespace std;

void openFitas(FILE* fentrada[FITAS], FILE* fsaida[FITAS]) {

    // FITAS DE ENTRADA

    if((fentrada[0] = fopen("fitas/fita1.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita1.txt");
        return;
    }
    if((fentrada[1] = fopen("fitas/fita2.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita2.txt");
        return;
    }
    if((fentrada[2] = fopen("fitas/fita3.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita3.txt");
        return;
    }
    if((fentrada[3] = fopen("fitas/fita4.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita4.txt");
        return;
    }
    if((fentrada[4] = fopen("fitas/fita5.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita5.txt");
        return;
    }
    if((fentrada[5] = fopen("fitas/fita6.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita6.txt");
        return;
    }
    if((fentrada[6] = fopen("fitas/fita7.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita7.txt");
        return;
    }
    if((fentrada[7] = fopen("fitas/fita8.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita8.txt");
        return;
    }
    if((fentrada[8] = fopen("fitas/fita9.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita9.txt");
        return;
    }
    if((fentrada[9] = fopen("fitas/fita10.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita10.txt");
        return;
    }
    if((fentrada[10] = fopen("fitas/fita11.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita11.txt");
        return;
    }
    if((fentrada[11] = fopen("fitas/fita12.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita12.txt");
        return;
    }
    if((fentrada[12] = fopen("fitas/fita13.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita13.txt");
        return;
    }
    if((fentrada[13] = fopen("fitas/fita14.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita14.txt");
        return;
    }
    if((fentrada[14] = fopen("fitas/fita15.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita15.txt");
        return;
    }
    if((fentrada[15] = fopen("fitas/fita16.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita16.txt");
        return;
    }
    if((fentrada[16] = fopen("fitas/fita17.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita17.txt");
        return;
    }
    if((fentrada[17] = fopen("fitas/fita18.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita18.txt");
        return;
    }
    if((fentrada[18] = fopen("fitas/fita19.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita19.txt");
        return;
    }
    if((fentrada[19] = fopen("fitas/fita20.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita20.txt");
        return;
    }

    // FITAS DE SAÍDA

    if((fsaida[0] = fopen("fitas/fita21.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita21.txt");
        return;
    }
    if((fsaida[1] = fopen("fitas/fita22.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita22.txt");
        return;
    }
    if((fsaida[2] = fopen("fitas/fita23.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita23.txt");
        return;
    }
    if((fsaida[3] = fopen("fitas/fita24.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita24.txt");
        return;
    }
    if((fsaida[4] = fopen("fitas/fita25.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita25.txt");
        return;
    }
    if((fsaida[5] = fopen("fitas/fita26.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita26.txt");
        return;
    }
    if((fsaida[6] = fopen("fitas/fita27.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita27.txt");
        return;
    }
    if((fsaida[7] = fopen("fitas/fita28.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita28.txt");
        return;
    }
    if((fsaida[8] = fopen("fitas/fita29.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita29.txt");
        return;
    }
    if((fsaida[9] = fopen("fitas/fita30.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita30.txt");
        return;
    }
    if((fsaida[10] = fopen("fitas/fita31.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita31.txt");
        return;
    }
    if((fsaida[11] = fopen("fitas/fita32.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita32.txt");
        return;
    }
    if((fsaida[12] = fopen("fitas/fita33.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita33.txt");
        return;
    }
    if((fsaida[13] = fopen("fitas/fita34.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita34.txt");
        return;
    }
    if((fsaida[14] = fopen("fitas/fita35.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita35.txt");
        return;
    }
    if((fsaida[15] = fopen("fitas/fita36.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita36.txt");
        return;
    }
    if((fsaida[16] = fopen("fitas/fita37.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita37.txt");
        return;
    }
    if((fsaida[17] = fopen("fitas/fita38.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita38.txt");
        return;
    }
    if((fsaida[18] = fopen("fitas/fita39.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita39.txt");
        return;
    }
    if((fsaida[19] = fopen("fitas/fita40.txt", "w+")) == NULL) {
        printf("\nErro ao abrir arquivo fita40.txt");
        return;
    }
}

void rewindFitas(FILE *fitas[], int n) {
    for(int i = 0; i < n; i++) {
        rewind(fitas[i]);
    }
}

void closeFitas(FILE *fitas[], int n) {
    for(int i = 0; i < n; i++) {
        fclose(fitas[i]);
    }
}
