#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED
#include "raylib.h"
#include <iostream>
#include <math.h>
#include "logica.h"
#include "const.h"



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

bool locateButton(Rectangle button);

Rectangle expandRectangle(Rectangle button, float border_size);

bool trocarTema(void);

void Titulo(void);

void Emblema(void);

void desenhaTabuleiro(Part tabuleiro[TAM][TAM], int i_atual, int j_atual, int clique_atual);

void DisplayTimer(void);

#endif 