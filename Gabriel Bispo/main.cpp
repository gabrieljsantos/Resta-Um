// iNCLUSÃO DE BIBLIOTECAS

#include "raylib.h"
#include <locale.h>
#include "projeto.h"
#include <iostream>
using namespace std;

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    cout << "\033[32m"; // Muda a cor do texto para verde

    // Initialization
    InitWindow(screenWidth, screenHeight, "RESTA UM - 60FPS");
    SetTargetFPS(144);

    stateJogo jogo = INICIO;
    int i_inicial = 0, j_inicial = 0;

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(corFundo);

        switch (jogo) {
            case INICIO:
                    Emblema();
                    if(locale_Button()) {
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            inicializa_tabuleiro(tabuleiro);
                            startTime = GetTime(); 
                            jogo = PLAY;
                        }
                    }
                break;

            case PLAY:
                    localize_Part(tabuleiro, &i_inicial, &j_inicial);
                    desenha_tabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
                    Jogada();
                    Titulo();

                    if(locale_Reset()) 
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogo = RESET;
                        }
                    

                    if(locale_Muda()){
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            trocarTema();
                        }
                
                    }
            
                break;

                case RESET:
                    Titulo();
                    startTime = GetTime();
                    inicializa_tabuleiro(tabuleiro);
                        jogo = PLAY;
                    break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

