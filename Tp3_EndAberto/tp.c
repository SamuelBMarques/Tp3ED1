#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "indiceInvertido.h"

int main(){
    IndiceInvertido* indice = aloca();              //Aloca e inicializa o hash
    int n = 0;
    
    scanf("%d", &n);                                //Lê o número de linhas
    getchar();

    le(indice, n);                                  //Faz a leitura da entrada

    char op;
    scanf("%c", &op);                               //Lê o operador
    switch (op) {
      case 'i':
      case 'I':                                     //Se for para imprimir
        imprime(indice);
        break;
      case'b':
	  case 'B':                                     //Se for para buscar algum documento
        getchar();
        char words[MAX_PALAVRAS_BUSCA][TAM_PALAVRA], ch;
        int index =0;

        while (scanf("%s%c", words[index++], &ch) == 2) {       //Lê os documentos e as palavras
            if (ch == '\n') {
                break;
            }
        }

        consulta(indice, words, index);                         //Faz a consulta e imprime os documentos encontrados
        break;
    }
    libera(indice);                                             //Libera a memória
}

