#ifndef BALANCEADA_HPP
#define BALANCEADA_HPP

#include <iostream>
#include <math.h>

#include "./um/blocos.hpp"
#include "./um/intercalacao.hpp"

#include "./dois/blocosSelecao.hpp"
#include "color.hpp"

using namespace std;

#include "./color.hpp"

void intercalacao_balanceada(int qtd, int situacao, int metodo, bool parametro);
void mostrarDados(FILE *arq, int qtd, int situacao, FILE *fitaFinal);

#endif