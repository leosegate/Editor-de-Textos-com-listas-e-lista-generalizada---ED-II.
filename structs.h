#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct charS {
    char letra;
    struct charS *ant, *prox;
} Letra;

typedef struct linha {
    struct linha *top, *botton;
    int nro; // qntd de letras na linha
    Letra *inicioL;
} Linha;

typedef struct descritor_editor {
    Linha *inicio;
    Linha *linhaTopoTela;
    int alturaTela;
    int qntdLinhas;
    int primLinha;   // use: 15 espacamento (F5)
    int recuoEsq;    // use: 5 espacamento (F5)
    int recuoDir;    // use: 75 (limite da coluna) (F5)
    int modoInsert; // 1: Inserir, 0: Sobrescrever (usando para INSERT)
    int negritoAtivo;// 1 para Ligado, 0 para Desligado (visual no main)
    struct noPalavra *dicionario; //usado para auto completar
    char palavraAtual[80];	//usado para auto completar
} DescLinhas;

typedef struct noPalavra {
    char letra;
    int final; // 1 para verdadeiro, 0 para falso
    struct noPalavra *prim; // Ponteiro para baixo 
    struct noPalavra *prox; // Ponteiro para a direita
} NoPalavra;

typedef struct cursor {
    Linha *linha;
    Letra *letra;
    int col;
}Cursor;

#endif
