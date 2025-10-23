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
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]);
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, int clique_atual);
void renderiza_Jogo(void);
void DisplayTimer(void);  // SEM PARÂMETRO

#endif // PROJETO_H_INCLUDED
