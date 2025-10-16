#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

#include "raylib.h"
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <cstdlib>
#include <stdlib.h>

const int TAM =7; 

const int dois = 2; //tipo uma const


const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;

enum Movimento {
    MOVIMENTO_VALIDO,
    MOVIMENTO_INVALIDO,
    MOVIMENTO_NENHUM
};


 





///-----> Tipo peça
typedef struct {
    int state;   /// 0 = invalido, 1 = vazio, 2 = peça
    Vector2 pos; ///posicão X e Y
} part;

/// Tabuleiro
part tabuleiro[TAM][TAM];

enum Clique {
    CLIQUE_PRIMEIRO,
    CLIQUE_SEGUNDO
};

typedef struct {// ---> BOTAO DO MINI MENU
    bool state = true;
    Vector2 local;
} botao;

botao menu[dois] = {
       // menu[0][0]
        { true, {740.0f, 530.0f} },
        // menu[0][1]
        { true, {830.0f, 530.0f} }
};    


bool localiza_BOTAO(botao (&menu)[dois], int* li); //Assinatura 
// --- BOTAO DE RESENT
void Botoes(botao(&menu)[dois]){

    for(int i = 0; i < 2; i++){
            if(menu[i].state){
                //DrawRectangle(menu[i][j].local.x, menu[i][j].local.y,80,50, (j==0)? PURPLE : GRAY);
                DrawCircle(menu[i].local.x, menu[i].local.y, (float)raio, (i==0)? PURPLE : GRAY);
                DrawText("RESET",711, 554, 20, RED);
                DrawText("RESET",711, 556, 20, RED);
                
            }
    
    }
}
 

///--------------------------------------------------------------> Cria o Tabuleiro com valores logicos (0 vazio), (2 peça), (1 centro)

void inicializa_tabuleiro(part (&tabuleiro)[TAM][TAM]) {
    int inicioX = 280, inicioY = 150;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
                                         ///Transaforma as coordenadas em PIXEL
            tabuleiro[i][j].pos ={ (float)inicioX + i * (diametro + espaco), (float)inicioY + j * (diametro + espaco) };

            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = 0; // parte vazia = 0
            else
                tabuleiro[i][j].state = 2; // peça = 2

        }
    }

    tabuleiro[3][3].state = 1; // centro vazio = 1
}
///--------------------------------------------------------------> Desneha o tabuleiro

void desenha_tabuleiro(part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, bool red) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tabuleiro[i][j].state == 0) continue;

            Color cor = (tabuleiro[i][j].state == 1) ? LIGHTGRAY : PURPLE;

            DrawCircleV(tabuleiro[i][j].pos, raio, cor);

            // Desenha 3 linhas ao redor do circulo cujo o mouse está sobrepondo no momento
            if (i == i_atual && j == j_atual) {
                for (int k = 0; k < 4; k++)
                    DrawCircleLinesV(tabuleiro[i][j].pos, raio + k, red ? RED : GREEN);
            }
        }
    }
}

// 3 = mesmo lugar, 0 = invalido, 1 = i variou, 2 = j variou (nao importa muito a direcao)
int calcule_movimento(int i_inicial, int j_inicial, int i_final, int j_final) {
    if (i_inicial == i_final && j_inicial == j_final) { // Nenhum movimento
        return MOVIMENTO_NENHUM;
    } else if (i_inicial != i_final && j_inicial != j_final) { // Movimento diagonal
        return MOVIMENTO_INVALIDO;
    } else if (abs(i_final - i_inicial) == 2 || abs(j_final - j_inicial) == 2) { // Unica possibilidade
        return MOVIMENTO_VALIDO;
    }

    return MOVIMENTO_INVALIDO;

}

// Para localizar BUTAO
bool localiza_BOTAO(botao (&menu)[dois], int* li){
    Vector2 mouse = GetMousePosition();
    
    double menor = diametro; // RECEBE O VALOR DO DIAMETRO
    for(int i = 0; i < dois; i++){
            double a = menu[i].local.x - mouse.x;
            double b = menu[i].local.y - mouse.y;

            double c = sqrt( pow(a,2) + pow(b,2));
         
            if (c < menor){
                *li = i; 
                menor =c;
            }
        
    }
    if (menor <= (double)raio) {
            return true;
        }

    return false;

}

// Para localizar peca valida 
bool localize_peca(part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state = -1) {
        Vector2 Mouse = {(float)GetMouseX(), (float)GetMouseY()};

        double menor = diametro;

        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (tabuleiro[i][j].state == state || state == -1) {
                    double a = tabuleiro[i][j].pos.x -  Mouse.x;
                    double b = tabuleiro[i][j].pos.y -  Mouse.y;

                    double c = sqrt(pow(a, 2) + pow(b, 2));

                    if (c < menor) {
                        menor = c;
                        *ii = i;
                        *jj = j;
                    }
                }
            }
        }

        if (menor <= (double)raio) {
            return true;
        }

        return false;
}

void renderiza_Jogo(){


Botoes(menu);



}



#endif // PROJETO_H_INCLUDED
