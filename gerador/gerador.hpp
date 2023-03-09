#ifndef GERADOR_HPP
#define GERADOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../tipo.hpp"

using namespace std;

void gera_arquivo_binario( int opcao, int tamanho );
const char* encontra_arquivo( int opcao );

#endif