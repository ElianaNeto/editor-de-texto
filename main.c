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
                adicionarLinha(editor, comando);
            else
                adicionarDepoisdaCorrente(editor, comando);
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
                //remover(editor,2);
                cmd_remover(editor, comando);
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
                //imprimirLista(editor);
                imprimirNovo(editor, comando);
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

    //fflush(stdin);*/
    return 0;
}
