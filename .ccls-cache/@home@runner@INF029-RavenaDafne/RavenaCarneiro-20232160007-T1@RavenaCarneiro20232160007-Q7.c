#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void limparTela() { system("clear"); }

void imprimirTabuleiro(char tabuleiro[3][3]) {
    limparTela();
    printf("Jogo da Velha\n");
    printf("\n");
    printf("  1 | 2 | 3\n");
    printf("----+---+---\n");
    for (int i = 0; i < 3; i++) {
        printf("%c", 'A' + i);
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("----+---+---\n");
        }
    }
    printf("\n");
}

int converteLinhaInt(char letra) { return letra - 'A'; }

void jogar(char tabuleiro[3][3], char jogador) {
    char linha;
    int coluna;

    do {
        printf("Digite as coordenadas (linha e coluna, ex: A1, B2, C3) em que quer "
               "colocar o '%c': ", jogador);
      scanf(" %c%d",&linha,&coluna);
      linha = toupper(linha) - 'A';
      coluna--;
        
    } while (linha < 0 || linha > 2|| coluna < 0 || coluna > 2   ||
            (tabuleiro[linha][coluna] != ' '));
           tabuleiro[linha][coluna] = jogador;
}

int verificarVencedor(char tabuleiro[3][3], char jogador) {
    for (int i = 0; i < 3; i++) {
        if ((tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) ||
            (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador)) {
            return 1;
        }
    }
    // Verifica diagonais
    if ((tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) ||
        (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)) {
        return 1;
    }
    return 0;
}

int main() {
    char tabuleiro[3][3], jogador;
    int rodada;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }

    imprimirTabuleiro(tabuleiro);
    for (rodada = 1; rodada <= 9; rodada++) {
        jogador = (rodada % 2 == 1) ? 'X' : 'O';
        jogar(tabuleiro, jogador);
        imprimirTabuleiro(tabuleiro);
        if (verificarVencedor(tabuleiro, jogador)) {
            printf("\nO Jogador '%c' ganhou!\n", jogador);
            return 0;
        }
    }
    printf("\nDeu Velha!\n");
    return 0;
}
