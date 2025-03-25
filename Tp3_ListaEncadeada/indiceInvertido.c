#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

IndiceInvertido* aloca() {
    IndiceInvertido* indice = (IndiceInvertido*)malloc(sizeof(IndiceInvertido));
    indice->tabela = (Hash**)malloc(MAX_TAMANHO * sizeof(Hash*));
    for (int i = 0; i < MAX_TAMANHO; i++) {
        indice->tabela[i] = NULL; // Inicializa cada posição da tabela como NULL
    }
    return indice;
}

void libera(IndiceInvertido *indice) {
    if (indice == NULL) return;
    
    // Libera cada bucket e suas listas encadeadas
    for (int i = 0; i < MAX_TAMANHO; i++) {
        Hash *atual = indice->tabela[i];
        while (atual != NULL) {
            Hash *temp = atual;
            atual = atual->prox;
            free(temp); // Libera cada nó da lista
        }
        indice->tabela[i] = NULL; // Marca como liberado
    }
    
    // Libera a tabela e o índice
    free(indice->tabela);
    free(indice);
}
void le(IndiceInvertido *indice, int n) {
    for (int i = 0; i < n; i++) {
        char word[TAM_PALAVRA] = {0}, doc[TAM_DOCUMENTO] = {0}, ch;
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
    int h = H(palavra, MAX_TAMANHO);
    int h2 = H2(palavra,MAX_TAMANHO);
    Hash *atual = indice->tabela[(h+h2)%MAX_TAMANHO];

    // Procura a palavra na lista
    while (atual != NULL && strcmp(atual->palavra, palavra) != 0) {
        atual = atual->prox;
    }

    if (atual != NULL) { // Palavra encontrada: verifica se o documento já existe
        // Verificar se o documento já existe na lista de documentos para esta palavra
        int documentoExiste = 0;
        for (int i = 0; i < atual->qtdDocumentos; i++) {
            if (strcmp(atual->documentos[i], nomeDocumento) == 0) {
                documentoExiste = 1;
                break;
            }
        }
        
        // Se o documento não existe e há espaço, adiciona
        if (!documentoExiste && atual->qtdDocumentos < MAX_DOCS) {
            strcpy(atual->documentos[atual->qtdDocumentos], nomeDocumento);
            atual->qtdDocumentos++;
        }
    } else { // Nova palavra: cria nó e insere no início
        Hash *novo = (Hash*)malloc(sizeof(Hash));
        if (novo == NULL) {
            // Tratamento de erro: falha na alocação
            return;
        }
        
        // Inicializa explicitamente cada campo
        strcpy(novo->palavra, palavra);
        novo->qtdDocumentos = 1;
        strcpy(novo->documentos[0], nomeDocumento);
        
        // Inicializa explicitamente as outras posições do array documentos
        for (int i = 1; i < MAX_DOCS; i++) {
            novo->documentos[i][0] = '\0';
        }
        
        novo->prox = indice->tabela[(h+h2)%MAX_TAMANHO];
        indice->tabela[(h+h2)%MAX_TAMANHO] = novo;
    }
}

void imprime(IndiceInvertido *indice) {
    for (int i = 0; i < MAX_TAMANHO; i++) {
        Hash *atual = indice->tabela[i];
        while (atual != NULL) {
            printf("%s -", atual->palavra);
            for (int j = 0; j < atual->qtdDocumentos; j++) {
                printf(" %s", atual->documentos[j]);
            }
            printf("\n");
            atual = atual->prox;
        }
    }
}

Hash* busca(IndiceInvertido *indice, char* palavra) {
    int h = H(palavra, MAX_TAMANHO);
    int h2 = H2(palavra,MAX_TAMANHO);
    Hash *atual = indice->tabela[(h + h2)%MAX_TAMANHO];
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual; // Retorna o nó encontrado
        }
        atual = atual->prox;
    }
    return NULL; // Não encontrado
}

void consulta(IndiceInvertido *indice, char words[][TAM_PALAVRA], int n) {
    if (n <= 0) {
        printf("Nenhuma palavra fornecida.\n");
        return;
    }

    // Caso com uma palavra
    if (n == 1) {
        Hash *node = busca(indice, words[0]);
        if (node == NULL) {
            printf("Palavra '%s' não encontrada.\n", words[0]);
            return;
        }
        ordenarStrings(node->documentos, node->qtdDocumentos);
        for (int i = 0; i < node->qtdDocumentos; i++) {
            printf("%s\n", node->documentos[i]);
        }
        return;
    }

    // Caso com múltiplas palavras
    Hash *primeiraNode = busca(indice, words[0]);
    if (primeiraNode == NULL) {
        printf("none\n");
        return;
    }

    char intersecao[MAX_DOCS][TAM_DOCUMENTO] = {0};
    int countInter = primeiraNode->qtdDocumentos;
    for (int i = 0; i < countInter; i++) {
        strcpy(intersecao[i], primeiraNode->documentos[i]);
    }

    // Atualiza a interseção para cada palavra adicional
    for (int w = 1; w < n; w++) {
        Hash *node = busca(indice, words[w]);
        if (node == NULL) {
            countInter = 0;
            break;
        }

        // Filtra a interseção atual usando os documentos da palavra atual
        int countNova = 0;
        char novaIntersecao[MAX_DOCS][TAM_DOCUMENTO] = {0};
        for (int i = 0; i < countInter; i++) {
            for (int j = 0; j < node->qtdDocumentos; j++) {
                if (strcmp(intersecao[i], node->documentos[j]) == 0) {
                    strcpy(novaIntersecao[countNova], intersecao[i]);
                    countNova++;
                    break;
                }
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