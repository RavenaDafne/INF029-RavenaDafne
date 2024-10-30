#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define TAM_TABULEIRO 10

typedef enum {
    REBOCADOR = 2,
    CONTRATORPEDOIRO = 3,
    CRUZADOR = 4,
    PORTA_AVIOES = 5
} TipoNavio;

typedef struct {
    TipoNavio tipo;
    bool afundado;
} Navio;

typedef struct {
    char matriz[TAM_TABULEIRO][TAM_TABULEIRO];
    Navio navios[TAM_TABULEIRO][TAM_TABULEIRO];
} Tabuleiro;

void limparTela() {
    system("clear");
}

void imprimirTabuleiroJogador(Tabuleiro *tabuleiro) {
    printf("  ");
    for (char c = 'A'; c < 'A' + TAM_TABULEIRO; c++) {
        printf("%c ", c);
    }
    printf("\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%c ", tabuleiro->matriz[i][j]);
        }
        printf("\n");
    }
}

void inicializarTabuleiro(Tabuleiro *tabuleiro) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro->matriz[i][j] = '.';
            tabuleiro->navios[i][j].tipo = REBOCADOR;
            tabuleiro->navios[i][j].afundado = false;
        }
    }
}


void posicionarNavios(Tabuleiro *tabuleiro) {
    srand(time(NULL)); 

    for (TipoNavio tipo = REBOCADOR; tipo <= PORTA_AVIOES; tipo++) {
        for (int i = 0; i < tipo; i++) {
            bool posicao_valida = false;

            while (!posicao_valida) {
                int linha = rand() % TAM_TABULEIRO;
                int coluna = rand() % TAM_TABULEIRO;
                bool vertical = rand() % 2 == 0; 
                posicao_valida = true;
                if (vertical) {
                    if (linha + tipo > TAM_TABULEIRO) {
                        posicao_valida = false;
                        continue; 
                    }
                 
                    for (int j = linha; j < linha + tipo; j++) {
                        if (tabuleiro->navios[j][coluna].tipo != REBOCADOR) {
                            posicao_valida = false;
                            break;
                        }
                    }
            
                    if (posicao_valida) {
                        for (int j = linha; j < linha + tipo; j++) {
                            tabuleiro->navios[j][coluna].tipo = tipo;
                        }
                    }
                } else {
                    if (coluna + tipo > TAM_TABULEIRO) {
                        posicao_valida = false;
                        continue; 
                    }
                    for (int j = coluna; j < coluna + tipo; j++) {
                        if (tabuleiro->navios[linha][j].tipo != REBOCADOR) {
                            posicao_valida = false;
                            break; 
                        }
                    }
                    if (posicao_valida) {
                        for (int j = coluna; j < coluna + tipo; j++) {
                            tabuleiro->navios[linha][j].tipo = tipo;
                        }
                    }
                }
            }
        }
    }
}

void realizarTiro(Tabuleiro *tabuleiro, int linha, int coluna) {
    if (tabuleiro->navios[linha][coluna].tipo != REBOCADOR) {
        tabuleiro->matriz[linha][coluna] = 'X';
        tabuleiro->navios[linha][coluna].afundado = true;
    } else {
        tabuleiro->matriz[linha][coluna] = 'O';
    }
}

bool todosNaviosAfundados(Tabuleiro *tabuleiro) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro->navios[i][j].tipo != REBOCADOR && !tabuleiro->navios[i][j].afundado) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    Tabuleiro tabuleiro;
    int linha, coluna, tiros = 0;
    inicializarTabuleiro(&tabuleiro);
    posicionarNavios(&tabuleiro);

    while (!todosNaviosAfundados(&tabuleiro)) {
        limparTela();
        printf("Tabuleiro do Jogador:\n");
        imprimirTabuleiroJogador(&tabuleiro);

        printf("\nInforme as coordenadas do tiro (linha e coluna): ");
        scanf(" %d %d", &linha,&coluna);
        linha--;
        coluna = toupper(coluna) - 'A';

        if (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO) {
            realizarTiro(&tabuleiro, linha, coluna);
            tiros++;
        } else {
            printf("Coordenadas inválidas. Tente novamente.\n");
        }
    }
    return 0; 
}
