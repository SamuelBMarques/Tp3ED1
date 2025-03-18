#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IndiceInvertido* inicia() {
    IndiceInvertido* indice;
    indice = (IndiceInvertido*)malloc(sizeof(IndiceInvertido));
    indice->tabela = (Hash*)malloc(MAX_TAMANHO* sizeof(Hash));
    for(int i = 0; i< MAX_TAMANHO; i++){
        indice->tabela[i].ocupado = 0;
        indice->tabela[i].qtdDocumentos = 0;
    }
    return indice;
}

// Manter como especificado
void libera(IndiceInvertido *indice) {
    free(indice->tabela);
}

int H(const char* palavra) {
    unsigned int s = 0;
    for (int i = 0; i < strlen(palavra); i++) {
        s += (unsigned int)palavra[i];
    }
    return s % MAX_TAMANHO;
    
}

// Manter como especificado
void insere (IndiceInvertido *indice, char* palavra, char *nomeDocumento) {
    int h = H(palavra);
    int j = 0;
    while (indice->tabela[h+j].ocupado && strcmp(indice->tabela[h+j].palavra, palavra) != 0) {
        j++;  
    }

    if (!indice->tabela[h+j].ocupado) {  
        strcpy(indice->tabela[h+j].palavra, palavra);
        indice->tabela[h+j].qtdDocumentos = 0;
        indice->tabela[h+j].ocupado = 1;
    }

    int qtd = indice->tabela[h+j].qtdDocumentos;
    if (qtd < MAX_DOCS) {
        strcpy(indice->tabela[h+j].documentos[qtd], nomeDocumento);
        indice->tabela[h+j].qtdDocumentos++;
    }
    
}
void imprime(IndiceInvertido *indice) {
    for (int i = 0; i < MAX_TAMANHO; i++) {
        if (indice->tabela[i].ocupado) {
            printf("%s -", indice->tabela[i].palavra);
            for (int j = 0; j < indice->tabela[i].qtdDocumentos; j++) {
                printf(" %s", indice->tabela[i].documentos[j]);
            }
            printf("\n");
        }
    }
}
