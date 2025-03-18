#ifndef indiceInvertido_h
#define indiceInvertido_h

#include "hash.h"

IndiceInvertido* aloca();
void libera(IndiceInvertido *indice);
void le(IndiceInvertido *indice,int n,  char documentos[][51], char palavras[][21], int* num_palavras);
void insereIndice (IndiceInvertido *indice, char* palavra, char *nomeDocumento);
void imprime(IndiceInvertido *indice);
int busca(IndiceInvertido *indice, char* palavra);

#endif