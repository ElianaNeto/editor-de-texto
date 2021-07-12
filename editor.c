#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "editor.h"

void error(int errorCode)
{
    char *errorMessages[] = {
        "ERRO: QUANTIDADE DE PARAMETROS INSUFICIENTES",
        "ERRO: FALTA VIRGULA",
        "ERRO: LINHA DE ÍNICIO DEVE SER MENOR COM RELAÇÃO A LINHA DE TERMINOU\nExemplo: $remover 1, 2",
        "ERRO: NÃO EXISTE A VIRGULA NO COMANDO",
        "ERRO: NÃO TEM ESPAÇO NO COMANDO E DEVE EXISTIR",
        "ERRO: LINHA NÃO VÁLIDA, LINHA NÃO VÁLIDA, LINHA NÃO MAIOR QUE 0",
        "ERRO: REFERÊNCIA DA LINHA DE ÍNICIO MAIOR QUE A FINAL",
        "ERRO: PRIMEIRO PARAMETRO NÃO PASSADO",
        "ERRO: QUANTIDADE DE PARAMETROS INSUFICIENTES",
        "ERRO: PRIMEIRO PARAMETRO NÃO PASSADO",
        "ERRO: QUANTIDADE DE PARAMETROS INVÁLIDOS",
        "ERRO: FALTA PARAMETROS PARA O COMANDO",
        "ERRO: DELIMITADORES INCONSCISTENTE",
        "ERRO: PARAMETROS ENVIADOS INSUFICIENTES",
        "ERRO: NÃO EXISTE LINHA CORRENTE VÁLIDA",
        "ERRO: LINHA COM A QUANTIDADE MÁXIMA DE CARACTERES ATINGIDA",
        "ERRO: PARAMETROS INSUFICIENTES",
        "ERRO: LINHA NÃO EXISTE",
        "ERRO: LINHAS FORA DO FORA DO NÚMERO ACTUAL DE LINHAS NO EDITOR DE TEXTO:",
        "ERRO: Pilha nao inicializada"}; //19

    printf("\n%s\n", errorMessages[errorCode]);
}

void warning(int warningCode)
{
    char *warningsMessages[] = {
        "AVISO: A LINHA ACTUAL JÁ ESTA SELECIONADA",
        "AVISO: EDITOR DE TEXTO VAZIO",
        "AVISO: PALAVRA NÃO ENCONTRADA",
        "AVISO: SEM ESPACO",
        "AVISO: PILHA VAZIA"};

    printf("\n%s\n", warningsMessages[warningCode]);
}

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
        res = res * 10 + str[i] - '0';

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

    if (compararRec(cmd, "prninv\0", 0) == 0)
        return CMD_INV;

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
                if (fimPrint <= editor->quantLinhas)
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
                }
                else
                    printf("ERRO: O fim da impressao deve ser %d!\n", editor->quantLinhas);
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
    //printf("{%d , %d} \n", inicPrint, fimPrint);

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
                            //printf("esse i:%d\n", i);
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

        if (paux == lista.linhaCorrent)
            printf("→ %d ", paux->info.idLinha);
        else
            printf("%d ", paux->info.idLinha);

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
    char st3[20]; //oldString
    char st4[20];
    char st5[20]; //newString
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
        if (comando[k] != '\0' && comando[k] != ' ')
        {
            oldString[k - j - 1] = comando[k];
        }
        else
        {
            break;
        }
    }
    oldString[k - j - 1] = '\0';
    //st3[comprimentoSt(st3) - 1] = '\0';

    while (comando[k] == ' ')
    {
        k++;
    }
    k = k - 1;

    for (l = k + 1; l < comprimento; l++)
    {
        if (comando[l] == '%')
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
    //st4[comprimentoSt(st4) - 1] = '\0';

    while (comando[l] == ' ')
    {
        l++;
    }
    l = l - 1;

    for (m = l + 1; m < comprimento; m++)
    {
        if (comando[m] != '\0' && comando[m] != ' ')
        {
            newString[m - l - 1] = comando[m];
        }
        else
        {
            break;
        }
    }
    newString[m - l - 1] = '\0';
    //fflush(stdin);
    //st5[comprimentoSt(st5) - 1] = '\0';

    while (comando[m] == ' ')
    {
        m++;
    }
    m = m - 1;

    for (n = m + 1; n < comprimento; n++)
    {
        if (comando[n] != '\0' && comando[n] != ' ')
        {
            st6[n - m - 1] = comando[n];
        }
        else
        {
            break;
        }
    }
    st6[n - m - 1] = '\0';
    //fflush(stdin);
    st6[comprimentoSt(st6) - 1] = '\0';
    //printf("{%s}\n", st1);
    //printf("{%s}\n", st2);
    printf("{%s}\n", oldString); //st3
    //printf("{%s}\n", st4);
    printf("{%s}\n", newString); //st4
    //printf("{%s}\n", st6);
}

