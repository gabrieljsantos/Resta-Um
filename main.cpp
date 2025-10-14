#include "raylib.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
/// Função principal do programa
//------------------------------------------------------------------------------------
int main(void)
{
    // Inicialização
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "RESTA UM");

    SetTargetFPS(60);               /// Define o jogo para rodar a 60 quadros por segundo
    //--------------------------------------------------------------------------------------

    // Loop principal do jogo
    while (!WindowShouldClose())    /// Detecta se o botão de fechar foi clicado ou se ESC foi pressionado
    {
        // Atualização
        //----------------------------------------------------------------------------------
        // TODO: Atualize suas variáveis aqui
        //----------------------------------------------------------------------------------




        // Desenho
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);

            DrawText("Gabriel", 50, 190, 50, BLACK);

            const int x=0,y=0;

                if(x == const int 300) x=0;
                if(y == const int 300) y=0;

                DrawText("\nMANICRAFT", 190 + x, 250 + y, 50, BLUE);

                x=+5;
                y=+5;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Desinicialização
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Fecha a janela e o contexto OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}
