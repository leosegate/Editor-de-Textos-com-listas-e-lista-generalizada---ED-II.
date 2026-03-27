#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include "structs.h"

// imprime todo o conteúdo do editor
void imprimirEditor(DescLinhas *d) {
    if (d == NULL || d->inicio == NULL) {
        printf("Editor vazio\n");
        return;
    }

    Linhas *linha = d->inicio;

    while (linha != NULL) {
        Letra *letra = linha->inicioL;

        while (letra != NULL) {
            printf("%c", letra->letra);
            letra = letra->prox;
        }

        printf("\n");
        linha = linha->botton;
    }
}

#endif