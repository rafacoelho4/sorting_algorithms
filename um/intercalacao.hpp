#ifndef INTERCALACAO_HPP
#define INTERCALACAO_HPP

#include <iostream>
#include <climits>

#include "blocos.hpp"
#include "files.hpp"
#include "sort.hpp"

void intercalacao(FILE *fin[], FILE *fout[], int *ready, int *comparacoes, int *tleitura, int *tescrita);
Item menorItem(Item chaves[], int *fmenor, int n, int *comparacoes);
void separacaoIntercalacao(FILE *fout[]);
void fimIntercalacao(FILE *fout[]);
void lerFitas(Item *pag, int *sair, FILE *fin[], int *end, int *tleitura);
void lerFita(Item *pag, int *sair, FILE *fin[], int *end, int *tleitura, int fmenor);

#endif