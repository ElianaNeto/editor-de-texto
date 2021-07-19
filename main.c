#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

//→ ->
int main()
{
    Tlista *editor = (Tlista *)(malloc(sizeof(Tlista)));
    TPilha *pilha = (TPilha *)(malloc(sizeof(TPilha)));

    int startMode = 1;
    int insertMode = 0;
    inicEditor(editor);
    iniciarPilha(pilha);
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
                //printf("REMOVENDO\n");
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
                //printf("ALTERAR\n");
                cmd_alterar(editor, comando);
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
                //startMode = 0;
                //insertMode = 0;
                cmdFim(&startMode, &insertMode);
                break;

            case CMD_INV: // prninv m, n
                insertMode = 0;
                cmd_prninv(editor, comando);
                break;

            case CMD_DEL: // deletar %x%
                insertMode = 0;
                printf("DELETAR\n");
                cmdDeletar(editor, comando, pilha);
                break;

            case CMD_UNDO: //undo
                printf("UNDO\n");
                insertMode = 0;
                /*empilhar(pilha, "ola");
                empilhar(pilha, "elia");
                empilhar(pilha, "t");
                desempilhar(pilha);*/
                printf("%s \n", pilha->pTopo->info.frase);
                break;

            default:
                insertMode = 0;
                error(21);
                break;
            }
        }

        else
            error(20);
    }

    //fflush(stdin);
    return 0;
}
