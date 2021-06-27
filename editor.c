#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

int comprimentoSt(char st[])
{
    int i, n = 0;
    for (i = 0; st[i] != '\0'; i++)
        n++;
    return n;
}

int converteStringToInte(char str[])
{
    int res = 0;
    int sign = 1;
    int i;
    int j = 0;

    if (str[0] == '-')
    {
        sign = -1;
        j++;
    }

    for (i = j; str[i] != '\0'; ++i)
    {
        res = res * 10 + str[i] - '0';
    }
    return sign * res;
}

void inicEditor(Tlista *editor)
{
    editor->primeiro = NULL;
    editor->ultimo = NULL;
    editor->linhaCorrent = NULL;
    editor->quantLinhas = 0;
}

Boolean vaziaLista(Tlista editor)
{
    return (editor.primeiro == NULL);
}

int verificarComando(char st[])
{
    int i = 0;
    int sinalComando = 0;
    while (st[i] != '\0')
    {
        if (st[i] == '$')
        {
            sinalComando = 1;
            break;
        }
        i++;
    }

    if (sinalComando == 1)
        return i;
    return -1;
}

int compararRec(char st1[], char st2[], int i)
{
    if ((st1[i] == '\0') || (st1[i] != st2[i]))
        return st1[i] - st2[i];
    return compararRec(st1, st2, i + 1);
}

void getComand(char st[], char st1[], int startCommandIndex)
{
    int i = startCommandIndex + 1;
    int j = 0;
    while (st1[i] != ' ' && st1[i] != '\n')
    {
        st[j] = st1[i];
        j++;
        i++;
    }
    st[j] = '\0';
}

int checkCommand(int startCommandIndex, char comando[])
{
    char cmd[LINHA_TAM];
    getComand(cmd, comando, startCommandIndex);
    if (compararRec(cmd, "inserir\0", 0) == 0)
        return CMD_INSERIR;

    if (compararRec(cmd, "remover\0", 0) == 0)
        return CMD_REMOVER;

    if (compararRec(cmd, "linha\0", 0) == 0)
        return CMD_LINHA;

    if (compararRec(cmd, "localizar\0", 0) == 0)
        return CMD_LOCALIZAR;

    if (compararRec(cmd, "alterar\0", 0) == 0)
        return CMD_ALTERAR;

    if (compararRec(cmd, "ultimo\0", 0) == 0)
        return CMD_ULTIMO;

    if (compararRec(cmd, "imprimir\0", 0) == 0)
        return CMD_IMPRIMIR;

    if (compararRec(cmd, "fim\0", 0) == 0)
        return CMD_FIM;

    return NOT_CMD;
}
void copiar(char st1[], char st2[])
{
    int i = 0;
    while ((st2[i] = st1[i]) != '\0')
        i++;
}

Boolean listaUnitaria(Tlista *editor)
{
    return editor->primeiro == editor->ultimo;
}

TAtomo *procurarLinhaCorrent(Tlista editor, int id)
{
    TAtomo *paux = editor.primeiro;
    while (paux != NULL && paux->info.idLinha != id)
        paux = paux->dprox;
    return paux;
}

void comandoLinha(Tlista editor, char comando[], int *id)
{
    // int a = verificarComando(comando);
    char st1[30];
    char st2[30];
    int i = 0;
    int j = 0;
    int comprimento = comprimentoSt(comando);

    for (i = 0; i < comprimento; i++)
    {
        if (comando[i] != ' ')
        {
            st1[i] = comando[i];
        }
        else
        {
            break;
        }
    }
    st1[i] = '\0';

    while (comando[i] == ' ')
    {
        i++;
    }
    i = i - 1;
    //printf("i:%d", i);

    for (j = i + 1; j < comprimento; j++)
    {
        if (comando[j] != '\0' && comando[j] != ' ')
        {
            st2[j - i - 1] = comando[j];
        }
        else
        {
            break;
        }
    }
    st2[j - i - 1] = '\0';
    st2[comprimentoSt(st2) - 1] = '\0';
    *id = converteStringToInte(st2);
    //printf("comprimento %d \n", comprimentoSt(st2));
    //printf("{%s}\n", st2);
    //printf("%d \n", *id);
}

