// INCLUSÃO DE BIBLIOTECAS
#include "logica.h"
#include "interface.h"

int main(void)
{

    // INICIALIZAÇÃO
    InitWindow(screenWidth, screenHeight, "RESTA UM - 60FPS");

    StateJogo jogo = main_Menu;
    int j_inicial;
    int i_inicial;


    

    while (!WindowShouldClose())
    {
        SetTargetFPS(60);
        BeginDrawing();
        ClearBackground(corFundo);
        

        switch (jogo){
        case main_Menu:
            Emblema();
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(locateButton(startButton)){
                    inicializaTabuleiro(tabuleiro); 
                    startTime = GetTime();
                    jogo = STARTGAME;
                }
            }
            break;

        case STARTGAME:
            localizePart(tabuleiro, i_inicial, j_inicial);
            desenhaTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();
            jogada();

            if (!jogadaValida(tabuleiro))
                jogo = ENDGAME;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                
                if (locateButton(resetButton))
                    jogo = RESETGAME;

                if (locateButton(themeButton))
                    trocarTema();
            }
                
            break;

        case RESETGAME:
            desenhaTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();
            startTime = GetTime();
            inicializaTabuleiro(tabuleiro);
            jogo = STARTGAME;

            break;

        case ENDGAME:
            desenhaTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                
                if (locateButton(resetButton))
                    jogo = RESETGAME;

                if (locateButton(themeButton))
                    trocarTema();
            }
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
