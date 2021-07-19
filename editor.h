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

#define LINHA_TAM 80

//Cores
#define COLOR "\033[0;36m"
#define NO_COLOR "\033[0m"

typedef struct
{
    int idLinha;
    char *frase;
    char *fraseAux;

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
    int nElem;

} TPilha;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} Boolean;

void warning(int warningCode);
void error(int errorCode);

//Funcoes para a estrutura de dados pilha
int iniciarPilha(TPilha *pilha);
int empilhar(TPilha *pilha, TInfo info);
int desempilhar(TPilha *pilha);
PAtomo *desempilharAtomo(TPilha *pilha);
int adicionarDepois(Tlista *editor, TPilha *pilha);
int inserirPalavra(Tlista *lista, int pos, char *string);

int vaziaPilha(TPilha pilha);

int comprimentoSt(char *st);
int converteStringToInte(char *str);
TAtomo *procurarLinha(Tlista editor, int id);
int inicEditor(Tlista *editor);
Boolean vaziaLista(Tlista editor);
int verificarComando(char *st);
int compararRec(char *st1, char *st2, int i);
int getcomandod(char *st, char *st1, int startCommandIndex);
int checkCommand(int startCommandIndex, char *comando);
int cmdLinha(Tlista *editor, char *comando);

int copiar(char *st1, char *st2);
int iniciarId(Tlista *editor);
int limparTerminal();

int actualizarLinhas(Tlista *editor);

//operacoes do editor
int adicionarLinha(Tlista *editor, char *comando);
int imprimirLista(Tlista *lista);
int comandoLinha(Tlista editor, char *comando, int *id);
int cmdUltimo(Tlista *lista);

int remover(Tlista *lista, int id);
int cmdRemover(Tlista *editor, char *comando);

int adicionarDepoisdaCorrente(Tlista *editor, char *comando);
int cmdImprimir(Tlista *editor, char *comando);

int funcaoTeste(Tlista *editor);
int encontrarVirgula(char *comando);
int separar4(char *st1, char *st2, char *st3, char *st4, char *comando);
int separarLocalizar(char *st1, char *st2, char *st3, char *comando);

int localizarFrase(Tlista lista, char *frase);
int cmdLocalizar(Tlista *editor, char *comando);
int encontrarPercent(char *comando);

int cmdFim(int *startMode, int *insertMode);
int cmdDeletar(Tlista *editor, char *comando, TPilha *pilha);

//int alterarFrase(Tlista *lista, char oldString, char newString);
int alterarFrase(Tlista lista, char *substring, char *frase);
int afastarCaracteres(char *str, int qtd, int ini, int op);
int arrastarString(char *str, int pos, int size);

int cmdAlterar(Tlista *editor, char *comando);
int separarAlterar(char *oldString, char *newString, char *comando);

int pegarString(char *comando, char *string);
int separarDeletar(char *comando, char *string);

//
int pegarPosicaoString(TAtomo *paux, char *subs, int *posInicial, int *posFinal);
int alterarString(Tlista *lista, char *subString1, char *subString2);

int separarALTNOVO(char *oldString, char *newString, char *comando);
int ckecarParametros(char *st);
int pegarPalavrasAlterar(char *st, char *oldString, char *newString);

//novo alterar
int alterarFrase1(Tlista *lista, char *oldString, char *newString);
int fStrStr(char *str, char *strSub);
int find(char *str, char *strSub);

///
int cmdPrninv(Tlista *editor, char *comando);

//NOVOS comandoS A SEREM IMPLEMENTADOS
//deletar()
//undo()
int undo(Tlista *editor, TPilha *pilha);
int deletar(Tlista *editor, TPilha *pilha, char *string);

#endif