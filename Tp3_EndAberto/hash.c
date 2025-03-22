#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
Nome: H
Funcão: Calcular a posição em que uma palavra deve ser inseridad na tabela hash.
Entrada: A palavra (chave) e o tamanho da hash em que ela vai ser inserida (m).
Saida: Posição (inteiro) para inserir a chave.
*/

int H(char * chave, int m) {
    float p[] = {0.8326030060567271, 0.3224428884580177, 
                 0.6964223353369197, 0.1966079596929834, 
                 0.8949283476433433, 0.4587297824155836, 
                 0.5100785238948532, 0.05356055934904358, 
                 0.9157270141062215, 0.7278472432221632};
    int tamP = 10;
    unsigned int soma = 0;
    for (int i=0;i<strlen ( chave );i++)                    //Para toda caracter da palavra
        soma += (unsigned int) chave [i] * p[i % tamP];     //Calcula o valor inteiro do caracter e multiplica por um dos pesos
    return soma % m;                                        //Retorna 
}

/* 
Nome: ordenarStrings
Funcão: Ordenar um vetor de arrays por ordem alfabética.
Entrada: O vetor de arrays  e o tamanho dele (n).
Saida:--
*/

void ordenarStrings(char arr[][TAM_DOCUMENTO], int n) {
    quicksort(arr, 0, n - 1);
}

/* 
Nome: swap
Funcão: Troca duas arrays de posição dentro do vetor.
Entrada:O vetor de arrays e a posição de cada uma das que devem ser trocadas.
Saida:--
*/

void swap(char arr[][TAM_DOCUMENTO], int i, int j) {
    char temp[TAM_DOCUMENTO];
    strcpy(temp, arr[i]);
    strcpy(arr[i], arr[j]);
    strcpy(arr[j], temp);
}

/* 
Nome: partition
Funcão: Rearranja o vetor de documentos para que as palavras anteriores fiquem à esquerda do pivô e as posteriores à direita.
Entrada: Vetor de arrays e as posições que demarcam qual parte deve ser ordenada.
Saida: Posição do pivô.
*/

int partition(char arr[][TAM_DOCUMENTO], int low, int high) {
    char* pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) {                        //Comparação alfabética
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);                                     //Troca o pivô para sua devida posição
    return i + 1;
}

/* 
Nome: quicksort
Funcão: Recursivamente, realiza a ordenação do vetor de arrays.
Entrada: Vetor de arrays e as posições que demarcam qual parte deve ser ordenada.
Saida:--
*/

void quicksort(char arr[][TAM_DOCUMENTO], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);                    //À esquerda do pivô
        quicksort(arr, pi + 1, high);                   //À direita do pivô
    }
}

/* 
Nome: inicializarDocHash
Funcão: Inicializa um hash de documentos.
Entrada: Hash de documentos.
Saida:--
*/

void inicializarDocHash(DocHash *set) {
    for (int i = 0; i < MAX_DOCS; i++) {
        set->ocupado[i] = 0;                //Indica que todos estão vazios
    }
}

/* 
Nome: inserirDocHash
Funcão: Insere um documento no hash especifico de documentos.
Entrada: Hash de documentos e o documento a ser inserido.
Saida:--
*/

void inserirDocHash(DocHash *set, const char *doc) {
    int h = H((char*)doc, MAX_DOCS);                                        // Reutiliza a função H existente
    int j = 0;
    while (j < MAX_DOCS && set->ocupado[(h + j) % MAX_DOCS]) {
        if (strcmp(set->documentos[(h + j) % MAX_DOCS], doc) == 0) {        //Se o documento já está na hash
            return;
        }
        j++;
    }
    if (j < MAX_DOCS) {                                                     //Se não percorreu todo o vetor
        strcpy(set->documentos[(h + j) % MAX_DOCS], doc);                   //Insere
        set->ocupado[(h + j) % MAX_DOCS] = 1;
    }
}

/* 
Nome: buscaDocHash
Funcão: Procura um documento no hash especifico de documentos.
Entrada: Hash de documentos e o documento a ser procurado.
Saida: Inteiro que indica a posição em o documento está ou 0 se não o encontrou.
*/

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