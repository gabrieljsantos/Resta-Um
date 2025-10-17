#include "raylib.h"
#include "projeto.h"

/// Tabuleiro
part tabuleiro[TAM][TAM];

enum Clique {
    CLIQUE_PRIMEIRO,
    CLIQUE_SEGUNDO
};

/// ------------------------------------------------------------
/// Função principal: inicializa janela, atualiza e desenha o jogo
/// ------------------------------------------------------------
int main(void)
{
    Vector2 loc = { 100, 100 };

    //--------------------------------------------------------------------------------------
    // Inicialização da janela e configurações básicas
    const int screenWidth = 900;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "TELA 60FPS");
    SetTargetFPS(100); // Define o FPS do jogo
    //--------------------------------------------------------------------------------------

    // Inicializa o tabuleiro
    inicializa_tabuleiro(tabuleiro);

    float tempoInicio = GetTime();
    float tempoFinal = 0;
    bool jogoTerminado = false;
    tempoFinal = GetTime() - tempoInicio;
    jogoTerminado = true;

    // Solicita a letra do jogador
    char nome[2];
    printf("Digite sua inicial: ");
    scanf("%1s", nome);

    // Salva o recorde
    salvarRecorde(nome, tempoFinal);







    int i_inicial = 0, j_inicial = 0; // Coordenadas do clique anterior
    Color mouse_circle = BLUE;

    unsigned int error_fps_counter = 0;
    bool red = false;
    int clique_atual = CLIQUE_PRIMEIRO;

    //--------------------------------------------------------------------------------------
    // Loop principal do jogo
    while (!WindowShouldClose()) // Fecha a janela se clicar em ESC ou X
    {
        //----------------------------------------------------------------------------------
        // Atualizações
        //----------------------------------------------------------------------------------

        mouse_circle = BLUE;

        // Controle da cor do círculo do mouse em caso de erro
        if (error_fps_counter > 0) {
            if (error_fps_counter % 5 == 0) {
                red = !red; // Pisca em vermelho
            }
            if (red) mouse_circle = RED;
            error_fps_counter--;
        }

        //----------------------------------------------------------------------------------
        // Desenho na tela
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("----- RESTA UM -----", 350, 50, 20, PURPLE);

        int i_atual = 0, j_atual = 0;
        localize_peca(tabuleiro, &i_atual, &j_atual);

        desenha_tabuleiro(tabuleiro, i_atual, j_atual);


         // Botão de reset
        Rectangle botaoReset = { 750, 520, 120, 40 }; // x, y, largura, altura
        DrawRectangleRec(botaoReset, DARKBLUE);
        DrawText("RESET", 780, 530, 20, RAYWHITE);



        // Verifica clique no botão
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, botaoReset)) {
                reset_tabuleiro(tabuleiro); // Chama a função de reset
            }
        }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        Vector2 pos = GetMousePosition(); // Pega posição (x,y) do mouse

        clique_atual = (i_inicial == 0 && j_inicial == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;

        //----------------------------------------------------------------------------------
        // Captura de cliques do mouse
        //----------------------------------------------------------------------------------
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();

            if (clique_atual == CLIQUE_PRIMEIRO) {
                // Primeiro clique: selecionar peça
                if (localize_peca(tabuleiro, &i_inicial, &j_inicial, 2)) {
                    DrawCircleV(mouse, 40, RED);
                    std::cout << "Primeiro clique na posição X: " << tabuleiro[i_inicial][j_inicial].pos.x
                              << ", Y: " << tabuleiro[i_inicial][j_inicial].pos.y << std::endl;
                }
            } else {
                // Segundo clique: selecionar destino
                int i_final = 0, j_final = 0;
                if (localize_peca(tabuleiro, &i_final, &j_final, 1)) {
                    DrawCircleV(mouse, 40, RED);
                    std::cout << "Segundo clique na posição X: " << tabuleiro[i_final][j_final].pos.x
                              << ", Y: " << tabuleiro[i_final][j_final].pos.y << std::endl;

                    int movimento = calcule_movimento(i_inicial, j_inicial, i_final, j_final);
                    if (movimento == MOVIMENTO_INVALIDO) {
                        std::cout << "Movimento inválido: I: " << i_inicial << " J: " << j_inicial
                                  << " para I2: " << i_final << " J2: " << j_final << std::endl;
                        error_fps_counter = 60; // = 1 segundo
                    } else {
                        int i_alvo = (i_inicial + i_final) / 2; // Linha intermediária
                        int j_alvo = (j_inicial + j_final) / 2; // Coluna intermediária

                        if (tabuleiro[i_alvo][j_alvo].state == 2) { // Há peça no meio
                            std::cout << "Deletando em i = " << i_alvo << "; j = " << j_alvo << std::endl;

                            tabuleiro[i_alvo][j_alvo].state = 1;
                            tabuleiro[i_final][j_final].state = 2;
                            tabuleiro[i_inicial][j_inicial].state = 1;
                        } else {
                            error_fps_counter = 60; // = 1 segundo
                        }
                    }

                    // Reseta e aguarda próximo lance
                    if (movimento != MOVIMENTO_NENHUM) {
                        i_inicial = 0;
                        j_inicial = 0;
                    }
                }
            }
        }

        // Desenha bolinha na posição do mouse
        DrawCircleV(pos, 20, mouse_circle);
        mostrarRecordes();

        EndDrawing();
    }
    //--------------------------------------------------------------------------------------

    // Finalização
    CloseWindow(); // Fecha a janela e o contexto OpenGL
    //--------------------------------------------------------------------------------------

    return 0;
}
