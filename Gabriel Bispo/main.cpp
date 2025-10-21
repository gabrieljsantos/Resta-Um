#include "raylib.h"
#include "projeto.h"

int main(void)
{
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
            if(locale_Button()){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    jogo = RESET;
                }
            }
            break;
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
