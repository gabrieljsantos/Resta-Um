// iNCLUSÃO DE BIBLIOTECAS
#include "setup.h"
// Biblioteca cujo apresenta todas as definicoes, e valores das contantes que podem não ter sua declaração na proximidade do uso.
#include "raylib.h"
// Biblioteca usada para renderizar todo o front-end.
#include "enumclass.h"

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
    int Current_Theme = 0;

    // Main game loop
    while (!WindowShouldClose())
    {


        BeginDrawing();
        ClearBackground(corFundo);
        /*
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
        }
        */
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

