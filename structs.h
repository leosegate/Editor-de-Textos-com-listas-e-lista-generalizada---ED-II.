#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct charS {
    char letra;
    struct charS *ant, *prox;
} Letra;

typedef struct linhas {
    struct linhas *top, *botton;
    int nro; // qntd de letras na linha
    Letra *inicioL;
} Linhas;

typedef struct descritor_editor {
    Linhas *inicio;
    int qntdLinhas;
    int primLinha;   // use: 15 espaços
    int recuoEsq;    // use: 5 espaços
    int recuoDir;    // use: 75 (limite da coluna)
} DescLinhas;

typedef struct noPalavra {
    char letra;
    int final; // 1 para verdadeiro, 0 para falso
    struct noPalavra *prim; // Ponteiro para baixo 
    struct noPalavra *prox; // Ponteiro para a direita
} NoPalavra;

#endif
