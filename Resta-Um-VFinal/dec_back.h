
#ifndef DEC_BACK_H_INCLUDED
#define DEC_BACK_H_INCLUDED

#include "dec_front.h"
#include "raylib.h"
#include <iostream>
#include <math.h>

#define MAX_RECORDES 10

typedef struct {
    char nome;   // A-J
    float tempo;
} Recorde;


typedef struct{
    int state;
    Vector2 pos;
} Part;

const int cima = -2;
const int baixo = +2;
const int esquerda = -2;
const int direita = +2;
const int atual = 0;

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


bool jogadaValida(Part tabuleiro[TAM][TAM]);

bool jogadaValida(Part tabuleiro[TAM][TAM], int iTest, int jTest);

bool localizePart(Part tabuleiro[TAM][TAM], int &ii, int &jj, int state = -1);

int calculeMovimento(int i_inicial, int j_inicial, int i_fim, int j_fim);

void imprimeTabuleiro(Part tabuleiro[TAM][TAM]);

void imprimeTabuleiro(Part tabuleiro[TAM][TAM], int i_atual, int j_atual, int clique_atual);

void jogada();

void salvarRecorde(char inicial, float tempo);

int carrega_recordes(Recorde recs[MAX_RECORDES]);

void ordena_recordes(Recorde recs[], int count);

void mostrarRecordesOrdenados(void);


#endif
