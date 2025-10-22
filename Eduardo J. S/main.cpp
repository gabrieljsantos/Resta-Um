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
                            startTime = GetTime(); 
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

                    if(locale_Reset()) 
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogo = RESET;
                        }
                    

                    if(locale_Muda()){
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            trocarTema();
                            std::cout << "Botão TEMA clicado!" << std::endl;
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

