#include "raylib.h"

#define TAM 7

typedef struct {
    int linha;
    int coluna;
    int estado;   // 0 = inválido, 1 = vazio, 2 = pino
    Vector2 pos;
} Casa;

void inicializa_tabuleiro(Casa tabuleiro[TAM][TAM]) {
    int inicioX = 100, inicioY = 100;
    int tamanho = 60;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].linha = i;
            tabuleiro[i][j].coluna = j;
            tabuleiro[i][j].pos = (Vector2){ inicioX + j * tamanho, inicioY + i * tamanho };

            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].estado = 0; // fora da cruz
            else
                tabuleiro[i][j].estado = 2; // pino
        }
    }

    tabuleiro[3][3].estado = 1; // centro vazio
}

void desenha_tabuleiro(Casa tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            Casa c = tabuleiro[i][j];

            if (c.estado == 0) continue;

            Color cor = (c.estado == 1) ? LIGHTGRAY : BLUE;
            DrawCircleV(c.pos, 20, cor);
        }
    }
}

int main(void) {
    InitWindow(900, 600, "Resta Um com struct e Raylib");

    Casa tabuleiro[TAM][TAM];
    inicializa_tabuleiro(tabuleiro);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenha_tabuleiro(tabuleiro);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
