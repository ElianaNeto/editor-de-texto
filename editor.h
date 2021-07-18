#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED
#define NOT_FOUND -1
#define OK 0
#define LIST_FULL 1
#define LIST_EMPTY 2
#define INVALID_INDEX 3
#define NO_SPACE 4
#define IMPOSSIBLE_REMOTION 5
#define TAM 80

//Codigo dos comandos
#define NOT_CMD -1
#define CMD_INSERIR 1
#define CMD_REMOVER 2
#define CMD_LINHA 3
#define CMD_LOCALIZAR 4
#define CMD_ALTERAR 5
#define CMD_ULTIMO 6
#define CMD_IMPRIMIR 7
#define CMD_FIM 8
#define CMD_INV 9
#define CMD_DEL 10
#define CMD_UNDO 11

#define LINHA_TAM 100

//Cores
#define COLOR "\033[0;36m"
#define NO_COLOR "\033[0m"

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

typedef struct
{
    int chave;
    float valor;

} TItem;

typedef struct Atomopilha
{
    TInfo info;
    struct Atomopilha *pant;

} PAtomo;

typedef struct
{
    //TItem pilha[TAM];
    //TItem *pilha;

    //TInfo info;
    PAtomo *pTopo;

} TPilha;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} Boolean;

//Funcoes para a estrutura de dados pilha
int iniciarPilha(TPilha *pilha);
int empilhar(TPilha *pilha, char *comando);
int desempilhar(TPilha *pilha);
int vaziaPilha(TPilha pilha);

void warning(int warningCode);
void error(int errorCode);

int comprimentoSt(char st[]);
int converteStringToInte(char str[]);
TAtomo *procurarLinha(Tlista editor, int id);
void inicEditor(Tlista *editor);
Boolean vaziaLista(Tlista editor);
int verificarComando(char st[]);
int compararRec(char st1[], char st2[], int i);
void getComand(char st[], char st1[], int startCommandIndex);
int checkCommand(int startCommandIndex, char comando[]);
void cmd_linha(Tlista *editor, char comando[]);

void copiar(char st1[], char st2[]);
void iniciarId(Tlista *editor);
void limparTerminal();

void actualizarLinhas(Tlista *editor);

//operacoes do editor
int adicionarLinha(Tlista *editor, char comando[]);
void imprimirLista(Tlista *lista);
void comandoLinha(Tlista editor, char comando[], int *id);
void cmd_ultimo(Tlista *lista);

int remover(Tlista *lista, int id);
void cmd_remover(Tlista *editor, char comando[]);

int adicionarDepoisdaCorrente(Tlista *editor, char comando[]);
void cmd_imprimir(Tlista *editor, char comando[]);

void funcao_teste(Tlista *editor);
int encontrarVirgula(char comando[]);
void separar4(char st1[], char st2[], char st3[], char st4[], char comando[]);
void separarLocalizar(char st1[], char st2[], char st3[], char comando[]);

void localizarFrase(Tlista lista, char *frase);
void cmd_localizar(Tlista *editor, char comando[]);
int encontrarPercent(char comando[]);

//void alterarFrase(Tlista *lista, char oldString[], char newString[]);
int alterarFrase(Tlista lista, char *substring, char *frase);
void afastarCaracteres(char *str, int qtd, int ini, int op);
void arrastarString(char *str, int pos, int size);

void cmd_alterar(Tlista *editor, char comando[]);
void separarAlterar(char oldString[], char newString[], char comando[]);

//Creuma
void pegarPosicaoString(TAtomo *paux, char subs[], int *posInicial, int *posFinal);
void alterarString(Tlista *lista, char subString1[], char subString2[]);

void separarALTNOVO(char oldString[], char newString[], char comando[]);
void ckecarParametros(char st[]);
void pegarPalavrasAlterar(char st[], char oldString[], char newString[]);

//novo alterar
void alterarFrase1(Tlista *lista, char oldString[], char newString[]);
int fStrStr(char *str, char *strSub);
int find(char *str, char *strSub);

///
void cmd_prninv(Tlista *editor, char comando[]);

//NOVOS COMANDOS A SEREM IMPLEMENTADOS
//deletar()
//undo()
int undo(Tlista *editor, TPilha *pilha);
int delectar(Tlista *editor, TPilha *pilha);

#endif