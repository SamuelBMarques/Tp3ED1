#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H(char * chave, int m) {
    float p[] = {0.8326030060567271, 0.3224428884580177, 
                 0.6964223353369197, 0.1966079596929834, 
                 0.8949283476433433, 0.4587297824155836, 
                 0.5100785238948532, 0.05356055934904358, 
                 0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    unsigned int soma = 0;
    for (int i=0;i<strlen ( chave );i++)
        soma += (unsigned int) chave [i] * p[i % tamP];
    return soma % m;
}

// Função para ordenar um array de strings
void ordenarStrings(char arr[][TAM_DOCUMENTO], int n) {
    quicksort(arr, 0, n - 1);
}

// Função para trocar duas strings no array
void swap(char arr[][TAM_DOCUMENTO], int i, int j) {
    char temp[TAM_DOCUMENTO];
    strcpy(temp, arr[i]);
    strcpy(arr[i], arr[j]);
    strcpy(arr[j], temp);
}

// Função de partição do Quicksort
int partition(char arr[][TAM_DOCUMENTO], int low, int high) {
    char* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) { // Comparação alfabética
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}

// Implementação do Quicksort
void quicksort(char arr[][TAM_DOCUMENTO], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void imprimeDoc(Hash *hash){
    ordenarStrings(hash->documentos, hash->qtdDocumentos);

    for(int i =0; i<hash->qtdDocumentos; i++){
        printf("%s\n", hash->documentos[i]);
    }
}

void inicializarDocHash(DocHash *set) {
    for (int i = 0; i < MAX_DOCS; i++) {
        set->ocupado[i] = 0;
    }
}

void inserirDocHash(DocHash *set, const char *doc) {
    int h = H((char*)doc, MAX_DOCS); // Reutiliza a função H existente
    int j = 0;
    while (j < MAX_DOCS && set->ocupado[(h + j) % MAX_DOCS]) {
        if (strcmp(set->documentos[(h + j) % MAX_DOCS], doc) == 0) {
            return; // Já existe
        }
        j++;
    }
    if (j < MAX_DOCS) {
        strcpy(set->documentos[(h + j) % MAX_DOCS], doc);
        set->ocupado[(h + j) % MAX_DOCS] = 1;
    }
}

int buscaDocHash(DocHash *set, const char *doc) {
    int h = H((char*)doc, MAX_DOCS);
    int j = 0;
    while (j < MAX_DOCS && set->ocupado[(h + j) % MAX_DOCS]) {
        if (strcmp(set->documentos[(h + j) % MAX_DOCS], doc) == 0) {
            return 1;
        }
        j++;
    }
    return 0;
}