#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include "structs.h"
#include "funcoes.h"
#include "manipular_arquivo.h"
#include "editor.h"
#include "interface.h"

// ================= FUNCOES =================
void resetarCursor(Cursor *c, DescLinhas *d) {
    c->linha = d->inicio;
    c->letra = NULL;
    c->col = 0;
}




void escolha(int tecla, DescLinhas **d, Cursor *cursor) {
    char nomeArq[100];

    if (tecla == 60) { // F2
        gotoxy(1, 25); // Pergunta na ultima linha para nao quebrar o visual
        printf("Arquivo para abrir: ");
        scanf("%s", nomeArq);
        fflush(stdin);
        freeLetrasDoEditor(*d); 
        DescLinhas *temp = lerArquivoTXT(nomeArq);
        if (temp != NULL) {
            free(*d);
            *d = temp;
            (*d)->linhaTopoTela = (*d)->inicio;
            resetarCursor(cursor, *d);
        }
    }

    if (tecla == 61) { // F3
        gotoxy(1, 25);
        printf("Arquivo para salvar: ");
        scanf("%s", nomeArq);
        fflush(stdin);
        salvarArquivoTXT(nomeArq, *d);
    }

    if (tecla == 63) { // F5
        system("cls");
        printf("--- EXIBICAO FORMATADA ---\n\n");
        exibirFormatado(*d);
        printf("\nPressione qualquer tecla para voltar...");
        getch();
    }

    if (tecla == 68) { // F10
        if ((*d)->negritoAtivo == 1) (*d)->negritoAtivo = 0;
        else (*d)->negritoAtivo = 1;
        inserirChar(cursor, (char)21);
    }
}

// ================= MAIN =================
int main() {
    DescLinhas *meuEditor = criarDescritor();
    Cursor cursor;
    int tecla = 0;
    int continuar = 1;
    char sugestao[80]; //autocompletar

    if (meuEditor != NULL) {
        inserirLinha(meuEditor, linhaEmBranco());
        resetarCursor(&cursor, meuEditor);

        while (continuar == 1) {
            system("cls"); 
            
            desenharInterface(meuEditor, &cursor);

            tecla = getch();

            if (tecla == 0 || tecla == 224) {
                tecla = getch();
                switch (tecla) {
                    case 71: moverHome(&cursor);
					break;
                    
					case 79: moverEnd(&cursor); 
					break;
                    
					case 75: moverEsquerda(&cursor); 
					break;
                    
					case 77: moverDireita(&cursor); 
					break;
                    
					case 72: moverCima(&cursor); 
					break;
                    
					case 80: moverBaixo(&cursor); 
					break;
                    
					case 62: continuar = 0; 
					break; // F4
                    
					case 73: scrollUp(meuEditor, &cursor); 
					break;
                    
					case 81: scrollDown(meuEditor, &cursor); 
					break;
                    
					case 83: removerSobCursor(&cursor); 
					break;
                    
					case 82: 
                        if (meuEditor->modoInsert == 1) 
							meuEditor->modoInsert = 0;
                        else 
							meuEditor->modoInsert = 1;
                    break;
                    
					default:
                        escolha(tecla, &meuEditor, &cursor);
                }
            }
            else {
                if (tecla == 27) { // ESC
                    continuar = 0;
                }
               else if (tecla == 13) { // ENTER  == (verificar erro de escrita na frente)
				    char sug[80];
				    sug[0] = '\0';
				    
				    // Busca se existe sugestao para o que esta no buffer agora
				    if (strlen(meuEditor->palavraAtual) > 1) {
				        buscarSugestao(meuEditor->dicionario, meuEditor->palavraAtual, sug);
				    }
				
				    // So completa se a sugestao for DIFERENTE e MAIOR que o que ja foi digitado
				    if (strlen(sug) > 0 && strcmp(sug, meuEditor->palavraAtual) != 0) {
				        int i = strlen(meuEditor->palavraAtual);
				        while (sug[i] != '\0') {
				            inserirChar(&cursor, sug[i]);
				            i++;
				        }
				        // Apos completar, limpar o buffer para que o prox enter (quebre a linha)
				        meuEditor->palavraAtual[0] = '\0'; 
				    } 
				    else {
				        // Se n tem sugestao nova, desce a linha
				        if (strlen(meuEditor->palavraAtual) > 2) {
				            inserirPalavraAuto(&(meuEditor->dicionario), meuEditor->palavraAtual);
				        }
				        quebrarLinha(&cursor, meuEditor);
				        meuEditor->palavraAtual[0] = '\0';
				    }
				}
                else if (tecla == 8) { // BACKSPACE
                    removerChar(&cursor);
                    int tam = strlen(meuEditor->palavraAtual);
                    if (tam > 0) {
                        meuEditor->palavraAtual[tam - 1] = '\0';
                    }
                }
                else if (tecla >= 32 && tecla <= 255) {
                    gerenciarDigitacao(meuEditor, &cursor, (char)tecla);
                }
            }
        }
        freeAll(&meuEditor);
    }
    return 0;
}
