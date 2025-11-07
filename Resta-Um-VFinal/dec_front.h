//------ Garante que os arquivos serão usados apenas uma vez ------
#ifndef DEC_FRONT_H_INCLUDED
#define DEC_FRONT_H_INCLUDED

//------ Inclusões ------
#include "raylib.h"
#include <iostream>
#include <math.h>
#include "dec_back.h"

//------ Constantes ------
const int screenWidth = 850;
const int screenHeight = 600;
const float inicioX = screenWidth / 3.2;
const float inicioY = screenHeight / 4;
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

//------ Externs ------
extern Rectangle startButton;
extern Rectangle themeButton;
extern Rectangle resetButton;
extern Rectangle borda;

extern bool temaAtual;
extern Color corBotao;
extern Color corFundo;
extern Color corPeca;
extern Color corTabu;
extern Color corTabuF;
extern Color corTime;
extern Color corERRO;

extern float startTime;

//------ Declaração das funções ------
bool locateButton(Rectangle button);

Rectangle expandRectangle(Rectangle button, float border_size);

bool trocarTema(void);

void Titulo(void);

void Emblema(void);

void DisplayTimer(void);

#endif