#ifndef LOGICA_H_INCLUDED
#define LOGICA_H_INCLUDED

#include "interface.h"
#include "raylib.h"
#include <iostream>
#include <math.h>
#include "const.h"


extern Part tabuleiro[TAM][TAM];
extern int restaPart;
extern int i_atual, j_atual;
extern int aux_ci, aux_cj;

extern int clique_atual;

enum Clique{
    CLIQUE_PRIMEIRO, CLIQUE_SEGUNDO};

enum Movimento{
    MOVIMENTO_VALIDO, MOVIMENTO_INVALIDO, MOVIMENTO_NENHUM};

enum RestaJogo{ 
    NAO_RESTA_JOGADA, RESTA_JOGADA};

enum PartState{
     N_EXIST, VAZIO, PART};

enum StateJogo{
     main_Menu, STARTGAME, RESETGAME, ENDGAME};

bool jogadaValida(Part tabuleiro[TAM][TAM] );

bool validaPart(Part tabuleiro[TAM][TAM], int iTest, int jTest);

bool localizePart(Part tabuleiro[TAM][TAM], int &ii, int &jj, int state = -1);

int calculeMovimento(int i_inicial, int j_inicial, int i_fim, int j_fim);

void imprimeTabuleiro(Part tabuleiro[TAM][TAM]);

void imprimeTabuleiro(Part tabuleiro[TAM][TAM], int i_atual, int j_atual, int clique_atual);


void jogada();



#endif 