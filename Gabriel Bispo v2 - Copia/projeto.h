#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

#include "raylib.h"
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>



extern Color corPeca;       // Peças (Roxo/Marrom)
extern bool temaAtual;      // TRUE = Tema 1, FALSE = Tema 2


// Estruturas
typedef struct {
    int state;   // 0 = invalido, 1 = vazio, 2 = peça
    Vector2 pos; // posição X e Y
    bool valida;
} Part;



void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]);

// Enumeradores
enum click_order{PRIMEIRO, SEGUNDO};
enum types_of_movement{VALID, INVALID, NONE};
enum is_possible_to_move{NOT, YES};
enum part_state{NOT_EXISTS, EMPTY_SPACE, EXISTS};
enum game_state {MAIN_MENU, PLAY, RESET, END_GAME};

// Função para verificar se um ponto está dentro de uma área
bool checks_if_the_mouse_is_in_an_area(Vector2 cp, Rectangle sri);

// Expande um retângulo adicionando borda
Rectangle ExpandRectangle(Rectangle original, int border_size);



//Initial statements and definition of preferences

// Constantes
const Vector2 screen = {850, 600};
const int inicioX = screen.x/3.5; // origem da renderização
const int inicioY = screen.y/4; // origem da renderização
const char* NAME_OF_WINDOW = "RESTA UM";
const int FPS = 144;
const int TAM = 7 ; // Tamanho do tabululeiro
const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;
const int Movimentos[4][2] = {
    {-2, 0}, // Cima
    {+2, 0}, // Baixo
    {0, -2}, // Esquerda
    {0, +2}  // Direita
};

Part tabuleiro[TAM][TAM];
const int button_border_size = 10;
Rectangle restart_button_pos = {700, 500, 100, 45}; // posiçoes dos botaos
Rectangle start_button_pos = {350, 350, 150, 70}; 
Rectangle Muda_button_pos = {30, 500, 100, 45};





// Variáveis globais
extern Part tabuleiro[TAM][TAM];
extern float startTime;  // TIMER SIMPLES
extern int clique_atual;

// Protótipos de funções
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
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, int clique_atual);
void renderiza_Jogo(void);
void DisplayTimer(void);  // SEM PARÂMETRO

#endif // PROJETO_H_INCLUDED
