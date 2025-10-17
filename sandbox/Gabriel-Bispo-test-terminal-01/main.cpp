#include "raylib.h"

#include <locale.h>

#include "projeto.h"



int main(void)
{
    setlocale(LC_ALL, "Portuguese"); // configura a linguagem para português


    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "TELA 60FPS");

    SetTargetFPS(288);             // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    inicializa_tabuleiro(tabuleiro);

    int i_inicial = 0, j_inicial = 0; // Coordenada do clique previo

    Color mouse_circle = GREEN;

   

    unsigned int error_fps_counter = 0;
    bool red = false;

    int clique_atual = CLIQUE_PRIMEIRO;



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here

        //----------------------------------------------------------------------------------

        // Draw
        DrawText("----- RESTA UM -----", 350, 50, 20,PURPLE);

                
        //----------------------------------------------------------------------------------
        BeginDrawing();

        
        // Botoes(menu);
        renderiza_Jogo();
       
        

        
        //DrawRectangle(450 , 370, 200, 200, RED);
        mouse_circle = GREEN;

        if (error_fps_counter > 0) {
            if (error_fps_counter % 5 == 0) { // A cada 5 frames
                red = !red; // Inverte a cor
            }
            if (red) mouse_circle = RED;
            error_fps_counter--;
        }


        clique_atual = (i_inicial == 0 && j_inicial == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;

        int i_atual = 0, j_atual = 0;
        localize_peca(tabuleiro, &i_atual, &j_atual);

        if (clique_atual == CLIQUE_PRIMEIRO) {
            desenha_tabuleiro(tabuleiro, i_atual, j_atual, tabuleiro[i_atual][j_atual].state != 2);
        } else {
            int movimento = calcule_movimento(i_inicial, j_inicial, i_atual, j_atual);
            desenha_tabuleiro(tabuleiro, i_atual, j_atual, movimento != MOVIMENTO_VALIDO);
        }


        //std::cout << movimento << std::endl;

        Vector2 pos = GetMousePosition(); // Pega posição (x,y) do mouse

        int ii;
         if( localiza_BOTAO( menu,&ii)){
                for(int i =0;i<4;i++)
                    DrawCircleLinesV(menu[ii].local,(float)raio +i , (ii==0)? GREEN:RED);
                    std :: cout << "achou "<< ii << "\n";
         }
                
       

        ///teste de funcao
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            // Index2 clique = Index_XY();

            if (clique_atual == CLIQUE_PRIMEIRO) { // Primeiro click
                if (localize_peca(tabuleiro, &i_inicial, &j_inicial, 2)) { // Captura primeiro click. state = 2 tem que ser peça
                    //DrawCircleV(mouse, 40, RED);
                    std::cout << "Primeiro clique na posição X: " << tabuleiro[i_inicial][j_inicial].pos.x << ", Y: " << tabuleiro[i_inicial][j_inicial].pos.y << std::endl;
                }
            } else { // Segundo click
                int i_final = 0, j_final = 0;
                if (localize_peca(tabuleiro, &i_final, &j_final, 1)) { // State = 1 tem que estar vazio
                   // DrawCircleV(mouse, 40, RED);
                    
                    std::cout << "Segundo clique na posição X: " << tabuleiro[i_final][j_final].pos.x << ", Y: " << tabuleiro[i_final][j_final].pos.y << std::endl;

                    int movimento = calcule_movimento(i_inicial, j_inicial, i_final, j_final);
                    if (movimento == MOVIMENTO_INVALIDO) {
                        std::cout << "Movimento inválido " << "I: " << i_inicial << " J: " << j_inicial << " para I2: " << i_final << " J2: " << j_final << std::endl;
                        error_fps_counter = 60; // = 1 segundo
                    } else {
                        int i_alvo = (i_inicial + i_final) / 2; // I do meio
                        int j_alvo = (j_inicial + j_final) / 2; // J do meio

                        if (tabuleiro[i_alvo][j_alvo].state == 2) { // Apenas se a casa do meio estiver uma bola
                            std::cout << "Deletando em i = " << i_alvo << "; j = " << j_alvo << std::endl;

                            tabuleiro[i_alvo][j_alvo].state = 1;
                            tabuleiro[i_final][j_final].state = 2;
                            tabuleiro[i_inicial][j_inicial].state = 1;
                        } else {
                            error_fps_counter = 60; // = 1 segundo
                        }
                    }

                    if (movimento != MOVIMENTO_NENHUM) {
                        i_inicial = 0; i_final = 0; j_inicial = 0; j_final = 0; // Reseta e aguarda próximo lance
                    }
                }
            }
         }

        BeginDrawing();
        ClearBackground(BLACK);

        //DrawCircleV(pos, 20, mouse_circle); // desenha bolinha na posição do mouse


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
