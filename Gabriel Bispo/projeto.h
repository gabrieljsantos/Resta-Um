#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED
#include "raylib.h"
#include <iostream>
#include <math.h>

const int fps = 144;
const int screenWidth = 850;
const int screenHeight = 600;
const int TAM = 7;
const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;
const int Movimentos[4][2] = {
    {-2, 0},
    {+2, 0},
    {0, -2},
    {0, +2}
};
extern Color corFundo;
extern Color corPeca;
extern bool temaAtual;

typedef struct
{
    int state;
    Vector2 pos;
} Part;

extern Rectangle startButton;
extern Rectangle themeButton;
extern Rectangle resetButton;
extern Rectangle borda;

enum Clique
{
    CLIQUE_PRIMEIRO,
    CLIQUE_SEGUNDO
};
enum Movimento
{
    MOVIMENTO_VALIDO,
    MOVIMENTO_INVALIDO,
    MOVIMENTO_NENHUM
};
enum Resta
{
    NAO_RESTA_JOGADA,
    RESTA_JOGADA
};
enum PartState
{
    N_EXIST,
    VAZIO,
    PART
};
enum StateJogo
{
    main_Menu,
    STARTGAME,
    RESETGAME,
    ENDGAME
};

extern Part tabuleiro[TAM][TAM];
extern float startTime;
extern int clique_atual;

bool locateButton(Rectangle sri);

Rectangle expandRectangle(Rectangle original, float border_size);

bool trocarTema(void);

bool jogadaValida(Part tabuleiro[TAM][TAM] );

bool validaPart(Part tabuleiro[TAM][TAM], int iTest, int jTest);

bool localizePart(Part tabuleiro[TAM][TAM], int &ii, int &jj, int state = -1);

int calculeMovimento(int i_inicial, int j_inicial, int i_fim, int j_fim);

void Titulo(void);

void Emblema(void);

void Jogada(void);

void imprimeTabuleiro(Part tabuleiro[TAM][TAM]);

void imprimeTabuleiro(Part tabuleiro[TAM][TAM], int i_atual, int j_atual, int clique_atual);

void DisplayTimer(void);

#endif // PROJETO_H_INCLUDED