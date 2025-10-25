#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

#include "raylib.h"
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

// Constantes
const int screenWidth = 850;
const int screenHeight = 600;
const int TAM = 7;
const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;
const int Movimentos[4][2] = {
    {-2, 0}, // Cima
    {+2, 0}, // Baixo
    {0, -2}, // Esquerda
    {0, +2}  // Direita
};
extern Color corFundo;      // Fundo (Preto/Branco)
extern Color corPeca;       // Peças (Roxo/Marrom)
extern bool temaAtual;      // TRUE = Tema 1, FALSE = Tema 2


// Estruturas
typedef struct {
    int state;   // 0 = invalido, 1 = vazio, 2 = peça
    Vector2 pos; // posição X e Y
    bool valida;
} Part;

// Enumeradores
enum Clique { CLIQUE_PRIMEIRO, CLIQUE_SEGUNDO };
enum Movimento { MOVIMENTO_VALIDO, MOVIMENTO_INVALIDO, MOVIMENTO_NENHUM };
enum Resta { NAO_RESTA_JOGADA, RESTA_JOGADA};
enum PART_STATE {N_EXIST, VAZIO, EXIST};
enum stateJogo {MAIN_MENU, PLAY, RESET, FIMDEJOGO};

// Variáveis globais
extern Part tabuleiro[TAM][TAM];
extern float startTime;  // TIMER SIMPLES
extern int clique_atual;

// Protótipos de funções

// Função para verificar se um ponto está dentro de uma área
bool checks_if_the_mouse_is_in_an_area(Vector2 cp, Rectangle sri);
// Expande um retângulo adicionando borda
Rectangle ExpandRectangle(Rectangle original, int border_size);
bool locale_Button();
bool locale_Reset();
bool locale_Muda();
bool trocarTema(void);
bool jogada_Valida(Part (&tabuleiro)[TAM][TAM], int (&Resta));
bool valida_Part(Part (&tabuleiro)[TAM][TAM], int It, int Jt, int (&S));
bool localize_Part(Part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state = -1);
int calcule_movimento(int i_inicial, int j_inicial, int i_final, int j_final);
void Titulo(void);
void Emblema(void);
void Jogada(void);
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]);
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, int clique_atual);
void renderiza_Jogo(void);
void DisplayTimer(void);  // SEM PARÂMETRO

// Definição da estrutura de cores do tema
typedef struct {
    Color BackgroundColor;
    Color PartColor;
    Color ButtonColor;
    Color BoardColor;
    Color BoardBorderColor;
    Color TimeColor;
    Color ButtonBoardColor; // novo
    Color TextColor;        // novo
}Theme;

// Valores diretos em RGBA
Theme white_beige = {
    {245, 245, 220, 255}, // BackgroundColor
    {101, 67, 33, 255},   // PartColor
    {165, 42, 42, 255},   // ButtonColor
    {165, 42, 42, 255},   // BoardColor
    {101, 67, 33, 255},   // BoardBorderColor
    {0, 0, 0, 255},       // TimeColor
    {210, 180, 140, 255}, // ButtonBoardColor
    {0, 0, 0, 255}        // TextColor
};

Theme dark_purple = {
    {0, 0, 0, 255},       // BackgroundColor
    {128, 0, 128, 255},   // PartColor
    {75, 0, 130, 255},    // ButtonColor
    {0, 0, 0, 255},       // BoardColor
    {0, 0, 0, 255},       // BoardBorderColor
    {255, 215, 0, 255},   // TimeColor
    {75, 0, 130, 255},    // ButtonBoardColor
    {255, 255, 255, 255}  // TextColor
};

Theme ocean_blue = {
    {28, 107, 160, 255},  // BackgroundColor
    {0, 191, 255, 255},   // PartColor
    {0, 128, 255, 255},   // ButtonColor
    {0, 105, 148, 255},   // BoardColor
    {0, 82, 117, 255},    // BoardBorderColor
    {255, 255, 255, 255}, // TimeColor
    {0, 128, 255, 255},   // ButtonBoardColor
    {255, 255, 255, 255}  // TextColor
};

Theme forest_green = {
    {34, 139, 34, 255},   // BackgroundColor
    {0, 100, 0, 255},     // PartColor
    {46, 139, 87, 255},   // ButtonColor
    {0, 128, 0, 255},     // BoardColor
    {0, 100, 0, 255},     // BoardBorderColor
    {255, 255, 255, 255}, // TimeColor
    {46, 139, 87, 255},   // ButtonBoardColor
    {255, 255, 255, 255}  // TextColor
};

Theme sunset_orange = {
    {255, 99, 71, 255},   // BackgroundColor
    {255, 140, 0, 255},   // PartColor
    {255, 165, 0, 255},   // ButtonColor
    {255, 127, 80, 255},  // BoardColor
    {255, 99, 71, 255},   // BoardBorderColor
    {0, 0, 0, 255},       // TimeColor
    {255, 165, 0, 255},   // ButtonBoardColor
    {0, 0, 0, 255}        // TextColor
};

white_beige.
#endif // PROJETO_H_INCLUDED
