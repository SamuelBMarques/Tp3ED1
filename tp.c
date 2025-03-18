#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(){
    IndiceInvertido* indice = inicia();
    int n = 0;
    scanf("%d", &n);
    
    insere(indice, "algoritmo", "prog.c");
    insere(indice, "algoritmo", "doc.c");
    insere(indice, "selecao", "darwin.c");
    imprime(indice);
    libera(indice);
}