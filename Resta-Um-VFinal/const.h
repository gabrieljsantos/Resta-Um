#ifndef CONST_H
#define CONST_H
#include "raylib.h"

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

typedef struct{
    int state;
    Vector2 pos;
} Part;

#endif