void arrastarStringFim(char *str, int pos, int size)
{
    while (size >= pos)
    {
        str[pos] = str[pos + 1];
        pos++;
    }
}

void arrastarString(char *str, int pos, int size)
{
    while (size >= pos)
    {
        str[size + 1] = str[size];
        size--;
    }
}

void afastarCaracteres(char *str, int qtd, int ini, int op)
{
    int size = comprimentoSt(str);
    //str[size+qtd]='\0';
    int i = 1;
    while (i <= qtd)
    {

        if (op == 1)
        {
            //arrastar e deixar espaco para nova string
            arrastarString(str, ini, size);
            size++;
        }
        if (op == 2)
        {
            //remover caracteres
            arrastarStringFim(str, ini, size);
        }

        i++;
    }
}

int alterarFrase(Tlista lista, char *substring, char *frase)
{
    // alterar apenas a linha corrente : esta na descricao do projecto
    int pos;
    int aux = 0;
    int cont = 0;

    int sizeF = comprimentoSt(frase);
    int sizeS = comprimentoSt(substring);
    TAtomo *paux = lista.linhaCorrent;
    if (paux == NULL)
    {
        return NOT_FOUND;
    }
    int tam = 0;
    int encontrei = 0;

    for (int i = 0; paux->info.frase[i] != '\0'; i++)
    {
        cont = 0;
        pos = i;
        for (int j = 0; j < sizeS; j++, pos++)
        {
            //substitui o break - o prof nao gosta dele
            if (paux->info.frase[pos] == '\0')
                break;
            //se for igual vou somando "cont"
            if (paux->info.frase[pos] != substring[j])
                break;
            else
                cont++;
        }
        //se encontrei a substring completa, vou alterar
        if (cont == sizeS)
        {
            pos = i;
            // o limite da busca e sempre a 2* string
            tam = sizeF + i;
            //antes de substituir devo analizar os tamanhos das strings
            if (sizeF == 0)
                afastarCaracteres(paux->info.frase, sizeS, i, 2);
            else if (sizeF > sizeS)
                afastarCaracteres(paux->info.frase, sizeF - sizeS, sizeS + i, 1);
            else if (sizeF < sizeS)
                afastarCaracteres(paux->info.frase, sizeS - sizeF, sizeF + i, 2);
            aux = 0;
            //onde adiciono a segunda frase
            while (pos < tam)
            {
                paux->info.frase[pos] = frase[aux];
                pos++;
                aux++;
            }
            // a ideia e pular os caracteres alterados e so
            //verificar os restantes
            //espero que entendam!
            if (sizeF != 0)
                i = (i + sizeF) - 1;
            encontrei = 1;
        }
    }
    //aqui verifico se encontrei pelo menos uma vez ou nao
    if (encontrei == 0)
        return NOT_FOUND;
    else
        return OK;
}

void cmd_alterar(Tlista *editor, char comando[])
{
    char oldString[LINHA_TAM] = "";
    char newString[LINHA_TAM] = "";
    separarALTNOVO(oldString, newString, comando);
    //separarAlterar(oldString, newString, comando);

    if (!vaziaLista(*editor))
    {
        if (editor->linhaCorrent != NULL)
        {
            //alterarFrase(*editor, oldString, newString);
            alterarFrase1(editor, oldString, newString);
        }
        else
            printf("ERRO: Linha corrente vazia!\n");
    }
    else
        printf("ERRO: Editor vazio!\n");
}

void pegarPalavrasAlterar(char st[], char oldString[], char newString[])
{
    int comprimento = comprimentoSt(st);
    int i = 0, j = 0;
    char st1[60], st2[60];

    for (i = 1; i < comprimento; i++)
    {
        if (st[i] != '%')
        {
            oldString[i - 1] = st[i];
        }
        else
        {
            break;
        }
    }
    oldString[i] = '\0';

    for (j = i + 1; j < comprimento; j++)
    {
        if (st[j] != '%')
        {
            newString[j - i - 1] = st[j];
        }
        else
        {
            break;
        }
    }
    newString[j - i - 1] = '\0';

    //printf("{%s}\n", oldString);
    //printf("{%s}\n", newString);
}

void ckecarParametros(char st[])
{
    int comprimento = comprimentoSt(st);
    int delimitador = 0;
    for (int i = 0; i < comprimento; i++)
    {
        if (st[i] == '%')
            delimitador++;
    }

    if (delimitador < 3)
        printf("Delimitador em falta\n");
    else if (delimitador > 3)
        printf("Delimitador em escesso\n");
}

