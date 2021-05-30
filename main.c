#include <stdio.h>
#include <stdlib.h>
#include "editor.h"

//→ ->
int main()
{
    Tlista *editor = (Tlista *)(malloc(sizeof(Tlista)));
    int startMode = 1;
    int insertMode = 0;
    char comando[LINHA_TAM];

    while (startMode == 1)
    {
        // char comando[LINHA_TAM];
        scanf("%[^~]", comando); //%[^\n] -- /t delimitador
        int ehComando = ehComando(comando);

        /* code */
    }

    char comando1[LINHA_TAM];

    printf("\n---------\n");

    printf("%s", comando);
    int i = 0;
    int j = 0;
    int a = 0;
    while (comando[i] != '$')
    {
        comando1[i] = comando[i];
        i++;
    }

    while (comando[a] != '\0')
    {
        if (comando[a] == '\n')
            j++;
        a++;
    }
    if (comando[a] == '\0')
        j++;

    printf("\n---------\n");
    printf("%s\n", comando1);
    printf("%d j\n", j);
    //fflush(stdin);
    return 0;
}
