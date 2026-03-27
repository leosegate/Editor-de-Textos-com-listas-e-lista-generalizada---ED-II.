/* [LISTA A SER REALIZADA] ��� [TEMPO TOTAL = 21:32 A ]
//[]home = � coloca o cursor no in�cio da linha corrente (dada pelo ponteiro linha)
//[]End � coloca o cursor no final da linha corrente (dada pelo ponteiro linha);
//[]Page Up � rolagem de uma tela para cima;
//[]Page Down � rolagem de uma tela para baixo;
//[]Back Space � apaga um caracter (� esquerda do cursor);
//[]Del � apaga um caracter (sob o cursor);
//[]Insert � ligado: Insere novos caracteres; desligado: escreve em cima dos caracteres existentes.
//[]F10 � Negrito: o caracter � (21 da tabela ASCII) indica in�cio ou fim de uma palavra ou trecho em Negrito. 

//[]F2 Abrir: Uma fun��o para ler do arquivo texto e carregar para a estrutura do editor (para efeito de simplifica��o, cada linha do arquivo n�o dever� ser maior que 79 caracteres)
//[]F3 Salvar: Uma fun��o para percorrer toda a estrutura do editor e gravar no arquivo texto;
//[]F5 Exibir: Uma fun��o para exibir o texto na tela a partir da estrutura do editor (listas din�micas) de maneira formatada de acordo com a configura��o pr�via: Primeira Linha, Recuo Esquerdo e Recuo Direito;

//[]Uma fun��o para buscar na lista generalizada de palavras
//[]Uma fun��o para inserir na lista generalizada de palavras

//[]verificar a fun��o AUTO COMPLETAR NO FINAL DO PDF


[===   OBSERVA��ES NECESS�RIAS PARA O FUNCIONAMENTO   ===]
// NO MAXIMO 79 CARACTERES POR LINHA!!!
// FINAL DA LINHA � FEITO POR "." "!" OU "?"
// SE A PALAVRA PASSAR DO TAMANHO LIMITE, ELE DEVE SER INSERIDO NA LINHA DE BAIXO
*/


#include <stdio.h>
#include "manipular_arquivo.h"
#include "editor.h"

int main() {
    char nomeArquivo[100];

    printf("Digite o nome do arquivo (ex: texto.txt): ");
    scanf("%s", nomeArquivo);

    DescLinhas *desc = lerArquivoTXT(nomeArquivo);

    if (desc == NULL) {
        printf("Erro ao ler arquivo.\n");
        return 1;
    }

    printf("\n===== CONTEUDO DO EDITOR =====\n\n");

    imprimirEditor(desc);
    getch();
    return 0;
}