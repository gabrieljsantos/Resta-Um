// INCLUSÃO DE BIBLIOTECAS
#include <locale.h>
#include "projeto.h"

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
                            inicializaTabuleiro(tabuleiro); // inicia  o tabuleiro um vez somente!
                            startTime = GetTime(); 
                            jogo = STARTGAME;
                        }
                    }
                break;

            case STARTGAME:
                    localizePart(tabuleiro, &i_inicial, &j_inicial);
                    desenhaTabuleiro(tabuleiro, i_inicial, j_inicial, clique_atual);
                    Jogada();
                    Titulo();
                     
                    if(locateButton(restartButton)) // Botão restart
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogo = RESETGAME;
                        }
                    if(locateButton(themeButton)){ // Botão tema
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                            trocarTema();
                        }
                    if(!jogadaValida(tabuleiro,aux)) jogo = ENDGAME;// se NÃO TIVER JOGADA VALIDA
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
                    if(locateButton(restartButton)) 
                        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        jogo = RESETGAME;
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
