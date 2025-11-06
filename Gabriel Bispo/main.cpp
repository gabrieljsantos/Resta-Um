// INCLUSÃO DE BIBLIOTECAS
#include <locale.h>
#include "projeto.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    // INICIALIZAÇÃO
    InitWindow(screenWidth, screenHeight, "RESTA UM - 60FPS");

    StateJogo jogo = main_Menu;
    int i_inicial = 0, j_inicial = 0; 

    while (!WindowShouldClose())
    {
        SetTargetFPS(fps);
        BeginDrawing();
        ClearBackground(corFundo);
        

        switch (jogo){
        case main_Menu:
            Emblema();
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(locateButton(startButton)){
                    imprimeTabuleiro(tabuleiro); 
                    startTime = GetTime();
                    jogo = STARTGAME;
                }
            }
            break;

        case STARTGAME:
            localizePart(tabuleiro, i_inicial, j_inicial);
            imprimeTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();
            Jogada();

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
            imprimeTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();
            startTime = GetTime();
            imprimeTabuleiro(tabuleiro);
            jogo = STARTGAME;

            break;

        case ENDGAME:
            imprimeTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
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
