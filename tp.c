#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

int main(){
    IndiceInvertido* indice = aloca();
    int n = 0;
    char op, aux;
    char documentos[MAX_DOCS][TAM_DOCUMENTO];
    char palavras[MAX_PALAVRAS_DOC][TAM_PALAVRA];
    int num_palavras[MAX_DOCS] = {0};
    scanf("%d", &n);
    getchar();
    le(indice,n,documentos,palavras,num_palavras);
    scanf("%c",&op);
    switch(op){
        case 'B':
            while(1){
                scanf("%s%c");
            }
        case 'I':
            imprime(indice);
    }   
    imprime(indice);
    libera(indice);
}

