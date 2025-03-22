#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

int main(){
    IndiceInvertido* indice = aloca();
    int n = 0;
    
    scanf("%d", &n);
    getchar();

    le(indice, n);

    char op;
    scanf("%c", &op);
    switch (op) {
      case 'i':
      case 'I':
        imprime(indice);
        break;
      case'b':
	  case 'B':
        getchar();
        char words[MAX_PALAVRAS_BUSCA][TAM_PALAVRA], ch;
        int index =0;

        while (scanf("%s%c", words[index++], &ch) == 2) {
            if (ch == '\n') {
                break;
            }
        }

        consulta(indice, words, index);
        break;
    }
    libera(indice);
}

