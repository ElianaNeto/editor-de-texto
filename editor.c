#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

void limparTerminal()
{
    system("tput reset");
}

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

TAtomo *procurarLinha(Tlista editor, int id)
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

void cmd_linha(Tlista *editor, char comando[])
{
    //→

    int id = 0;
    comandoLinha(*editor, comando, &id);
    TAtomo *idAux = (TAtomo *)malloc(sizeof(TAtomo));
    idAux = procurarLinha(*editor, id);

    if (!vaziaLista(*editor))
    {
        if (idAux != NULL)
        {
            editor->linhaCorrent = idAux;
        }
        else
        {
            printf("ERRO: Linha %d não existe!\n", id);
        }
    }
    else
        printf("ERRO:Lista vazio\n");
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
    {
        editor->primeiro = pnovo;
        editor->ultimo = pnovo;
    }
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

int remover(Tlista *lista, int id)
{
    if (vaziaLista(*lista))
        return LIST_EMPTY;

    TAtomo *pdel = procurarLinha(*lista, id);
    if (pdel == NULL)
        return NOT_FOUND;
    if (pdel == lista->primeiro)
    {
        lista->primeiro = pdel->dprox;
        lista->primeiro->eprox = NULL;
    }
    else if (pdel == lista->ultimo)
    {
        lista->ultimo = pdel->eprox;
        lista->ultimo->dprox = NULL;
    }
    else
    {
        pdel->eprox->dprox = pdel->dprox;
        pdel->dprox->eprox = pdel->eprox;
    }

    free(pdel);
    lista->quantLinhas--;

    return OK;
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

int encontrarVirgula(char comando[])
{
    for (int i = 0; comando[i] != '\0'; i++)
    {
        if (comando[i] == ',')
        {
            return i;
            break;
        }
    }
    return -1;
}

int encontrarPercent(char comando[])
{
    for (int i = 0; comando[i] != '\0'; i++)
    {
        if (comando[i] == '%')
        {
            return i;
            break;
        }
    }
    return -1;
}

void separar4(char st1[], char st2[], char st3[], char st4[], char comando[])
{

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    int comprimento = comprimentoSt(comando);
    fflush(stdin);
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
        if (comando[j] != '\0' && comando[j] != ' ' && comando[j] != ',')
        {
            st2[j - i - 1] = comando[j];
        }
        else
        {
            break;
        }
    }
    st2[j - i - 1] = '\0';
    //st2[comprimentoSt(st2) - 1] = '\0';

    while (comando[j] == ' ')
    {
        j++;
    }
    j = j - 1;
    //multiplas virgulas ATT
    for (k = j + 1; k < comprimento; k++)
    {
        if (comando[k] == ',')
        {
            st3[k - j - 1] = comando[k];
        }
        else
        {
            break;
        }
    }
    st3[k - j - 1] = '\0';
    //st3[comprimentoSt(st3) - 1] = '\0';

    while (comando[k] == ' ')
    {
        k++;
    }
    k = k - 1;

    for (l = k + 1; l < comprimento; l++)
    {
        if (comando[l] != '\0' && comando[l] != ' ')
        {
            st4[l - k - 1] = comando[l];
        }
        else
        {
            break;
        }
    }
    st4[l - k - 1] = '\0';
    //fflush(stdin);
    st4[comprimentoSt(st4) - 1] = '\0';
}

void cmd_imprimir(Tlista *editor, char comando[])
{
    char st1[30];
    char st2[30];
    char st3[30];
    char st4[30];

    separar4(st1, st2, st3, st4, comando);
    int startVirgula = encontrarVirgula(comando);

    int inicPrint = converteStringToInte(st2);
    int fimPrint = converteStringToInte(st4);

    if (!vaziaLista(*editor))
    {
        printf("-----------------------------------\n");

        if (startVirgula != -1)
        {
            if (inicPrint >= 1)
            {
                if (inicPrint <= fimPrint && fimPrint <= editor->quantLinhas)
                {
                    for (int i = inicPrint; i <= fimPrint; i++)
                    {
                        for (TAtomo *paux = editor->primeiro; paux != NULL; paux = paux->dprox)
                        {
                            if (paux->info.idLinha == i)
                            {
                                if (paux == editor->linhaCorrent)
                                    printf("%d → %s", paux->info.idLinha, paux->info.frase);
                                else
                                    printf("%d %s", paux->info.idLinha, paux->info.frase);
                            }
                        }
                    }
                }
                else
                    printf("ERRO: Inicio e fim de impressao invalidos!\n");
            }
            else
                printf("ERRO: Inicio de impressao invalida!\n");
        }
        else
            printf("ERRO: Falta ',' \n");
        printf("-----------------------------------\n");
    }
    else
        printf("ERRO: Editor vazio!\n");

    //printf("%d , %d", inicPrint, fimPrint);
    //printf("comprimento %d \n", comprimentoSt(st2));
    //printf("{%s}\n", st1);
    //printf("{%s}\n", st2);
    //printf("{%s}\n", st3);
    //printf("{%s}\n", st4);
    //printf("%d \n", *id);
}

void cmd_remover(Tlista *editor, char comando[])
{
    char st1[30];
    char st2[30];
    char st3[30];
    char st4[30];

    separar4(st1, st2, st3, st4, comando);
    int startVirgula = encontrarVirgula(comando);
    int inicPrint = converteStringToInte(st2);
    int fimPrint = converteStringToInte(st4);
    printf("{%d , %d} \n", inicPrint, fimPrint);

    if (!vaziaLista(*editor))
    {
        if (startVirgula != -1)
        {
            if (inicPrint >= 1)
            {
                if (inicPrint <= fimPrint && fimPrint <= editor->quantLinhas)
                {
                    if (inicPrint == 1 && fimPrint == editor->quantLinhas)
                        inicEditor(editor);

                    else
                    {
                        for (int i = inicPrint; i <= fimPrint; i++)
                        {
                            printf("esse i:%d\n", i);
                            remover(editor, i);
                        }

                        actualizarLinhas(editor);
                    }
                }
                else
                    printf("ERRO:!\n");
            }
            else
                printf("ERRO:!\n");
        }
        else
            printf("ERRO: Falta ',' \n");
    }
    else
        printf("ERRO: Editor vazio!\n");
}

void separarLocalizar(char st1[], char st2[], char st3[], char comando[])
{

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    int comprimento = comprimentoSt(comando);
    fflush(stdin);
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
        if (comando[j] == '%')
        {
            st2[j - i - 1] = comando[j];
        }
        else
        {
            break;
        }
    }
    st2[j - i - 1] = '\0';
    //st2[comprimentoSt(st2) - 1] = '\0';

    while (comando[j] == ' ')
    {
        j++;
    }
    j = j - 1;
    //multiplas virgulas ATT
    for (k = j + 1; k < comprimento; k++)
    {
        if (comando[k] != ' ')
        {
            st3[k - j - 1] = comando[k];
        }
        else
        {
            break;
        }
    }
    st3[k - j - 1] = '\0';
    st3[comprimentoSt(st3) - 1] = '\0';

    //printf("{%s}\n", st1);
    //printf("{%s}\n", st2);
    //printf("{%s}\n", st3);
}

