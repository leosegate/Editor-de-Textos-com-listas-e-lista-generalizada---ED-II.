#include <stdio.h>

typedef struct charS {
	char letra;
	struct charS *ant, *prox;
} Letra;

typedef struct linhas {
	struct linhas *top, *botton;
	int nro;
	Letra *inicioL;
}Linhas;

typedef struct descritor {
	Linhas *inicio;
}DescLinhas;

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
	if(*L == NULL)
		return;
	
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

void freeAll(DescLinhas**d) {
	Linhas *linha, *aux;
	
	if(*d == NULL) {
		return;
	}
	
	aux = (*d)->inicio;
	
	while(aux != NULL) {
		linha = aux->botton;
		freeLinha(&aux);
		aux = linha;
	}
	
	free(*d);
	*d = NULL;
}

Linhas* linhaEmBranco() {
	Linhas *nova;
	nova = (Linhas*)malloc(sizeof(Linhas));
	
	if (nova = NULL)
		return NULL;
	
	nova->botton = NULL;
	nova->top = NULL;
	nova->nro = 0;
	nova->inicioL = NULL;
	
	return nova;
}