void linha(Tlista *editor, char comando[])
{
    //→

    int id = 0;
    comandoLinha(*editor, comando, &id);
    TAtomo *idAux = (TAtomo *)malloc(sizeof(TAtomo));
    idAux = procurarLinhaCorrent(*editor, id);

    if (idAux != NULL)
    {
        editor->linhaCorrent = idAux;
    }
    else
    {
        printf("ERRO: Linha %d não existe!\n", id);
    }
}

void iniciarId(Tlista *editor)
{
    for (TAtomo *paux = editor->primeiro; paux != NULL; paux = paux->dprox)
        paux->info.idLinha = 0;
}

void actualizarLinhas(Tlista *editor)
{

    iniciarId(editor);
    editor->primeiro->info.idLinha = 1;
    for (TAtomo *paux = editor->primeiro->dprox; paux != NULL; paux = paux->dprox)
        paux->info.idLinha = paux->eprox->info.idLinha + 1;
}

int adicionarDepoisdaCorrente(Tlista *editor, char comando[])
{
    TAtomo *pnovo = (TAtomo *)malloc(sizeof(TAtomo));
    if (pnovo == NULL)
        return NO_SPACE;
    copiar(comando, pnovo->info.frase);

    TAtomo *pcorrent = NULL, *pd = editor->primeiro;
    while (pd != NULL && pcorrent != editor->linhaCorrent)
    {
        pcorrent = pd;
        pd = pd->dprox;
    }

    if (pcorrent == editor->ultimo)
    {
        editor->ultimo->dprox = pnovo;
        pnovo->eprox = editor->ultimo;
        editor->ultimo = pnovo;
    }

    else
    {
        pnovo->dprox = pcorrent->dprox;
        pnovo->eprox = pcorrent;
        pcorrent->dprox = pnovo;
        pd->eprox = pnovo;
    }

    editor->linhaCorrent = pnovo;
    editor->quantLinhas++;
    actualizarLinhas(editor);
    return OK;
}

int adicionarLinha(Tlista *editor, char comando[])
{
    TAtomo *pnovo = (TAtomo *)malloc(sizeof(TAtomo));
    if (pnovo == NULL)
        return NO_SPACE;
    copiar(comando, pnovo->info.frase);
    pnovo->dprox = NULL;
    if (editor->ultimo == NULL)
        pnovo->info.idLinha = 1;
    else
        pnovo->info.idLinha = editor->ultimo->info.idLinha + 1;

    if (vaziaLista(*editor))
        editor->primeiro = pnovo;
    else if (listaUnitaria(editor))
    {
        editor->primeiro->dprox = pnovo;
        pnovo->eprox = editor->primeiro;
    }
    else
    {
        //analisar
        editor->ultimo->dprox = pnovo;
        pnovo->eprox = editor->ultimo;
    }

    editor->ultimo = pnovo;
    editor->quantLinhas++;
    return OK;
}

void cmd_ultimo(Tlista *lista)
{
    if (!vaziaLista(*lista))
        printf("%d\n", lista->ultimo->info.idLinha);
    else
        printf("ERRO: Editor vazio!\n");
}

void imprimirLista(Tlista *lista)
{
    if (!vaziaLista(*lista))
    {
        printf("-----------------------------------\n");
        for (TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->dprox)
        {
            if (paux == lista->linhaCorrent)
                printf("%d → %s", paux->info.idLinha, paux->info.frase);
            else
                printf("%d %s", paux->info.idLinha, paux->info.frase);
        }

        printf("-----------------------------------\n");
    }
    else
        printf("ERRO: Editor vazio!\n");
}

void funcao_teste(Tlista *editor)
{
    TAtomo *p = NULL;
    for (TAtomo *paux = editor->primeiro; paux != NULL; paux = paux->dprox)
    {
        if (paux == editor->linhaCorrent)
        {
            p = paux->dprox;
            break;
        }
    }
    printf("o dpt da linha corrent: %s\n", p->info.frase);
}
