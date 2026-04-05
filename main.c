#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include "structs.h"
#include "funcoes.h"
#include "manipular_arquivo.h"
#include "editor.h"

// ================= FUNÇÕES =================
void resetarCursor(Cursor *c, DescLinhas *d) {
    c->linha = d->inicio;
    c->letra = NULL;
    c->col = 0;
}

void escolha(int tecla, DescLinhas **d, Cursor *cursor) {
    char nomeArq[100];

    // F2 - Abrir
    if (tecla == 60) { 
        printf("\nNome do Arquivo para abrir: ");
        scanf("%s", nomeArq);
        fflush(stdin);

        freeLetrasDoEditor(*d); 
        
        DescLinhas *temp = lerArquivoTXT(nomeArq);
        if (temp != NULL) {
            free(*d);
            *d = temp;
            (*d)->linhaTopoTela = (*d)->inicio;
            resetarCursor(cursor, *d);

            printf("\nArquivo carregado com sucesso!");
        } else {
            printf("\nErro ao carregar arquivo.");
        }
        Sleep(600);
    }

    // F3 - Salvar
    if (tecla == 61) { 
        printf("\nNome do Arquivo para salvar: ");
        scanf("%s", nomeArq);
        fflush(stdin);

        salvarArquivoTXT(nomeArq, *d);

        printf("\nSalvo!");
        Sleep(600);
    }

    // F5 - Exibir formatado
    if (tecla == 63) { 
        system("cls");

        printf("--- Configuracao dos Paragrafos ---\n");

        printf("Primeira Linha (espacos): ");
        scanf("%d", &((*d)->primLinha));
        
        printf("Recuo Esquerdo (espacos): ");
        scanf("%d", &((*d)->recuoEsq));
        
        printf("Recuo Direito (coluna): ");
        scanf("%d", &((*d)->recuoDir));
        
        printf("\n--- EXIBICAO FORMATADA ---\n\n");

        exibirFormatado(*d);

        printf("\n-----------------------------------------------------------------");
        printf("\nPressione qualquer tecla para voltar...");
        getch();
    }

    // F10 - Negrito (placeholder)
    if (tecla == 68) { 
        inserirChar(cursor, (char)21);
    }
}

// ================= MAIN =================
int main() {
    DescLinhas *meuEditor = criarDescritor();
    Cursor cursor;
	/*
    printf("DEBUG:\n");
    printf("inicio: %p\n", meuEditor->inicio);
    printf("topo: %p\n", meuEditor->linhaTopoTela);
    printf("cursor linha: %p\n", cursor.linha);

    getch();*/

    int tecla = 0;
    int continuar = 1;

    if (meuEditor != NULL) {

        inserirLinha(meuEditor, linhaEmBranco());

        resetarCursor(&cursor, meuEditor);

        while (continuar == 1) {
            system("cls");

            printf("--- EDITOR DE TEXTO (FIPP) ---\n");
            printf("| F2: Abrir | F3: Salvar | F4: Sair | F5: Exibir | F10: Negrito |\n");
            printf("-----------------------------------------------------------------\n");

            gotoxy(1,29), printf("-----------------------------------------------------------------");
            gotoxy(1,4);

            imprimirEditor(meuEditor, &cursor);

            tecla = getch();

            // TECLAS ESPECIAIS
            if (tecla == 0 || tecla == 224) {
                tecla = getch();

                switch (tecla) {
                    case 75: // ←
                        moverEsquerda(&cursor);
                        break;

                    case 77: // →
                        moverDireita(&cursor);
                        break;

                    case 72: // ↑
                        moverCima(&cursor);
                        break;

                    case 80: // ↓
                        moverBaixo(&cursor);
                        break;

                    case 62: // F4
                        continuar = 0;
                        break;

                    case 73: // Page Up
                        scrollUp(meuEditor, &cursor);
                        break;

                    case 81: // Page Down
                        scrollDown(meuEditor, &cursor);
                        break;

                    default:
                        escolha(tecla, &meuEditor, &cursor);
                }
            }

            // TECLAS NORMAIS
            else {
                if (tecla == 27) { // ESC
                    continuar = 0;
                }
                else if (tecla == 13) { // ENTER
                    quebrarLinha(&cursor, meuEditor);
                }
                else if (tecla == 8) { // BACKSPACE
                    removerChar(&cursor);
                }
                else if (tecla >= 32 && tecla <= 255) {
                    inserirChar(&cursor, (char)tecla);
                }
            }
        }

        freeAll(&meuEditor);
    }

    return 0;
}
