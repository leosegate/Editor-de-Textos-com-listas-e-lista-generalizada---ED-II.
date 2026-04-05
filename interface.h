void exibirBarraStatus(DescLinhas *d, Cursor *c) {
    //rodape
    gotoxy(1, 28);
    printf("-----------------------------------------------------------------");
    gotoxy(1, 30);
    
    // INSERT
    printf("INSERT: ");
    if (d->modoInsert == 1) {
        printf("[ON ] ");
    }
    if (d->modoInsert == 0) {
        printf("[OFF] ");
    }

    // NEGRITO (F10)
    printf("| NEGRITO (F10): ");
    if (d->negritoAtivo == 1) {
        printf("[ON ] ");
    }
    if (d->negritoAtivo == 0) {
        printf("[OFF] ");
    }
	//visualizacao de onde o ponteiro ta
    printf("| COL: %d LIN: %d", c->col, d->qntdLinhas);
}
void desenharInterface(DescLinhas *d, Cursor *c) {
    int i;
    char sugestao[80];
    sugestao[0] = '\0';
    
    gotoxy(1, 1);
    textcolor(WHITE);
    textbackground(BLACK); 
    printf("--- EDITOR DE TEXTO (FIPP) ---");
    
    gotoxy(1, 2);
    printf("| F2: Abrir | F3: Salvar | F4: Sair | F5: Exibir | F10: Negrito |");
    
    gotoxy(1, 3);
    printf("-----------------------------------------------------------------");

    gotoxy(1, 4);
    imprimirEditor(d, c);

if (strlen(d->palavraAtual) > 1) {
        buscarSugestao(d->dicionario, d->palavraAtual, sugestao);
    }

    gotoxy(1, 22); 
    if (strlen(sugestao) > 0) {
        textcolor(LIGHTMAGENTA);
        printf(" Sugestao: %s (Pressione ENTER para completar)", sugestao);
        textcolor(WHITE);
    } else {
        printf("                                                                 ");
    }

    gotoxy(1, 23);
    printf("-----------------------------------------------------------------");
    
    gotoxy(1, 24);
    printf("INSERT: ");
    if (d->modoInsert == 1) {
        textcolor(GREEN); printf("[LIGADO]   ");
    } else {
        textcolor(RED); printf("[DESLIGADO]");
    }
    
    textcolor(WHITE);
    printf(" | NEGRITO: ");
    if (d->negritoAtivo == 1) {
        textcolor(GREEN); printf("[ON] ");
    } else {
        textcolor(WHITE); printf("[OFF]");
    }

    textcolor(LIGHTCYAN);
    printf(" | COL: %d | LIN: %d  ", c->col, obterLinhaAtual(d, c));
    
    textcolor(WHITE);
    textbackground(BLACK);
}

