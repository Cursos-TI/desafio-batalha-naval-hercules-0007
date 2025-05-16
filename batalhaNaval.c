#include <stdio.h>

#define TAB_SIZE 10
#define HAB_SIZE 5
#define AFETADO 5
#define NAVIO 3
#define AGUA 0

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // Posicionando navios de exemplo
    tabuleiro[2][2] = NAVIO;
    tabuleiro[4][4] = NAVIO;
    tabuleiro[6][6] = NAVIO;
}

// Exibe o tabuleiro com símbolos
void exibirTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ ");
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");
            else if (tabuleiro[i][j] == AFETADO)
                printf("* ");
        }
        printf("\n");
    }
}

// Gera uma matriz de habilidade em forma de cone (ponta para cima)
void gerarCone(int matriz[HAB_SIZE][HAB_SIZE]) {
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            matriz[i][j] = (j >= HAB_SIZE / 2 - i && j <= HAB_SIZE / 2 + i) ? 1 : 0;
        }
    }
}

// Gera uma matriz de habilidade em forma de cruz
void gerarCruz(int matriz[HAB_SIZE][HAB_SIZE]) {
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            matriz[i][j] = (i == HAB_SIZE / 2 || j == HAB_SIZE / 2) ? 1 : 0;
        }
    }
}

// Gera uma matriz de habilidade em forma de octaedro (losango)
void gerarOctaedro(int matriz[HAB_SIZE][HAB_SIZE]) {
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            int centro = HAB_SIZE / 2;
            matriz[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro, usando (orig_i, orig_j) como centro
void aplicarHabilidade(int tabuleiro[TAB_SIZE][TAB_SIZE], int habilidade[HAB_SIZE][HAB_SIZE], int orig_i, int orig_j) {
    for (int i = 0; i < HAB_SIZE; i++) {
        for (int j = 0; j < HAB_SIZE; j++) {
            if (habilidade[i][j] == 1) {
                int linha = orig_i + (i - HAB_SIZE / 2);
                int coluna = orig_j + (j - HAB_SIZE / 2);
                if (linha >= 0 && linha < TAB_SIZE && coluna >= 0 && coluna < TAB_SIZE) {
                    // Marcar como afetado (não sobrescreve navio)
                    if (tabuleiro[linha][coluna] == AGUA)
                        tabuleiro[linha][coluna] = AFETADO;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    int habilidade[HAB_SIZE][HAB_SIZE];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Ponto de origem no tabuleiro
    int origem_i = 4, origem_j = 4;

    printf("=== Tabuleiro Inicial ===\n");
    exibirTabuleiro(tabuleiro);

    // Habilidade: Cone
    gerarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, origem_i, origem_j);

    printf("\n=== Tabuleiro com Habilidade: Cone ===\n");
    exibirTabuleiro(tabuleiro);

    // Reinicia o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Habilidade: Cruz
    gerarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, origem_i, origem_j);

    printf("\n=== Tabuleiro com Habilidade: Cruz ===\n");
    exibirTabuleiro(tabuleiro);

    // Reinicia o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Habilidade: Octaedro
    gerarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, origem_i, origem_j);

    printf("\n=== Tabuleiro com Habilidade: Octaedro ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}