void localizarFrase(Tlista lista, char *frase)
{
    printf("-----------------------------------\n");
    int pos;
    int cont = 0;
    int size = comprimentoSt(frase);
    for (TAtomo *paux = lista.primeiro; paux != NULL; paux = paux->dprox)
    {
        //Para imprimir os tracos - ou ->
        if (paux == lista.linhaCorrent)
            printf("→ ");
        //else
        // printf("\n%d - ", paux->info.idLinha);
        //percorrer cada frase
        for (int i = 0; paux->info.frase[i] != '\0'; i++)
        {
            cont = 0;
            pos = i;
            //percorrer cada letra da frase
            for (int j = 0; j < size; j++, pos++)
            {
                if (paux->info.frase[pos] == '\0')
                    break;
                //se for igual vou somando "cont"
                if (paux->info.frase[pos] != frase[j])
                    break;
                else
                    cont++;
            }
            //se encontrei a substring completa, vou pintar
            if (cont == size)
            {
                pos = i;
                while (pos < size + i)
                {
                    printf(COLOR);
                    printf("%c", paux->info.frase[pos]);
                    printf(NO_COLOR);
                    pos++;
                }
                i = (i + size) - 1;
                //caso contrario vou imprimir o caracter daquela posicao [i]
            }
            else
                printf("%c", paux->info.frase[i]);
        }
        //printf("\n");
    }
    printf("-------------------------------------\n");
}

