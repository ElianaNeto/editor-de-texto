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

void getComand(char st[], char st1[])
{
}

int checkCommand(int startCommandIndex, char comando[])
{
    char cmd[LINHA_TAM];
    getComand(cmd, comando);
    if (compararRec(cmd, "INC", 0) == 0)
        return 1;
}
