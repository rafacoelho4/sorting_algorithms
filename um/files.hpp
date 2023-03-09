#ifndef FILES_HPP
#define FILES_HPP

#include <cstring>

#define FITAS 20

void openFitas(FILE* fentrada[FITAS], FILE* fsaida[FITAS]);
void rewindFitas(FILE *fitas[], int n);
void closeFitas(FILE *fitas[], int n);
void checarFitas(FILE *fitas[], int n);

#endif