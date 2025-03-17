#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Manter como especificado
#define VAZIO "!!!!!!!!!!\0"

void inicia(Hash *hash, int m, int p) {
    hash->m = m;
    hash->p = p;
    hash->pesos = (int *)malloc(p * sizeof(int));
    hash->chaves = (Chave *)malloc(m * sizeof(Chave));
    for (int i = 0; i < m; i++){
        strcpy(hash->chaves[i], VAZIO);
    }
}

// Manter como especificado
void libera(Hash *hash) {
    // PREENCHER AQUI
    free(hash->chaves);
    free(hash->pesos);
}

int H(Hash* hash, Chave chave) {
    // PREENCHER AQUI
    unsigned int s = 0;
    for (int i = 0; i < strlen(chave); i++) {
        s += (unsigned int)chave[i] * hash->pesos[i % hash->p];
    }
    return s % hash->m;
    
}

// Manter como especificado
int insere (Hash *hash, Chave chave) {
    // PREENCHER AQUI
    int h = H(hash, chave);
    int j = 0;
    while ( strcmp ( hash->chaves[(h + j) % hash->m ], VAZIO ) != 0 && j < hash->m && strcmp(hash->chaves[(h + j) % hash->m ],chave )!= 0) {
        j++;
    }

    if(!strcmp(hash->chaves[(h + j) % hash->m ],chave))return -1;

    //printf("\n%d\n",j);
    if(j<hash->m){
        strcpy(hash->chaves[(h + j) % hash->m], chave);
        return (h + j) % hash->m;
    }
    
    return -1;
}
