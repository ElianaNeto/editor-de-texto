#include <stdio.h>
#include <stdlib.h>
#include "editor.h"

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
    while (st1[i] != ' ' && st1[i] != '\n' )
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
        return 1;

    if (compararRec(cmd, "remover\0", 0) == 0)
        return 2;

    if (compararRec(cmd, "linha\0", 0) == 0)
        return 3;

    if (compararRec(cmd, "localizar\0", 0) == 0)
        return 4;

    if (compararRec(cmd, "alterar\0", 0) == 0)
        return 5;

    if (compararRec(cmd, "ultimo\0", 0) == 0)
        return 6;

    if (compararRec(cmd, "imprimir\0", 0) == 0)
        return 7;

    if (compararRec(cmd, "fim\0", 0) == 0)
        return 8;

    return -1;
}
