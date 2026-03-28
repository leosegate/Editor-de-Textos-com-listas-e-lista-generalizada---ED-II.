#ifndef MANIPULAR_ARQUIVO_H
#define MANIPULAR_ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funcoes.h"

DescLinhas* criarDescritor() {
    DescLinhas *d = (DescLinhas*)malloc(sizeof(DescLinhas));
    if (d != NULL) {
        d->inicio = NULL;
        d->qntdLinhas = 0;
    }
    return d;
}

DescLinhas* lerArquivoTXT(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    DescLinhas *desc = NULL;

    if (f != NULL) {
        desc = criarDescritor();
        if (desc != NULL) {
            char buffer[81]; 
            while (fgets(buffer, sizeof(buffer), f)) {
                Linhas *nova = linhaEmBranco();
                if (nova != NULL) {
                    int i = 0;
                    while (buffer[i] != '\0' && buffer[i] != '\n' && i < 79) {
                        inserirLetra(nova, buffer[i]);
                        i++;
                    }
                    inserirLinha(desc, nova);
                }
            }
        }
        fclose(f);
    } else {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
    }
    return desc;
}

void salvarArquivoTXT(const char *nomeArquivo, DescLinhas *d) {
    if (d != NULL) {
        FILE *f = fopen(nomeArquivo, "w");
        
        if (f != NULL) {
            Linhas *lin = d->inicio;
            
            while (lin != NULL) {
                Letra *let = lin->inicioL;
                
                while (let != NULL) {
                    fprintf(f, "%c", let->letra);
                    let = let->prox;
                }
                
                fprintf(f, "\n");
                lin = lin->botton;
            }
            
            fclose(f);
            printf("\nArquivo salvo com sucesso!");
        } else {
            printf("\nErro ao criar o arquivo para salvar.");
        }
    }
}

#endif
