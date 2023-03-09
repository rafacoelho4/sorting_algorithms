#ifndef BLOCOS_HPP
#define BLOCOS_HPP

#define LEITURA 3

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <iostream>
#include <climits>
#include <time.h>

#include "files.hpp"
#include "sort.hpp"
#include "../color.hpp"

#include "../color.hpp"

void blocos(FILE *in, FILE *fin[], FILE *fout[], int n, bool parametro);
void separacaoBloco(FILE *fout[]);
void separacaoBloco(FILE *fout);
void fimBloco(FILE *fout[]);

#endif