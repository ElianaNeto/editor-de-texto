#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED
#define NOT_FOUND -1
#define OK 0
#define LIST_FULL 1
#define LIST_EMPTY 2
#define INVALID_INDEX 3
#define NO_SPACE 4
#define IMPOSSIBLE_REMOTION 5

#define LINHA_TAM 60

typedef struct
{
    int idLinha;
    char frase[LINHA_TAM];

} TInfo;

typedef struct Atomo
{
    TInfo info;
    struct Atomo *dprox;
    struct Atomo *eprox;

} TAtomo;

typedef struct
{
    TAtomo *primeiro;
    TAtomo *ultimo;
    TAtomo *linhaCorrent;
    int quantLinhas;

} Tlista;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} Boolean;

int comprimentoSt(char st[]);

void inicEditor(Tlista *editor);
Boolean vaziaLista(Tlista editor);
int verificarComando(char st[]);
int compararRec(char st1[], char st2[], int i);
void getComand(char st[], char st1[], int startCommandIndex);
int checkCommand(int startCommandIndex, char comando[]);
int adicionarLinha(Tlista *editor, char comando[]);
void linha(Tlista *editor, char comando[]);
int converteStringToInte(char str[]);
void copiar(char st1[], char st2[]);
void imprimirLista(Tlista *lista);
void comandoLinha(Tlista editor, char comando[], int id);
int procurarLinhaCorrent(Tlista editor, int id);
int adicionarDepoisdaCorrente(Tlista *editor, char comando[]);

//Operacoes
//inserir
//remover
//linha
//Localizar
//alterar
//ultimo
//imprimir
//fim

#endif