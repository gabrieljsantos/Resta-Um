#include "raylib.h"
#include <locale.h>
#include "projeto.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese"); // configura a linguagem para português
    
    
    
    // Initialization
    //--------------------------------------------------------------------------------------   

    InitWindow(screenWidth, screenHeight, "TELA 60FPS");
    int i_inicial=0, j_inicial=0;

   
    SetTargetFPS(60);             // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    stateJogo jogo = INICIO;
        
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

        switch (jogo){

        case INICIO:
            Emblema();
            if(locale_Button()){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    inicializa_tabuleiro(tabuleiro);
                    jogo=PLAY;
                }
            }
            break;
        case PLAY:
            //DrawRectangle(inicioX-40,inicioY-40,440,440,BROWN);
            Atualiza_Imformação();
            desenha_tabuleiro(tabuleiro,i_inicial,j_inicial,-1);
            Jogada();
            Titulo();
            if(locale_Reset()){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    jogo = RESET;
                }
            }
            break;
        // case ESCOLHE:
        //     /* code */
        //     break;
        
        // case MOVI:
        //     /* code */
        //     break;
        
        case RESET:
            inicializa_tabuleiro(tabuleiro);
            jogo=PLAY;
            break;
        
        // case TEMA:
        //     /* code */
        //     break;
        
        // case FIMDEJOGO:
        //     /* code */
        //     break;
        
        default:

            break;
        }



        ///------------------
        /*/ PLAY GAME ---> *///renderiza_Jogo();
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
