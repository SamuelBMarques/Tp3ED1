#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

IndiceInvertido* aloca() {
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

void le(IndiceInvertido *indice,int n,  char documentos[][51], char palavras[][21], int* num_palavras){
    for (int i = 0; i < n; i++) {
        char linha[TAM_DOCUMENTO + (MAX_PALAVRAS_DOC * (TAM_PALAVRA + 1))];
        fgets(linha, sizeof(linha), stdin);  // Lendo a linha completa

        // Extrair o nome do documento
        char *ptr = linha;
        sscanf(ptr, "%s", documentos[i]);

        // Pular o nome do documento e começar a extrair palavras
        ptr += strlen(documentos[i]);
        while (*ptr == ' ') ptr++;  // Pular espaços extras

        // Extrair palavras até o final da linha
        while (*ptr != '\0' && *ptr != '\n' && num_palavras[i] < MAX_PALAVRAS_DOC) {
            sscanf(ptr, "%s", palavras[num_palavras[i]]);
            ptr += strlen(palavras[num_palavras[i]]);
            num_palavras[i]++;
            while (*ptr == ' ') ptr++;  // Pular espaços extras
        }
        for(int j = 0; j<num_palavras[i]; j++){
            insereIndice(indice,palavras[j],documentos[i]);
        }
    }
}

void insereIndice (IndiceInvertido *indice, char* palavra, char *nomeDocumento) {
    int h = H(palavra, MAX_TAMANHO);
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

int busca(IndiceInvertido *indice, char* palavra){
    for (int i = 0; i < MAX_TAMANHO; i++) {
        if (indice->tabela[i].ocupado) {
            for (int j = 0; j < MAX_DOCS; j++) {
                if(strcmp(indice->tabela[i].documentos[j], palavra) == 0)
                    return j;
            }
        }
    }
    return 0;
}