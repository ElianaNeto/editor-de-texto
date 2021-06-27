#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED
#define NOT_FOUND -1
#define OK 0
#define LIST_FULL 1
#define LIST_EMPTY 2
#define INVALID_INDEX 3
#define NO_SPACE 4
#define IMPOSSIBLE_REMOTION 5

//Codigo dos comandos
#define CMD_INSERIR 1
#define CMD_REMOVER 2
#define CMD_LINHA 3
#define CMD_LOCALIZAR 4
#define CMD_ALTERAR 5
#define CMD_ULTIMO 6
#define CMD_IMPRIMIR 7
#define CMD_FIM 8
#define NOT_CMD -1

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
int converteStringToInte(char str[]);

TAtomo *procurarLinhaCorrent(Tlista editor, int id);

void inicEditor(Tlista *editor);
Boolean vaziaLista(Tlista editor);
int verificarComando(char st[]);
int compararRec(char st1[], char st2[], int i);
void getComand(char st[], char st1[], int startCommandIndex);
int checkCommand(int startCommandIndex, char comando[]);
void linha(Tlista *editor, char comando[]);

void copiar(char st1[], char st2[]);
void iniciarId(Tlista *editor);

void actualizarLinhas(Tlista *editor);

//operacoes do editor
int adicionarLinha(Tlista *editor, char comando[]);
void imprimirLista(Tlista *lista);
void comandoLinha(Tlista editor, char comando[], int *id);
void cmd_ultimo(Tlista *lista);

//
int adicionarDepoisdaCorrente(Tlista *editor, char comando[]);

void funcao_teste(Tlista *editor);
int novo(Tlista *editor, char comando[]);

#endif