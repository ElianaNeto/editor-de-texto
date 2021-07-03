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
    limparTerminal();

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
                cmd_remover(editor, comando);
                break;

            case CMD_LINHA: // linha m
                insertMode = 0;
                cmd_linha(editor, comando);
                break;

            case CMD_LOCALIZAR: // localizar %x
                insertMode = 0;
                cmd_localizar(editor, comando);
                break;

            case CMD_ALTERAR: // alterar %x %y %
                insertMode = 0;
                printf("ALTERAR\n");
                cmd_alterar(editor,comando);
                break;

            case CMD_ULTIMO: // ultimo (to test)
                insertMode = 0;
                cmd_ultimo(editor);
                break;

            case CMD_IMPRIMIR: // imprimir m, n
                insertMode = 0;
                cmd_imprimir(editor, comando);
                break;

            case CMD_FIM: // fim
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
