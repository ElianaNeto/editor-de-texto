# Editor de texto

Editor de texto usando C, com estrutura de dados(Lista duplamente Ligadas).

#### Formas de executar o projecto (1 ou 2)

1. Faça `./executar.sh` na linha de comando.
2. Faça `make` na linha de comando.

#### Sobre o editor texto

Editor de texto, baseado em linha de comando. Por definição, um editor de texto é um programa que processa texto, linha por linha. Suponhamos que cada linha tenha exactamente 80 caracteres. Cada comando de edição começa com o caracter cifrão (e nenhuma outra linha começa com esse caracter. Este editor de texto possui oito comandos:

1. `$inserir`: Inserir uma porção de texto depois da linha corrente. A linha corrente é indicada pelo caracter “→”.
2. `$remover m,n`: Cada linha no texto, entre as linhas m e n, inclusive, devem ser removidas. Se a linha corrente está nesse intervalo, a nova linha corrente deve ser a linha m-1
3. `$linha m`:A linha m deve tornar-se a linha corrente.
4. `$Localizar %x`:localizar no texto todas as ocorrências da cadeia de caracteres x
5. `$alterar %x %y %`:na linha corrente, cada ocorrência da cadeia x deve ser substituída pela cadeia y
6. `$último`: deve imprimir o número da última linha do texto. Por exemplo, dado o texto
7. `$imprimir m,n`: devem ser impressas todas as linhas do texto, e o número de linhas, das linhas m até n, inclusive n.
8. `$fim`:termina a execução do editor de texto.
