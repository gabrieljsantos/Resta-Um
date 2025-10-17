#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

#include "raylib.h"
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define TAM 7
#define MAX_RECORDES 10

typedef struct {
    char nome;      // apenas 1 letra identificando o jogador
    float tempo;    // tempo em segundos
} Recorde;

//--------------------------------------------------------------------------------------
// Constantes gráficas
//--------------------------------------------------------------------------------------
const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;

//--------------------------------------------------------------------------------------
// Enumeração de estados de movimento da peça
//--------------------------------------------------------------------------------------
enum Movimento {
    MOVIMENTO_VALIDO,
    MOVIMENTO_INVALIDO,
    MOVIMENTO_NENHUM
};

//--------------------------------------------------------------------------------------
// Estruturas auxiliares para índice e peças do tabuleiro
//--------------------------------------------------------------------------------------
typedef struct {
    int i;
    int j;
} Index2;

///-----> Tipo peça
typedef struct {
    int state;   /// 0 = inválido, 1 = vazio, 2 = peça
    Vector2 pos; /// posição X e Y em pixels
} part;

//--------------------------------------------------------------------------------------
// Função: inicializa_tabuleiro
// Cria o tabuleiro com valores lógicos e posiciona as peças em coordenadas de tela.
//--------------------------------------------------------------------------------------
void inicializa_tabuleiro(part (&tabuleiro)[TAM][TAM]) {
    int inicioX = 280, inicioY = 150;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            /// Transforma as coordenadas em PIXEL
            
            tabuleiro[i][j].pos = { 
             (float)(inicioX + i * (diametro + espaco)), 
             (float)(inicioY + j * (diametro + espaco))
};

            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = 0; // parte inválida = 0
            else
                tabuleiro[i][j].state = 2; // peça = 2
        }
    }

    tabuleiro[3][3].state = 1; // centro vazio = 1
}

//--------------------------------------------------------------------------------------
// Função: desenha_tabuleiro
// Desenha o tabuleiro na tela e destaca a posição atual do mouse.
//--------------------------------------------------------------------------------------
void desenha_tabuleiro(part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == 0) continue;

            Color cor = (tabuleiro[i][j].state == 1) ? LIGHTGRAY : PURPLE;
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);

            // Desenha 3 linhas ao redor do círculo que o mouse sobrepõe
            if (i == i_atual && j == j_atual) {
                for (int k = 0; k < 3; k++)
                    DrawCircleLinesV(tabuleiro[i][j].pos, raio + k, WHITE);
            }
        }
    }
}

//--------------------------------------------------------------------------------------
// Função: calcule_movimento
// Calcula se o movimento da peça é válido, inválido ou nulo.
//--------------------------------------------------------------------------------------
int calcule_movimento(int i_inicial, int j_inicial, int i_final, int j_final) {
    if (i_inicial == i_final && j_inicial == j_final) {
        return MOVIMENTO_NENHUM; // Nenhum movimento
    } else if (i_inicial != i_final && j_inicial != j_final) {
        return MOVIMENTO_INVALIDO; // Movimento diagonal é inválido
    } else if (abs(i_final - i_inicial) == 2 || abs(j_final - j_inicial) == 2) {
        return MOVIMENTO_VALIDO; // Movimento válido (pula 1 casa)
    }

    return MOVIMENTO_INVALIDO;
}

//--------------------------------------------------------------------------------------
// Função: localize_peca
// Localiza a peça mais próxima do mouse. Retorna true se o clique estiver dentro de uma peça.
//--------------------------------------------------------------------------------------
bool localize_peca(part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state = -1) {
    Vector2 Mouse = { (float)GetMouseX(), (float)GetMouseY() };

    double menor = diametro;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == state || state == -1) {
                double a = tabuleiro[i][j].pos.x - Mouse.x;
                double b = tabuleiro[i][j].pos.y - Mouse.y;
                double c = sqrt(pow(a, 2) + pow(b, 2));

                if (c < menor) {
                    menor = c;
                    *ii = i;
                    *jj = j;
                }
            }
        }
    }

    return (menor <= (double)raio);
}


//--------------------------------------------------------------------------------------
// Função: reset_tabuleiro
// Reinicia o estado do tabuleiro para o padrão inicial (como no início do jogo).
//--------------------------------------------------------------------------------------
void reset_tabuleiro(part (&tabuleiro)[TAM][TAM]) {
    inicializa_tabuleiro(tabuleiro);
    std::cout << "Tabuleiro reiniciado!" << std::endl;
}


//-------------------------------------------------------------------------------------
// Função salvar recorde 
// Salva o melhor tempo atual em uma especie ranking
//-------------------------------------------------------------------------------------
void salvarRecorde(const char* nome, float tempo) {
    FILE* arquivo = fopen("recordes.txt", "a"); // abre em modo append
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de recordes!\n");
        return;
    }

    fprintf(arquivo, "%s %.2f\n", nome, tempo);
    fclose(arquivo);
}


//-------------------------------------------------------------------------------------
// Função Mostra o record
// lê e exibe os recordes na tela usando Raylib.
//-------------------------------------------------------------------------------------
void mostrarRecordes() {
    FILE* arquivo = fopen("recordes.txt", "r");
    if (arquivo == NULL) {
        DrawText("Nenhum recorde salvo ainda!", 50, 400, 20, WHITE);
        return;
    }

    char nome[10];
    float tempo;
    int y = 400;

    DrawText("==== RECORDES ====", 50, y, 20, YELLOW);
    y += 30;

    while (fscanf(arquivo, "%s %f", nome, &tempo) == 2) {
        char linha[50];
        sprintf(linha, "%s - %.2f s", nome, tempo);
        DrawText(linha, 50, y, 20, WHITE);
        y += 25;
    }

    fclose(arquivo);
}




//--------------------------------------------------------------------------------------
// Protótipo: AtualizaTabu
// (Ainda não implementada)
//--------------------------------------------------------------------------------------
void AtualizaTabu();

#endif // PROJETO_H_INCLUDED
