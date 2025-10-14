#include "raylib.h"
#include <stdio.h>

//------------------------------------------------------------------------------------
/// Fun��o principal do programa
//------------------------------------------------------------------------------------
int main(void)
{
    // Inicializa��o
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "RESTA UM");

    SetTargetFPS(60);               /// Define o jogo para rodar a 60 quadros por segundo
    //--------------------------------------------------------------------------------------

    // Loop principal do jogo
    while (!WindowShouldClose())    /// Detecta se o bot�o de fechar foi clicado ou se ESC foi pressionado
    {
        // Atualiza��o
        //----------------------------------------------------------------------------------
        // TODO: Atualize suas vari�veis aqui
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

    // Desinicializa��o
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Fecha a janela e o contexto OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}
