// iNCLUSÃO DE BIBLIOTECAS
#include "raylib.h"
#include <locale.h>
#include "projeto.h"
#include <iostream>
using namespace std;

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    cout << "\033[32m"<<std::endl; // Muda a cor do terminal para verde

    // INICIALIZAÇÃO
    InitWindow(screenWidth, screenHeight, "RESTA UM - 60FPS");
    SetTargetFPS(fps);

    stateJogo jogo = main_Menu;
    int i_inicial = 0, j_inicial = 0, aux;

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(corFundo);

        switch (jogo) {
            case main_Menu:
                    Emblema();
                    if(locateButton(startButton)) {
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            inicializa_tabuleiro(tabuleiro); // inicia o tabuleiro um vez somente!
                            startTime = GetTime(); 
                            jogo = STARTGAME;
                        }
                    }
                break;

            case STARTGAME:
                    localize_Part(tabuleiro, &i_inicial, &j_inicial);
                    desenha_tabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
                    Jogada();
                    Titulo();
                     
                    if(locateButton(restartButton)) // Botão restart
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogo = RESTARTGAME;
                        }
                    if(locateButton(themeButton)){ // Botão tema
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            trocarTema();
                        }
                    if(!jogada_Valida(tabuleiro,aux)) jogo = ENDGAME;// se NÃO TIVER JOGADA VALIDA
                    }
            
                break;

                case RESTARTGAME:
                    desenha_tabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
                    Titulo();
                    startTime = GetTime();
                    inicializa_tabuleiro(tabuleiro);
                        jogo = STARTGAME;

                break;

                case ENDGAME:
                    desenha_tabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
                    Titulo();
                    if(locateButton(restartButton)) 
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogo = RESTARTGAME;
                        }
                    
                    if(locateButton(themeButton)){
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            trocarTema();
                        }
                
                    }
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
