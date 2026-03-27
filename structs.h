#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct charS {
	char letra;
	struct charS *ant, *prox;
} Letra;

typedef struct linhas {
	struct linhas *top, *botton;
	int nro; // qntd de letras visiveis
	Letra *inicioL;
}Linhas;

typedef struct descritor_editor {
	Linhas *inicio;
  int qntdLinhas;
}DescLinhas;


//para usar no final do pdf, entender direito isso
typedef struct noPalavra {
    char letra;
    int final; //true or false
    struct noPalavra *prim; // Ponteiro para baixo 
    struct noPalavra *prox; // Ponteiro para a direita
} NoPalavra;
//-----------------------------------------------------------------

#endif
