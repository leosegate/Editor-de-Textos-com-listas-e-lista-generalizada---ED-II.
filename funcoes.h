#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void freeLetras(Linhas**L) {
	Letra *letra, *aux;
	if(*L != NULL) {
		aux = (*L)->inicioL;
		while(aux != NULL) {
			letra = aux;
			aux = aux->prox;
			free(letra);		
		}
		(*L)->inicioL = NULL;
	}
}

void freeLinha(Linhas**L) {
	if(*L != NULL) {
		Linhas *ant = (*L)->top;
		Linhas *prox = (*L)->botton;
		
		freeLetras(&*L);
		
		free(*L);
		
		if (ant != NULL)
					ant->botton = prox;

			if (prox != NULL)
					prox->top = ant;
					
			free(*L);
			*L = NULL;
	}
}

void freeAll(DescLinhas**d) {
	if(*d != NULL) {
		Linhas *linha, *aux;		
		
		aux = (*d)->inicio;
		
		while(aux != NULL) {
			linha = aux->botton;
			freeLinha(&aux);
			aux = linha;
		}
		
		free(*d);
		*d = NULL;
	}
}

Linhas* linhaEmBranco() {
	Linhas *nova;
	nova = (Linhas*)malloc(sizeof(Linhas));
	
	if (nova == NULL)
		return NULL;
	
	nova->botton = NULL;
	nova->top = NULL;
	nova->nro = 0;
	nova->inicioL = NULL;
	
	return nova;
}

Letra* criarLetra(char c) {
    Letra *nova = (Letra*) malloc(sizeof(Letra));
    if (nova == NULL) 
			return NULL;

    nova->letra = c;
    nova->ant = NULL;
    nova->prox = NULL;

    return nova;
}

void inserirLinha(DescLinhas *d, Linhas *nova) {
    if (d->inicio == NULL) {
        d->inicio = nova;
    } else {
        Linhas *aux = d->inicio;

        while (aux->botton != NULL)
            aux = aux->botton;

        aux->botton = nova;
        nova->top = aux;
    }

    d->qntdLinhas++;
}

void inserirLetra(Linhas *linha, char c) {
    Letra *nova = criarLetra(c);

    if (linha->inicioL == NULL) {
        linha->inicioL = nova;
    } else {
        Letra *aux = linha->inicioL;
        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = nova;
        nova->ant = aux;
    }

    linha->nro++;
}

#endif