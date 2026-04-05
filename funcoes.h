#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// ta conflicando (n sei pq)
void inserirPalavraAuto(NoPalavra **raiz, char *palavra);
void buscarSugestao(NoPalavra *raiz, char *prefixo, char *sugestao);
// --- Limpeza de Memoria---
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
        Linha *proxima;
        while (aux != NULL) {
            proxima = aux->botton;
            freeLinha(&aux);
            aux = proxima;
        }
        free(*d);
        *d = NULL;
    }
}

// --- Criacao e insercao ---

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

void inserirChar(Cursor *cursor, char ch) {
    Letra *nova = criarLetra(ch);

    if (cursor->linha->inicioL == NULL) {
        cursor->linha->inicioL = nova;
        cursor->letra = nova;
    }
    
    else if (cursor->letra == NULL) {
        nova->prox = cursor->linha->inicioL;
        cursor->linha->inicioL->ant = nova;
        cursor->linha->inicioL = nova;
        cursor->letra = nova;
    }
    
    else {
        nova->prox = cursor->letra->prox;
        nova->ant = cursor->letra;

        if (cursor->letra->prox != NULL) {
            cursor->letra->prox->ant = nova;
        }

        cursor->letra->prox = nova;
        cursor->letra = nova;
    }

    cursor->col++;
    cursor->linha->nro++;   
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
// --- Lista Generalizada (Auto-completar) --- 	mexidov

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

void removerChar(Cursor *c) {
    if (c->letra == NULL) {
        if (c->linha->top == NULL)
            return;

        Linha *linhaAtual = c->linha;
        Linha *linhaCima = c->linha->top;

        Letra *aux = linhaCima->inicioL;
        Letra *ultima = NULL;

        while (aux != NULL) {
            ultima = aux;
            aux = aux->prox;
        }

        if (ultima != NULL) {
            ultima->prox = linhaAtual->inicioL;

            if (linhaAtual->inicioL != NULL)
                linhaAtual->inicioL->ant = ultima;
        } else {
            linhaCima->inicioL = linhaAtual->inicioL;
        }

        linhaCima->nro += linhaAtual->nro;
        linhaCima->botton = linhaAtual->botton;

        if (linhaAtual->botton != NULL)
            linhaAtual->botton->top = linhaCima;

        c->linha = linhaCima;
        c->letra = ultima;
        c->col = linhaCima->nro;

        free(linhaAtual);
    }
    else {
        Letra *remover = c->letra;

        if (remover->ant != NULL) {
            remover->ant->prox = remover->prox;
        } else {
            c->linha->inicioL = remover->prox;
        }
        if (remover->prox != NULL) {
            remover->prox->ant = remover->ant;
        }
        c->letra = remover->ant;
        c->col--;

        c->linha->nro--;

        free(remover);
    }
}

void quebrarLinha(Cursor *c, DescLinhas *d) {
    Linha *linhaAtual = c->linha;

    Linha *nova = (Linha*) malloc(sizeof(Linha));
    nova->inicioL = NULL;
    nova->top = linhaAtual;
    nova->botton = linhaAtual->botton;
    nova->nro = 0;

    if (linhaAtual->botton != NULL)
        linhaAtual->botton->top = nova;

    linhaAtual->botton = nova;

    if (c->letra == NULL) {
        nova->inicioL = linhaAtual->inicioL;
        nova->nro = linhaAtual->nro;

        linhaAtual->inicioL = NULL;
        linhaAtual->nro = 0;
    }

    else {
        Letra *quebra = c->letra->prox;

        nova->inicioL = quebra;

        int count = 0;
        Letra *aux = quebra;

        while (aux != NULL) {
            aux->ant = NULL;
            if (aux->prox == NULL) break;
            aux = aux->prox;
            count++;
        }
        if (quebra != NULL) count++; 

        nova->nro = count;

        c->letra->prox = NULL;
        linhaAtual->nro -= nova->nro;

        if (quebra != NULL)
            quebra->ant = NULL;
    }

    d->qntdLinhas++;

    c->linha = nova;
    c->letra = NULL;
    c->col = 0;
}
//QUEBRA DE LINHAS (79 CARACTERE)
void realizarQuebraAutomatica(DescLinhas *d, Cursor *c) {
    if (c->linha->nro >= 79) {
        Letra *aux = c->linha->inicioL;
        Letra *ultimoEspaco = NULL;
        
        // Busca o ultimo espaço na linha atual
        while (aux != NULL) {
            if (aux->letra == ' ') {
                ultimoEspaco = aux;
            }
            aux = aux->prox;
        }

        // Se houver um espaço, separa
        if (ultimoEspaco != NULL) {
            // Salva a posicao antiga para ajustar o cursor depois
            Letra *letraAntiga = c->letra;
            
            // Move o cursor para o espaco para usar a quebrarLinha
            c->letra = ultimoEspaco;
            quebrarLinha(c, d);
            
            // Remove o espaço que ficou sobrando no final da linha de cima
            removerChar(c); 
        } else {
            // Se for palavra gigante sem espaços, quebra no caractere atual
            quebrarLinha(c, d);
        }
    }
}

// EXIBICAO LINHAS (MAIN)
int obterLinhaAtual(DescLinhas *d, Cursor *c) {
    int cont = 1;
    Linha *aux = d->inicio;
    
    while (aux != NULL && aux != c->linha) {
        aux = aux->botton;
        cont++;
    }
    
    return cont;
}


// IR PARA INICIO [HOME]
void moverHome(Cursor *c) {
    if (c != NULL) {
        if (c->linha != NULL) {
            c->letra = NULL;
            c->col = 0;
        }
    }
}
// IR PARA FIM [END]
void moverEnd(Cursor *c) {
    if (c != NULL) {
        if (c->linha != NULL) {
            Letra *aux = c->linha->inicioL;
            int contador = 0;

            if (aux != NULL) {
                while (aux->prox != NULL) {
                    aux = aux->prox;
                    contador++;
                }
                c->letra = aux;
                c->col = contador + 1;
            }
            else {
                c->letra = NULL;
                c->col = 0;
            }
        }
    }
}
// DELETE [DEL]
void removerSobCursor(Cursor *c) {
    if (c != NULL) {
        if (c->linha != NULL) {
            Letra *remover = NULL;

            if (c->letra == NULL) {
                if (c->linha->inicioL != NULL) {
                    remover = c->linha->inicioL;
                    c->linha->inicioL = remover->prox;
                    
                    if (remover->prox != NULL) {
                        remover->prox->ant = NULL;
                    }
                    
                    free(remover);
                    c->linha->nro--;
                }
            }
            // Se o cursor estiver sobre uma letra, o DEL apaga a letra a DIREITA (prox)
            else {
                if (c->letra->prox != NULL) {
                    remover = c->letra->prox;
                    c->letra->prox = remover->prox;
                    
                    if (remover->prox != NULL) {
                        remover->prox->ant = c->letra;
                    }
                    
                    free(remover);
                    c->linha->nro--;
                }
            }
        }
    }
}
//INSERT [INS]	
void gerenciarDigitacao(DescLinhas *d, Cursor *cursor, char ch) {
  //adiciona no buffer oq ta sendo usado
    if (ch != ' ' && ch != '.' && ch != ',' && ch != '?' && ch != '!' && ch != (char)13) {
        int tam = strlen(d->palavraAtual);
        if (tam < 79) {
            d->palavraAtual[tam] = ch;
            d->palavraAtual[tam + 1] = '\0';
        }
    } 
    // 2. Se for espaco, enter ou pontuacao. a palavra terminou
    else {
        if (strlen(d->palavraAtual) > 2) {
            inserirPalavraAuto(&(d->dicionario), d->palavraAtual);
        }
        d->palavraAtual[0] = '\0'; // Limpa para a prox palavra
    }

    // Insercao normal no texto
    inserirChar(cursor, ch);
    
    // quebra linha
    if (cursor->linha->nro >= 79) {
        realizarQuebraAutomatica(d, cursor);
    }
}
void scrollUp(DescLinhas *d, Cursor *c) {
    int i = 0;

    while (i < d->alturaTela && d->linhaTopoTela->top != NULL) {
        d->linhaTopoTela = d->linhaTopoTela->top;
        i++;
    }

    // Ajusta cursor
    c->linha = d->linhaTopoTela;
    c->letra = NULL;
}

void scrollDown(DescLinhas *d, Cursor *c) {
    int i = 0;

    while (i < d->alturaTela && d->linhaTopoTela->botton != NULL) {
        d->linhaTopoTela = d->linhaTopoTela->botton;
        i++;
    }

    // Ajusta cursor
    c->linha = d->linhaTopoTela;
    c->letra = NULL;
}

void moverEsquerda(Cursor *c) {
    if (c->letra != NULL) {
        c->letra = c->letra->ant;
        c->col--;
    }
}

void moverDireita(Cursor *c) {
    if (c->letra == NULL) {
        if (c->linha->inicioL != NULL) {
            c->letra = c->linha->inicioL;
            c->col++;
        }
    } else if (c->letra->prox != NULL) {
        c->letra = c->letra->prox;
        c->col++;
    }
}

Letra* irParaColuna(Linha *linha, int col) {
    Letra *aux = linha->inicioL;

    int i = 0;
    Letra *anterior = NULL;

    while (aux != NULL && i < col) {
        anterior = aux;
        aux = aux->prox;
        i++;
    }

    return anterior;
}

void moverCima(Cursor *c) {
    if (c->linha->top == NULL) return;

    c->linha = c->linha->top;

    if (c->col > c->linha->nro)
        c->col = c->linha->nro;

    c->letra = irParaColuna(c->linha, c->col);
}

void moverBaixo(Cursor *c) {
    if (c->linha->botton == NULL) return;

    c->linha = c->linha->botton;

    if (c->col > c->linha->nro)
        c->col = c->linha->nro;

    c->letra = irParaColuna(c->linha, c->col);
}


void inserirPalavraAuto(NoPalavra **raiz, char *palavra) {
    if (palavra != NULL && palavra[0] != '\0') {
        //no null. cria letra
        if (*raiz == NULL) {
            *raiz = criarNoPalavra(palavra[0]);
        }

        // Se a letra do no == a letra da palavra
        if ((*raiz)->letra == palavra[0]) {
            // Se for a ultima letra da palavra, marca como final (T)
            if (palavra[1] == '\0') {
                (*raiz)->final = 1; 
            } else {
                // se n for. continua inserindo a prox letra para baixo (prim)
                inserirPalavraAuto(&((*raiz)->prim), &palavra[1]); 
	            }
        } else {
            // Se a letra e diferente, tenta inserir para a direita (prox)
            inserirPalavraAuto(&((*raiz)->prox), palavra); 
        }
    }
}

void buscarSugestao(NoPalavra *raiz, char *prefixo, char *sugestao) {
    NoPalavra *aux = raiz;
    int i = 0;
    sugestao[0] = '\0';

    // 1. Navega ate o final digitado pelo usuario
    while (prefixo[i] != '\0' && aux != NULL) {
        while (aux != NULL && aux->letra != prefixo[i]) {
            aux = aux->prox;
        }
        if (aux != NULL) {
            if (prefixo[i+1] != '\0') {
                aux = aux->prim;
            }
            i++;
        }
    }

    // 2. Se achou algo, verifica se o caminho eh UNICO (sem prox)
    if (aux != NULL && aux->prim != NULL) {
        NoPalavra *filho = aux->prim;

        if (filho->prox == NULL) {
            int k = 0;
            // Copia o que ja foi digitado
            while (k < i) {
                sugestao[k] = prefixo[k];
                k++;
            }

            // Segue o caminho unico para baixo ate o fim 
            while (filho != NULL && filho->prox == NULL) {
                sugestao[k++] = filho->letra;
                if (filho->final == 1) {
                    filho = NULL; // Achou o fim da palavra (T)
                } else {
                    filho = filho->prim;
                }
            }
            sugestao[k] = '\0';
        }
    }
}

#endif
