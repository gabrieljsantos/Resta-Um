// iNCLUSÃO DE BIBLIOTECAS
#include "setup.h"
// Biblioteca cujo apresenta todas as definicoes, e valores das contantes que podem não ter sua declaração na proximidade do uso.
#include "raylib.h"
// Biblioteca usada para renderizar todo o front-end.
#include "enumclass.h"
#include "themesclass.h"

#include <locale.h>
//#include "projeto.h"
#include <iostream>
using namespace std;

int main(void)
{
    //Initialization of terminal
    setlocale(LC_ALL, "Portuguese");
    cout << "\033[32m"<<std::endl; // Muda a cor do terminal para verde

    //Initialization of windows
    InitWindow(screen.x, screen.y, NAME_OF_WINDOW);
    SetTargetFPS(FPS);

    //Initialization of games status init
    game_state jogo = MAIN_MENU; // Indica que o estado do jogo deve começar indo diretamente para o menu
    int i_inicial = 0; //?
    int j_inicial = 0; //?
    int r; // quem é r?
    Theme colors_theme = white_beige;

    // Main game loop
    while (!WindowShouldClose())
    {


        BeginDrawing();
        ClearBackground(colors_theme.BackgroundColor);
        
        switch (jogo) {
            case MAIN_MENU:
                DrawText("Resta Um", screen.x/2, screen.y + 50, 100, colors_theme.PartColor);
                DrawRectangleRec(start_button_pos, colors_theme.ButtonColor);
                DrawText("START", screen.x/2-43, screen.y/2+70, 25, BLACK);

                if(locale_Button()){
                    for(int i = 0; i < 4; i++){
                        DrawRectangleLines(350-i, 350-i, 152+i, 72+i, GREEN);
                    }
                }
                    if(locale_Button()) {
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            inicializa_tabuleiro(tabuleiro);
                            startTime = GetTime();
                            jogo = PLAY;
                        }
                    }
                break;

            /*
            case PLAY:
                    localize_Part(tabuleiro, &i_inicial, &j_inicial);
                    desenha_tabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
                    Jogada();
                    Titulo();
                    if(!jogada_Valida(tabuleiro, r)) jogo = FIMDEJOGO;

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
                    desenha_tabuleiro(tabuleiro,i_inicial,j_inicial,clique_atual);
                    Titulo();
                    startTime = GetTime();
                    inicializa_tabuleiro(tabuleiro);
                        jogo = PLAY;

                break;

                case FIMDEJOGO:
                    desenha_tabuleiro(tabuleiro,i_inicial,j_inicial,clique_atual);
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

                */
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

