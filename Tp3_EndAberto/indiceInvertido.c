#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

/* 
Nome: aloca
Funcão: Aloca a memória e inicializa o hash de indice invertido.
Entrada:--
Saida: Hash de indice invertido.
*/

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

/* 
Nome: libera
Funcão: Libera a memória do hash de indice invertido.
Entrada: Hash de indice invertido.
Saida: --
*/

void libera(IndiceInvertido *indice) {
    free(indice->tabela);
    free(indice);
}

/* 
Nome: le
Funcão: Lê a entrada e chama a função que insere no hash de indice invertido.
Entrada: Hash de indice invertido e o número de linhas da entrada.
Saida: --
*/

void le(IndiceInvertido *indice, int n) {
    for (int i = 0; i < n; i++) {
        char word[TAM_PALAVRA], doc[TAM_DOCUMENTO], ch;
        scanf("%s", doc);                                       //Lê o documento
        while (scanf("%s%c", word, &ch) == 2) {                 //Lê a palavra e o caracter em sequencia
            insereIndice(indice, word, doc);                    //insere
            if (ch == '\n') {                                   //Se o caracter for \n, chegou no final da linha
                break;
            }
        }
    }
}

/* 
Nome: insereIndice
Funcão: Insere no hash de indice invertido, na devida posição e trata os casos de colisões.
Entrada: Hash de indice invertido, palavra e documento.
Saida: --
*/

void insereIndice(IndiceInvertido *indice, char* palavra, char *nomeDocumento) {
    int h = H(palavra, MAX_TAMANHO);
    int j = 0;
    while (indice->tabela[h+j].ocupado &&
           strcmp(indice->tabela[h+j].palavra, palavra) != 0) {
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

/* 
Nome: imprime
Funcão: Imprime todo o hash de indice invertido.
Entrada: Hash de indice invertido.
Saida: --
*/

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

/* 
Nome: busca
Funcão: Procura uma palavra no hash, e retorna a posição, caso tenha encontrado.
Entrada: Hash de indice invertido e a palavra.
Saida: Posição em que a palavra foi encontrada.
*/

int busca(IndiceInvertido *indice, char* palavra) {
    int h = H(palavra, MAX_TAMANHO);
    int j = 0;
    while (j < MAX_TAMANHO && indice->tabela[(h+j)%MAX_TAMANHO].ocupado &&
           strcmp(indice->tabela[(h+j)%MAX_TAMANHO].palavra, palavra) != 0) {           // Se não percorreu todas as posições e a posição está ocupada e a palavra for diferente da buscada
        j++;  
    }
    if (j >= MAX_TAMANHO || !indice->tabela[(h+j)%MAX_TAMANHO].ocupado) {               // Se percorreu todas as posições ou encontrou uma posição vazia
        return -1;
    }
    return (h+j) % MAX_TAMANHO;
}

/* 
Nome: consulta
Funcão: Procura uma ou mais palavras no hash e exibe os documentos que pertencem a ambas.
Entrada: Hash de indice invertido, vetor de palavras e tamanho de tal vetor.
Saida: --
*/

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
