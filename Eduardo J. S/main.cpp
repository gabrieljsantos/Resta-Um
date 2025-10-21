#include "raylib.h"
#include <locale.h>
#include "projeto.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese"); // configura a linguagem para português
    
    
    // Initialization
    //--------------------------------------------------------------------------------------   

    InitWindow(screenWidth, screenHeight, "TELA 60FPS");

    SetTargetFPS(60);             // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

            

        //----------------------------------------------------------------------------------

        // Draw
        
                
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ///------------------
        /*/ PLAY GAME ---> */renderiza_Jogo();
        ///-------------------
    
        ClearBackground(BLACK);// COR DE FUNDO

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
