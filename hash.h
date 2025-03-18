# ifndef hash_h
# define hash_h

#define MAX_TAMANHO 1000  
#define MAX_DOCS 100   
#define MAX_PALAVRAS_DOC 1000 
#define MAX_PALAVRAS_BUSCA 100 
#define TAM_PALAVRA 21       
#define TAM_DOCUMENTO 51

typedef struct {
    char palavra[21];      // Palavra-chave (máx. 20 caracteres)
    char documentos[MAX_DOCS][51];  // Vetor de nomes de documentos
    int qtdDocumentos;     // Quantidade de documentos associados
    int ocupado;           // Indica se a posição está ocupada
} Hash;

typedef struct {
    //Hash tabela[MAX_TAMANHO];  // Tabela hash
    Hash *tabela;
    int tamanho;  // Número de elementos na hash
} IndiceInvertido;

// Manter como especificado
IndiceInvertido* inicia();

// Manter como especificado
void libera(IndiceInvertido*);

void imprime(IndiceInvertido *indice);

//Definir de acordo com o metodo escolhido para insercao na arvore
void insere (IndiceInvertido*, char *palavra, char *nomeDocumento);

# endif
