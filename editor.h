#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include "structs.h"

void imprimirEditor(DescLinhas *d, Cursor *c) {
    if (d == NULL || d->linhaTopoTela == NULL) {
        printf("Editor vazio\n");
        return;
    }

    Linha *lin = d->linhaTopoTela;
    int count = 0;

    while (lin != NULL && count < d->alturaTela) {
        Letra *let = lin->inicioL;

        // cursor no início
        if (lin == c->linha && c->letra == NULL) {
            printf("|");
        }

        while (let != NULL) {
            printf("%c", let->letra);

            if (lin == c->linha && c->letra == let) {
                printf("|");
            }

            let = let->prox;
        }

        printf("\n");

        lin = lin->botton;
        count++;
    }
}

/*
void imprimirEditor(DescLinhas *d, Cursor *c) {
    if (d != NULL && d->inicio != NULL) {
        Linha *lin = d->inicio;

        while (lin != NULL) {
            Letra *let = lin->inicioL;

            // Cursor no início da linha
            if (lin == c->linha && c->letra == NULL) {
                printf("|");
            }

            while (let != NULL) {
                printf("%c", let->letra);

                // Cursor depois dessa letra
                if (lin == c->linha && c->letra == let) {
                    printf("|");
                }

                let = let->prox;
            }

            printf("\n");
            lin = lin->botton;
        }
    } else {
        printf("Editor sem conteudo.\n");
    }
}


void imprimirEditor(DescLinhas *d) {
    if (d != NULL && d->inicio != NULL) {
        Linha *lin = d->inicio;
        while (lin != NULL) {
            Letra *let = lin->inicioL;
            while (let != NULL) {
                printf("%c", let->letra);
                let = let->prox;
            }
            printf("\n");
            lin = lin->botton;
        }
    } else {
        printf("Editor sem conteudo.\n");
    }
}*/

// Formatacao do F5 (para haver recuo(modificacao na estrutura do DescLinhas))
void exibirFormatado(DescLinhas *d) {
    if (d != NULL && d->inicio != NULL) {
        Linha *lin = d->inicio;
        int novoParagrafo = 1; 
        int i;

        while (lin != NULL) {
            Letra *let = lin->inicioL;
            Letra *ultima = NULL;
            int colAtual = 0; // Come�amos a contar do zero em cada linha

            // 1. Recuo Esquerdo base para todas as linhas 
            for (i = 0; i < d->recuoEsq; i++) {
                printf(" ");
                colAtual++;
            }

            // 2. Recuo extra apenas se for in�cio de par�grafo 
            if (novoParagrafo == 1) {
                for (i = 0; i < d->primLinha; i++) {
                    printf(" ");
                    colAtual++;
                }
                novoParagrafo = 0;
            }

            // 3. Imprime as letras respeitando o limite da coluna 
            while (let != NULL && colAtual < d->recuoDir) {
                printf("%c", let->letra);
                ultima = let;
                let = let->prox;
                colAtual++;
            }
            printf("\n");

            // 4. Verifica pontua��o para definir o pr�ximo paragrafo 
            if (ultima != NULL) {
                if (ultima->letra == '.' || ultima->letra == '!' || ultima->letra == '?') {
                    novoParagrafo = 1;
                }
            }
            lin = lin->botton;
        }
    } else {
        printf("\nO editor nao possui texto carregado.\n");
    }
}

#endif
