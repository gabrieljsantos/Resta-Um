#ifndef SETUP_H_INCLUDED
#define SETUP_H_INCLUDED

#include "structs.h" // inclusão de todas as estruturas usadas
#include "raylib.h"

//Initial statements and definition of preferences

// Constantes
const VectorXY screen = {850, 600};
const char* NAME_OF_WINDOW = "RESTA UM";
const int FPS = 144;
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

Rectangle restart_button_pos = {700, 500, 100, 45}; // posiçoes dos botaos
Rectangle start_button_pos = {350, 350, 150, 70}; 
Rectangle Muda_button_pos = {30, 500, 100, 45};


#endif // SETUP_H_INCLUDED
