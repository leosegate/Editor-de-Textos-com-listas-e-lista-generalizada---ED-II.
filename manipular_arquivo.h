#ifndef MANIPULAR_ARQUIVO_H
#define MANIPULAR_ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

// cria descritor vazio
DescLinhas* criarDescritor() {
    DescLinhas *d = (DescLinhas*) malloc(sizeof(DescLinhas));
    if (!d) return NULL;

    d->inicio = NULL;
    d->qntdLinhas = 0;

    return d;
}

// FUNÇÃO PRINCIPAL: lê arquivo txt e monta estrutura
DescLinhas* lerArquivoTXT(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return NULL;
    }

    DescLinhas *desc = criarDescritor();
    if (!desc) {
        fclose(f);
        return NULL;
    }

    char linhaTexto[80]; // respeitando limite do trabalho (79 + \0)

    while (fgets(linhaTexto, sizeof(linhaTexto), f)) {
		int i;
        Linhas *novaLinha = linhaEmBranco();
        if (!novaLinha) continue;

        for (i = 0; linhaTexto[i] != '\0' && linhaTexto[i] != '\n'; i++) {
            inserirLetra(novaLinha, linhaTexto[i]);
        }

        inserirLinha(desc, novaLinha);
    }

    fclose(f);
    return desc;
}

#endif
