#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

IndiceInvertido* aloca() {
    IndiceInvertido* indice;
    indice = (IndiceInvertido*)malloc(sizeof(IndiceInvertido));
    indice->tabela = (Hash*)malloc(MAX_TAMANHO * sizeof(Hash));
    for (int i = 0; i < MAX_TAMANHO; i++){
        indice->tabela[i].ocupado = 0;
        indice->tabela[i].qtdDocumentos = 0;
    }
    return indice;
}

void libera(IndiceInvertido *indice) {
    free(indice->tabela);
    free(indice);
}

void le(IndiceInvertido *indice, int n) {
    for (int i = 0; i < n; i++) {
        char word[TAM_PALAVRA], doc[TAM_DOCUMENTO], ch;
        scanf("%s", doc);
        while (scanf("%s%c", word, &ch) == 2) {
            insereIndice(indice, word, doc);
            if (ch == '\n') {
                break;
            }
        }
    }
}


void insereIndice(IndiceInvertido *indice, char* palavra, char *nomeDocumento) {
    int h1 = H(palavra, MAX_TAMANHO);
    int h2 = H2(palavra, MAX_TAMANHO);
    int j = 0;
    
    while (indice->tabela[(h1 + j * h2) % MAX_TAMANHO].ocupado &&
           strcmp(indice->tabela[(h1 + j * h2) % MAX_TAMANHO].palavra, palavra) != 0) {
        j++;  
    }
    
    if (!indice->tabela[(h1 + j * h2) % MAX_TAMANHO].ocupado) {  
        strcpy(indice->tabela[(h1 + j * h2) % MAX_TAMANHO].palavra, palavra);
        indice->tabela[(h1 + j * h2) % MAX_TAMANHO].qtdDocumentos = 0;
        indice->tabela[(h1 + j * h2) % MAX_TAMANHO].ocupado = 1;
    }
    
    int qtd = indice->tabela[(h1 + j * h2) % MAX_TAMANHO].qtdDocumentos;
    if (qtd < MAX_DOCS) {
        strcpy(indice->tabela[(h1 + j * h2) % MAX_TAMANHO].documentos[qtd], nomeDocumento);
        indice->tabela[(h1 + j * h2) % MAX_TAMANHO].qtdDocumentos++;
    }
}

int busca(IndiceInvertido *indice, char* palavra) {
    int h1 = H(palavra, MAX_TAMANHO);
    int h2 = H2(palavra, MAX_TAMANHO);
    int j = 0;
    
    while (j < MAX_TAMANHO && indice->tabela[(h1 + j * h2) % MAX_TAMANHO].ocupado &&
           strcmp(indice->tabela[(h1 + j * h2) % MAX_TAMANHO].palavra, palavra) != 0) {
        j++;  
    }
    
    if (j >= MAX_TAMANHO || !indice->tabela[(h1 + j * h2) % MAX_TAMANHO].ocupado) {
        return -1;
    }
    return (h1 + j * h2) % MAX_TAMANHO;
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


void consulta(IndiceInvertido *indice, char words[][TAM_PALAVRA], int n) {
    if (n <= 0) {
        printf("Nenhuma palavra fornecida.\n");
        return;
    }

    // Se apenas uma palavra foi consultada, exibe os documentos dela.
    if (n == 1) {
        int idx = busca(indice, words[0]);
        if (idx == -1) {
            printf("Palavra '%s' não encontrada.\n", words[0]);
            return;
        }
        // Ordena os documentos antes de exibir
        ordenarStrings(indice->tabela[idx].documentos, indice->tabela[idx].qtdDocumentos);
        for (int i = 0; i < indice->tabela[idx].qtdDocumentos; i++) {
            printf("%s\n", indice->tabela[idx].documentos[i]);
        }
        return;
    }

    // Para múltiplas palavras, pegamos os documentos da primeira palavra.
    int idx = busca(indice, words[0]);
    if (idx == -1) {
        printf("none\n");
        return;
    }
    char intersecao[MAX_DOCS][TAM_DOCUMENTO];
    int countInter = indice->tabela[idx].qtdDocumentos;
    for (int i = 0; i < countInter; i++) {
        strcpy(intersecao[i], indice->tabela[idx].documentos[i]);
    }

    // Atualiza a interseção para cada palavra adicional
    for (int w = 1; w < n; w++) {
        int idxW = busca(indice, words[w]);
        if (idxW == -1) {
            countInter = 0;
            break;
        }

        // Cria um hash set para os documentos da palavra atual
        DocHash docSet;
        inicializarDocHash(&docSet);
        for (int j = 0; j < indice->tabela[idxW].qtdDocumentos; j++) {
            inserirDocHash(&docSet, indice->tabela[idxW].documentos[j]);
        }

        // Filtra a interseção atual usando o hash set
        int countNova = 0;
        char novaIntersecao[MAX_DOCS][TAM_DOCUMENTO];
        for (int i = 0; i < countInter; i++) {
            if (buscaDocHash(&docSet, intersecao[i])) {
                strcpy(novaIntersecao[countNova], intersecao[i]);
                countNova++;
            }
        }
        countInter = countNova;
        for (int i = 0; i < countNova; i++) {
            strcpy(intersecao[i], novaIntersecao[i]);
        }

        if (countInter == 0) break;
    }

    // Exibe os documentos resultantes
    if (countInter == 0) {
        printf("none\n");
    } else {
        // Ordena os documentos resultantes
        ordenarStrings(intersecao, countInter);
        for (int i = 0; i < countInter; i++) {
            printf("%s\n", intersecao[i]);
        }
    }
}
