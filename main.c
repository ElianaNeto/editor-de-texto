#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        if (ehComando == NOT_CMD && insertMode == 1)
        {
            if (editor->linhaCorrent == NULL)
            {
                // printf("Nao tem uma linha corrente \n");
                adicionarLinha(editor, comando);
            }
            else
            {
                novo(editor, comando);

                //adicionarDepoisdaCorrente(editor, comando);
                // printf("Tem uma linha corrente \n");
            }
        }
        else if (ehComando != NOT_CMD)
        {
            int startCommandIndex = ehComando;
            int commandCode = checkCommand(startCommandIndex, comando);

            switch (commandCode)
            {

            case CMD_INSERIR: // Inserir
                insertMode = 1;
                //printf("INSERINDO\n");
                break;

            case CMD_REMOVER: // remover m, n
                insertMode = 0;
                printf("REMOVENDO\n");
                break;

            case CMD_LINHA: // linha m
                insertMode = 0;
                //printf(" → LINHA\n");
                //comandoLinha(*editor, comando, 2);
                linha(editor, comando);
                break;

            case CMD_LOCALIZAR: // localizar %x
                insertMode = 0;
                printf("LOCALIZAR\n");
                break;

            case CMD_ALTERAR: // alterar %x %y %
                insertMode = 0;
                printf("ALTERAR\n");
                break;

            case CMD_ULTIMO: // ultimo (to test)
                insertMode = 0;
                printf("ULTIMO\n");
                cmd_ultimo(editor);
                break;

            case CMD_IMPRIMIR: // imprimir m, n
                insertMode = 0;

                imprimirLista(editor);
                funcao_teste(editor);
                break;

            case CMD_FIM: // fim
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
