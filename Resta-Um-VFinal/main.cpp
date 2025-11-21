#include "dec_back.h"
#include "dec_front.h"

int main(void)
{

    // INICIALIZA��O
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
            mostrarRecordesOrdenados();
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
            imprimeTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();
            startTime = GetTime();
            imprimeTabuleiro(tabuleiro);
            jogo = STARTGAME;

            break;

        case ENDGAME:
            imprimeTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
            Titulo();                    // j� salva + mostra vit�ria
            mostrarRecordesOrdenados();  // mostra recordes
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if (locateButton(resetButton)) jogo = RESETGAME;
                if (locateButton(themeButton)) trocarTema();
            }
            break;
                }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
