#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// --- Limpeza de Mem�ria ---

void freeLetras(Linha* L) {
    if (L != NULL) {
        Letra *aux = L->inicioL;
        while (aux != NULL) {
            Letra *letra = aux;
            aux = aux->prox;
            free(letra);
        }
        L->inicioL = NULL;
    }
}

void freeLinha(Linha** L) {
    if (*L != NULL) {
        freeLetras(*L);
        free(*L);
        *L = NULL;
    }
}

void freeAll(DescLinhas** d) {
    if (*d != NULL) {
        Linha *aux = (*d)->inicio;
        while (aux != NULL) {
            Linha *proxima = aux->botton;
            freeLinha(&aux);
            aux = proxima;
        }
        free(*d);
        *d = NULL;
    }
}

// --- Cria��o e Inser��o ---

Linha* linhaEmBranco() {
    Linha *nova = (Linha*)malloc(sizeof(Linha));
    if (nova != NULL) {
        nova->botton = NULL;
        nova->top = NULL;
        nova->nro = 0;
        nova->inicioL = NULL;
    }
    return nova;
}

Letra* criarLetra(char c) {
    Letra *nova = (Letra*)malloc(sizeof(Letra));
    if (nova != NULL) {
        nova->letra = c;
        nova->ant = NULL;
        nova->prox = NULL;
    }
    return nova;
}

void inserirLinha(DescLinhas *d, Linha *nova) {
    if (d->inicio == NULL) {
        d->inicio = nova;
    } else {
        Linha *aux = d->inicio;
        while (aux->botton != NULL) {
            aux = aux->botton;
        }
        aux->botton = nova;
        nova->top = aux;
    }
    d->qntdLinhas++;
}

void inserirLetra(Linha *linha, char c) {
    Letra *nova = criarLetra(c);
    if (nova != NULL) {
        if (linha->inicioL == NULL) {
            linha->inicioL = nova;
        } else {
            Letra *aux = linha->inicioL;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = nova;
            nova->ant = aux;
        }
        linha->nro++;
    }
}

void digitarCaractere(DescLinhas *d, char c) {
    if (d != NULL) {
        Linha *atual = d->inicio;
        
        // 1. Navega ate a ultima linha
        if (atual != NULL) {
            while (atual->botton != NULL) {
                atual = atual->botton;
            }
        }

        // 2. Verifica se a linha atual estourou o limite de 79 caracteres
        if (atual == NULL || atual->nro >= 79) {
            Linha *nova = linhaEmBranco();
            if (nova != NULL) {
                inserirLinha(d, nova);
                atual = nova;
            }
        }

        // 3. Insere a letra na linha (seja na antiga ou na nova criada)
        if (atual != NULL) {
            inserirLetra(atual, c);
            // O PDF diz que se a palavra nao couber, ela deve ir para baixo.
            // Por enquanto, inserimos caractere a caractere conforme a digitacao do usuario.
        }
    }
}
void freeLetrasDoEditor(DescLinhas *d) {
    if (d != NULL) {
        Linha *aux = d->inicio;
        
        // Percorre todas as linhas
        while (aux != NULL) {
            Linha *proximaLinha = aux->botton;
            
            // Limpa as letras da linha atual 
            freeLetras(aux);
            
            // Libera a estrutura da linha 
            free(aux);
            
            aux = proximaLinha;
        }
        
        // Reseta o descritor para o estado vazio
        d->inicio = NULL;
        d->qntdLinhas = 0;
    }
}

void apagarUltimoCaractere(DescLinhas *d) {
    if (d != NULL && d->inicio != NULL) {
        Linha *atual = d->inicio;
        
        // 1. Navega ate a ultima linha
        while (atual->botton != NULL) {
            atual = atual->botton;
        }

        // 2. Verifica se a linha tem letras para apagar
        if (atual->inicioL != NULL) {
            Letra *aux = atual->inicioL;
            
            // Navega ate a ultima letra da linha
            while (aux->prox != NULL) {
                aux = aux->prox;
            }

            // Caso A: A letra a ser apagada e a unica da linha
            if (aux->ant == NULL) {
                atual->inicioL = NULL;
            } else {
                // Caso B: Tem mais de uma letra, ajusta o ponteiro da penultima
                aux->ant->prox = NULL;
            }

            free(aux);
            atual->nro--;
        } else {
            // 3. Se a linha estiver vazia, removemos a linha (se n for a unica)
            if (atual->top != NULL) {
                Linha *anterior = atual->top;
                anterior->botton = NULL;
                free(atual);
                d->qntdLinhas--;
            }
        }
    }
}
// --- Lista Generalizada (Auto-completar) --- 		mexi aqui ainda n

NoPalavra* criarNoPalavra(char c) {
    NoPalavra *novo = (NoPalavra*)malloc(sizeof(NoPalavra));
    if (novo != NULL) {
        novo->letra = c;
        novo->final = 0;
        novo->prim = NULL;
        novo->prox = NULL;
    }
    return novo;
}

void inserirNaListaG(NoPalavra **raiz, char *palavra) {
    if (palavra != NULL && palavra[0] != '\0') {
        if (*raiz == NULL) {
            *raiz = criarNoPalavra(palavra[0]);
        }

        if ((*raiz)->letra == palavra[0]) {
            if (palavra[1] == '\0') {
                (*raiz)->final = 1;
            } else {
                inserirNaListaG(&((*raiz)->prim), &palavra[1]);
            }
        } else {
            inserirNaListaG(&((*raiz)->prox), palavra);
        }
    }
}

#endif
