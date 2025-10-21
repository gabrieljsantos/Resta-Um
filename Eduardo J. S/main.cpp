// iNCLUSÃO DE BIBLIOTECAS

#include "raylib.h"
#include <locale.h>
#include "projeto.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    // Initialization
    InitWindow(screenWidth, screenHeight, "RESTA UM - 60FPS");
    SetTargetFPS(60);

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
                        startTime = GetTime();  // TIMER INICIA
                        jogo = PLAY;
                    }
                }
                break;

            case PLAY:
            Atualiza_Imformacao();
            localize_Part(tabuleiro, &i_inicial, &j_inicial);
            desenha_tabuleiro(tabuleiro, i_inicial, j_inicial, false);
            Jogada();
            Titulo();

            if(locale_Reset()) {
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    startTime = GetTime();
                    jogo = RESET;
                }
            }

            if(locale_Muda()){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    trocarTema();
                    std::cout << "Botão TEMA clicado!" << std::endl;
                }
                // Highlight do botão TEMA
                for(int i = 0; i < 4; i++) {
                    DrawRectangleLines(30-i, 500-i, 100+i, 45+i, GREEN);
                }
            }
            break;

            case RESET:
                inicializa_tabuleiro(tabuleiro);
                jogo = PLAY;
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
