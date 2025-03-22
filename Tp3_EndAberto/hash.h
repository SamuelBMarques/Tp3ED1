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
    char documentos[MAX_DOCS][TAM_DOCUMENTO];
    int ocupado[MAX_DOCS];
} DocHash;

typedef struct {
    //Hash tabela[MAX_TAMANHO];  // Tabela hash
    Hash *tabela;
} IndiceInvertido;

int H(char * chave, int m);
void inserirDocHash(DocHash *set, const char *doc);
void imprimeDoc(Hash *hash);
void inicializarDocHash(DocHash *set);
int buscaDocHash(DocHash *set, const char *doc);

// Funções para ordenação de arrays de strings (supondo que cada string tem TAM_DOCUMENTO caracteres)
void ordenarStrings(char arr[][TAM_DOCUMENTO], int n);
void swap(char arr[][TAM_DOCUMENTO], int i, int j);
int partition(char arr[][TAM_DOCUMENTO], int low, int high);
void quicksort(char arr[][TAM_DOCUMENTO], int low, int high);


# endif
