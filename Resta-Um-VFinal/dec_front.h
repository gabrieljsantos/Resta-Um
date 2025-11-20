// Garante que os arquivos serão usados apenas uma vez
#ifndef DEC_FRONT_H_INCLUDED
#define DEC_FRONT_H_INCLUDED

//------ Inclusões ------
#include "raylib.h"
#include <iostream>
#include <math.h>
#include "dec_back.h"

//------ Constantes ------
const int screenWidth = 950;
const int screenHeight = 700;
const float inicioX = screenWidth / 3.2;
const float inicioY = screenHeight / 4;
const int TAM = 7;
const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;
const Rectangle resetButton = {820.0f, 600.0f, 100.0f, 45.0f};
const Rectangle startButton = {screenWidth/2 - 75, screenHeight /2 +45, 150.0f, 70.0f};
const Rectangle themeButton = {30.0f, 600.0f, 100.0f, 45.0f};
const Rectangle fundoMaior = {inicioX-50, inicioY-50, 460, 460};
const Rectangle fundoMenor = {inicioX-40, inicioY-40, 440,440};

//------ Externs ------

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

void DisplayTimer(void);

void salvarRecordeAutomatico(void);

#endif