void separarALTNOVO(char oldString[], char newString[], char comando[])
{
    int i = 0, j = 0;
    char st1[60];
    char st2[60];
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

    for (j = i + 1; j < comprimento; j++)
    {
        if (comando[j] != ' ')
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

    //printf("{%s}\n", st1);
    //printf("{%s}\n", st2);
    ckecarParametros(st2);
    pegarPalavrasAlterar(st2, oldString, newString);
}

int fStrStr(char *str, char *strSub)
{
    int i = 0, j = 0;
    int nTemp = i;
    int nStrLen = strlen(str);
    int nStrSubLen = strlen(strSub);
    for (i = 0; i < nStrLen - nStrSubLen; i++)
    {
        nTemp = i;
        for (j = 0; j < nStrSubLen; j++)
        {

            if (str[nTemp] == strSub[j])
            {
                if (j == nStrSubLen - 1)
                    return 1;
                nTemp++;
            }
            else
                break;
        }
    }

    return 0;
}

int find(char *str, char *strSub)
{
    int i = 0;
    int j = 0;
    while (str[i] != '\0')
    {
        if (str[i] == strSub[0])
        {
            j = 1;
            while (strSub[j] != '\0' && str[j + 1] != '\0' || strSub[j] == str[j + 1])
            {
                j++;
            }
            if (strSub[j] == '\0')
            {
                printf("Sub-string found. %d", i);
                return i;
            }
        }
        i++;
    }
    return -1;
}

void alterarFrase1(Tlista *lista, char oldString[], char newString[])
{
    int cmOld = comprimentoSt(oldString);
    int cmNew = comprimentoSt(newString);
    int a = 0;
    TAtomo *paux = lista->linhaCorrent;

    int comprimentoCorent = comprimentoSt(paux->info.frase);
    comprimentoCorent = comprimentoCorent + 3;
    //printf("o comprimento da corwn %d\n", comprimentoCorent);
    //printf("o comprimento da corwn %d\n", cmNew);

    int findAt = find(paux->info.frase, oldString);

    if (paux != NULL)
    {
        if (findAt != -1)
        {
            //printf("Sub-string found.\n");
            while (comprimentoCorent >= findAt)
            {
                paux->info.frase[comprimentoCorent + 1] = paux->info.frase[comprimentoCorent];
                comprimentoCorent--;
            }

            printf("%s\n", paux->info.frase);

            for (int i = findAt; i <= findAt + cmNew - 1; i++, a++)
            {
                paux->info.frase[i] = newString[a];
            }
        }
        else
            printf("Sub-string nao encontrada\n");
    }
    else
        printf("");

    //printf("%c\n", paux->info.frase);
}

void cmd_prninv(Tlista *editor, char comando[])
{
    char st1[30];
    char st2[30];
    char st3[30];
    char st4[30];

    separar4(st1, st2, st3, st4, comando);
    int startVirgula = encontrarVirgula(comando);
    int inicPrint = converteStringToInte(st2);
    int fimPrint = converteStringToInte(st4);
    //printf("{%d , %d} \n", inicPrint, fimPrint);
    int inicio = inicPrint;

    if (!vaziaLista(*editor))
    {
        printf("-----------------------------------\n");

        if (startVirgula != -1)
        {
            if (inicPrint >= 1 && inicPrint <= editor->quantLinhas)
            {
                if (fimPrint <= editor->quantLinhas)
                {
                    for (int i = 0; i < fimPrint; i++)
                    {
                        for (TAtomo *paux = editor->primeiro; paux != NULL; paux = paux->dprox)
                        {
                            if (paux->info.idLinha == inicio)
                            {
                                if (paux == editor->linhaCorrent)
                                    printf("%d → %s", paux->info.idLinha, paux->info.frase);
                                else
                                    printf("%d %s", paux->info.idLinha, paux->info.frase);
                                inicio--;
                            }
                        }
                    }
                }
                else
                    printf("ERRO: qtidades de linhas escessiva!\n");
            }
            else
                printf("ERRO:!\n");
        }
        else
            printf("ERRO: Falta ',' \n");
        printf("-----------------------------------\n");
    }
    else
        printf("ERRO: Editor vazio!\n");
}

int iniciarPilha(TPilha *pilha)
{
    //pilha->pilha = (TItem *)malloc(sizeof(TItem));
    pilha->pTopo = NULL;
    //if (pilha->pilha == NULL)
    // //error(19);
    return OK;
}

int vaziaPilha(TPilha pilha)
{
    return pilha.pTopo == NULL;
}

int empilhar(TPilha *pilha, char *comando)
{
    PAtomo *pnovo = (PAtomo *)malloc(sizeof(PAtomo));
    if (pnovo == NULL)
        warning(3);
    if (vaziaPilha(*pilha))
        pnovo->pant = NULL;
    else
        pnovo->pant = pilha->pTopo;
    copiar(comando, pnovo->info.frase);
    pilha->pTopo = pnovo;

    return OK;
}

int desempilhar(TPilha *pilha)
{
    if (vaziaPilha(*pilha))
        warning(4);
    PAtomo *pdel = pilha->pTopo;
    pilha->pTopo = pilha->pTopo->pant;
    return OK;
}

int undo(Tlista *editor, TPilha *pilha)
{
}
