#include <stdio.h>
#include <stdlib.h>
#include "editor.h"

//→ ->
int main()
{
    Tlista *editor = (Tlista *)(malloc(sizeof(Tlista)));
    int startMode = 1;
    int insertMode = 0;
    inicEditor(editor);

    while (startMode == 1)
    {
        char comando[LINHA_TAM];
        fgets(comando, sizeof(comando), stdin);
        //scanf("%[^\n]", comando);
        int ehComando = verificarComando(comando);
        if (ehComando == -1 && insertMode == 1)
        {
            adicionarLinha(editor, comando);
            //printf("Momento para adicionar\n");
        }
        else if (ehComando != -1)
        {
            int startCommandIndex = ehComando;
            int commandCode = checkCommand(startCommandIndex, comando);

            switch (commandCode)
            {

            case 1: // Inserir
                insertMode = 1;
                //printf("INSERINDO\n");
                break;

            case 2: // remover m, n
                insertMode = 0;
                printf("REMOVENDO\n");
                break;

            case 3: // linha m
                insertMode = 0;
                printf("LINHA\n");
                break;

            case 4: // localizar %x
                insertMode = 0;
                printf("LOCALIZAR\n");
                break;

            case 5: // alterar %x %y %
                insertMode = 0;
                printf("ALTERAR\n");
                break;

            case 6: // ultimo (to test)
                insertMode = 0;
                printf("ULTIMO\n");
                break;

            case 7: // imprimir m, n
                insertMode = 0;
               // printf("IMPRIMIR\n");
                imprimirLista(editor);
                break;

            case 8: // fim
                //printf("FIM\n");
                startMode = 0;
                insertMode = 0;
                break;

            default:
                insertMode = 0;
                printf("ERRO: Comando inválido!\n");
                break;
            }
        }

        else
        {
            printf("\nERRO: Comandos devem começar com $\n");
        }
    }

    /*char comando1[LINHA_TAM];

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
    // printf("eh comando%d\n", ehComando);
    //fflush(stdin);*/
    return 0;
}
