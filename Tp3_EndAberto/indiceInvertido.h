#ifndef INDICEINVERTIDO_H
#define INDICEINVERTIDO_H

#include "hash.h"

// Functions
IndiceInvertido* aloca();
void libera(IndiceInvertido *indice);
void le(IndiceInvertido *indice, int n);
void insereIndice(IndiceInvertido *indice, char* palavra, char* nomeDocumento);
void imprime(IndiceInvertido *indice);
int busca(IndiceInvertido *indice, char* palavra);
void consulta(IndiceInvertido *indice, char words[][TAM_PALAVRA], int n);

#endif