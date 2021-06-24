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
        res = res * 10 + str[i] - '0';

    return sign * res;
}

int procurarLinhaCorrent(Tlista editor, int id)
{
    TAtomo *paux = editor.primeiro;
    while (paux != NULL && paux->info.idLinha != id)
        paux = paux->dprox;
    if (paux == NULL)
        return -1;
    return paux->info.idLinha;
}

void comandoLinha(Tlista editor, char comando[], int id)
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
}

void linha(Tlista *editor, char comando[])
{
    //→
    int tamanho = strlen(editor->linhaCorrent->info.frase);
    int id;
    comandoLinha(*editor, comando, id);
    int idAux = procurarLinhaCorrent(*editor, id);

    if (!vaziaLista(*editor))
    {
        if (editor->linhaCorrent != NULL)
        {
            if (editor->linhaCorrent->info.frase[0] == 'o')
                printf("t");
        }
    }
    else
    {
        printf("ERRO: Lista vazia!\n");
    }
}

int adicionarDepoisdaCorrente(Tlista *editor, char comando[])
{
    return OK;
}

int adicionarLinha(Tlista *editor, char comando[])
{
    TAtomo *pnovo = (TAtomo *)malloc(sizeof(TAtomo));
    if (pnovo == NULL)
        return NO_SPACE;
    copiar(comando, pnovo->info.frase);
    pnovo->dprox = NULL;
    pnovo->info.idLinha = 1;
    if (vaziaLista(*editor))
        editor->primeiro = pnovo;
    else if (listaUnitaria(editor))
    {
        editor->primeiro->dprox = pnovo;
        pnovo->eprox = editor->primeiro;
    }
    else
    {
        editor->ultimo->dprox = pnovo;
        pnovo->eprox = editor->ultimo;
    }

    editor->ultimo = pnovo;
    editor->quantLinhas++;
    editor->linhaCorrent = pnovo;
    return OK;
}

void imprimirLista(Tlista *lista)
{
    if (!vaziaLista(*lista))
    {
        for (TAtomo *paux = lista->primeiro; paux != NULL; paux = paux->dprox)
            printf("%s", paux->info.frase);
        //printf("\n");
    }
}