void cmd_localizar(Tlista *editor, char comando[])
{
    char st1[30];
    char st2[30];
    char fraseLocalizar[30];

    separarLocalizar(st1, st2, fraseLocalizar, comando);

    int startPercent = encontrarPercent(comando);

    if (!vaziaLista(*editor))
    {
        if (startPercent != -1)
        {
            localizarFrase(*editor, fraseLocalizar);
        }
        else
            printf("ERRO: Parametro em falta \n");
    }
    else
        printf("ERRO: Editor vazio!\n");
}

void separarAlterar(char oldString[], char newString[], char comando[])
{
    char st1[20];
    char st2[20];
    char st3[20];
    char st4[20];
    char st5[20];
    char st6[20];

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    int n = 0;

    int comprimento = comprimentoSt(comando);
    fflush(stdin);
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
        if (comando[j] != '\0' && comando[j] != ' ' && comando[j] != ',')
        {
            st2[j - i - 1] = comando[j];
        }
        else
        {
            break;
        }
    }
    st2[j - i - 1] = '\0';
    //st2[comprimentoSt(st2) - 1] = '\0';

    while (comando[j] == ' ')
    {
        j++;
    }
    j = j - 1;
    //multiplas virgulas ATT
    for (k = j + 1; k < comprimento; k++)
    {
        if (comando[k] == ',')
        {
            st3[k - j - 1] = comando[k];
        }
        else
        {
            break;
        }
    }
    st3[k - j - 1] = '\0';
    //st3[comprimentoSt(st3) - 1] = '\0';

    while (comando[k] == ' ')
    {
        k++;
    }
    k = k - 1;

    for (l = k + 1; l < comprimento; l++)
    {
        if (comando[l] != '\0' && comando[l] != ' ')
        {
            st4[l - k - 1] = comando[l];
        }
        else
        {
            break;
        }
    }
    st4[l - k - 1] = '\0';
    //fflush(stdin);
    st4[comprimentoSt(st4) - 1] = '\0';

    while (comando[l] == ' ')
    {
        l++;
    }
    l = l - 1;

    for (m = l + 1; m < comprimento; m++)
    {
        if (comando[m] != '\0' && comando[m] != ' ')
        {
            st4[m - l - 1] = comando[m];
        }
        else
        {
            break;
        }
    }
    st5[m - l - 1] = '\0';
    //fflush(stdin);
    //st5[comprimentoSt(st4) - 1] = '\0';

    while (comando[l] == ' ')
    {
        m++;
    }
    m = m - 1;

    for (n = m + 1; n < comprimento; n++)
    {
        if (comando[n] != '\0' && comando[n] != ' ')
        {
            st4[n - m - 1] = comando[n];
        }
        else
        {
            break;
        }
    }
    st5[n - m - 1] = '\0';
    //fflush(stdin);
    st5[comprimentoSt(st4) - 1] = '\0';
    printf("{%s}\n", st1);
    printf("{%s}\n", st2);
    printf("{%s}\n", st3);
    printf("{%s}\n", st4);
    printf("{%s}\n", st5);
    printf("{%s}\n", st6);
}

void cmd_alterar(Tlista *editor, char comando[])
{
    char oldString[LINHA_TAM];
    char newString[LINHA_TAM];

    separarAlterar(oldString, newString, comando);

    if (!vaziaLista(*editor))
    {
        if (editor->linhaCorrent != NULL)
        {
            printf("Ola mundo!\n");
        }
        else
            printf("ERRO: Linha corrente vazia!\n");
    }
    else
        printf("ERRO: Editor vazio!\n");
}
