#include <stdio.h>
#include <conio.h> 
#include <windows.h>
#include "structs.h"
#include "funcoes.h"
#include "manipular_arquivo.h"
#include "editor.h"


void escolha(int tecla, DescLinhas **d) {
    char nomeArq[100];

    // F2 - Abrir
    if (tecla == 60) { 
        printf("\nNome do Arquivo para abrir: ");
        scanf("%s", nomeArq);
        fflush(stdin);

        // Limpa a memoria do que existia antes
        freeLetrasDoEditor(*d); 
        
        DescLinhas *temp = lerArquivoTXT(nomeArq);
        if (temp != NULL) {
            free(*d); // Libera o descritor antigo
            *d = temp; // O ponteiro do main agora aponta para o novo arquivo
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

    // F5 - Exibir 
    if (tecla == 63) { 
        system("cls");
        printf("--- Configuracao dos Paragrafos ---\n");
        fflush(stdin);
        
       
        printf("Primeira Linha (espacos): ");
        scanf("%d", &((*d)->primLinha));
        
        printf("Recuo Esquerdo (espacos): ");
        scanf("%d", &((*d)->recuoEsq));
        
        printf("Recuo Direito (coluna): ");
        scanf("%d", &((*d)->recuoDir));
        
        fflush(stdin);
        
        printf("--- EXIBICAO FORMATADA ---\n\n");
        // Chama a função de exibição passando o conteudo do ponteiro
        exibirFormatado(*d);
        printf("-----------------------------------------------------------------");
        printf("\nPressione qualquer tecla para voltar...");
        getch();
    }

    // F10 - Negrito (colocar ele como uma tecla própria, seguir exemplo do desenho do trab
    if (tecla == 68) { 
        digitarCaractere(*d, (char)21); 
    }
}
int main() {
    DescLinhas *meuEditor = criarDescritor();
    int tecla = 0;
    int continuar = 1;

    if (meuEditor != NULL) {
        // Inicia com uma linha vazia para digitação
        inserirLinha(meuEditor, linhaEmBranco());

        while (continuar == 1) {
            system("cls");
            printf("--- EDITOR DE TEXTO (FIPP) ---\n");
            printf("| F2: Abrir | F3: Salvar | F4: Sair | F5: Exibir | F10: Negrito |\n");
            printf("-----------------------------------------------------------------\n");
            
            imprimirEditor(meuEditor);
            
            tecla = getch();

            // Teclas de Funcao e Setas
            if (tecla == 0 || tecla == 224) {
                tecla = getch();
                    
                if (tecla == 62) { // F4 para sair
                    continuar = 0;
                } else {
                    escolha(tecla, &meuEditor);
                }    
            } 
            
			else {
                // Tecla ESC para sair
                if (tecla == 27) {
                    continuar = 0;
                } 
                // Tecla ENTER
                else 
					if (tecla == 13) {
                    	inserirLinha(meuEditor, linhaEmBranco());
                	} 
                // Backspace (ta apagando)
                else 
					if (tecla == 8) {
                    	apagarUltimoCaractere(meuEditor);
                }
				 
                // Caracteres normais
                else 
					if (tecla >= 32 && tecla <= 255) {
                    	digitarCaractere(meuEditor, (char)tecla);
                	}
            }
        }
		freeAll(&meuEditor);
    }
    return 0;
}
