#include "dec_back.h"
#include "dec_front.h"

float startTime = 0.0f;
float timeElapsed;
int minutos;
int segundos;
char textoTimer[50];
int restaPart;

Part tabuleiro[TAM][TAM]; 

int i_atual = 0, j_atual = 0;
int aux_ci, aux_cj;
int clique_atual = CLIQUE_PRIMEIRO;

bool temaAtual = true;
Color corBotao = BROWN;
Color corFundo = BEIGE;
Color corPeca = DARKBROWN;
Color corTabu = BROWN;
Color corTabuF = DARKBROWN;
Color corTime = BLACK;
Color corERRO = WHITE;


Rectangle resetButton = {820.0f, 500.0f, 100.0f, 45.0f};
Rectangle startButton = {screenWidth/2 - 75, screenHeight /2 +45, 150.0f, 70.0f};
Rectangle themeButton = {30.0f, 500.0f, 100.0f, 45.0f};

Rectangle borda;
Rectangle fundoMaior = {inicioX-50, inicioY-50, 460, 460};
Rectangle fundoMenor = {inicioX-40, inicioY-40, 440,440};


bool trocarTema(void)
{
    temaAtual = !temaAtual;

    if (temaAtual)
    {
        corFundo = BEIGE;
        corPeca = DARKBROWN;
        corBotao = BROWN;
        corTabu = BROWN;
        corTabuF = DARKBROWN;
        corTime = BLACK;
        corERRO = WHITE;
    }
    else
    {
        corFundo = BLACK;
        corPeca = PURPLE;
        corBotao = DARKPURPLE;
        corTabu = DARKPURPLE;
        corTabuF = PURPLE;
        corTime = GOLD;
        corERRO = RED;
    }

    return temaAtual;
}

void imprimeTabuleiro(Part tabuleiro[TAM][TAM], int i_aux, int j_aux, int clique_atual)
{
    DrawRectangleRec(fundoMaior, corTabuF);
    DrawRectangleRec(fundoMenor, corTabu);

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (tabuleiro[i][j].state == N_EXIST)
                continue;

            Color cor = (tabuleiro[i][j].state == VAZIO) ? LIGHTGRAY : corPeca;
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);

            for (float o = 0.2; o < 3; o++)
                DrawCircleLinesV(tabuleiro[i][j].pos, raio + o, BLACK);

            if (jogadaValida(tabuleiro))
            {
                if(clique_atual==CLIQUE_SEGUNDO)
                    for(float c = 0.2; c<4;c++){
                        DrawCircleLinesV(tabuleiro[aux_ci][aux_cj].pos, raio + c, GOLD);
                    }
                

                int movimento = calculeMovimento(i_atual, j_atual, i_aux, j_aux);
                if (movimento == MOVIMENTO_VALIDO && tabuleiro[i_aux][j_aux].state == VAZIO)
                {
                    for (float i = 0.2; i < 4; i++)
                        DrawCircleLinesV(tabuleiro[i_aux][j_aux].pos, raio + i, GREEN);
                }

                if (i == i_aux && j == j_aux)
                {
                    bool Mov = jogadaValida(tabuleiro, i, j);
                    Color Cor = Mov ? GREEN : RED;
                    if (clique_atual == CLIQUE_SEGUNDO)
                        Cor = RED;
                    for (float k = 0.5; k < 4; k++)
                        DrawCircleLinesV(tabuleiro[i][j].pos, raio + k, Cor);
                }
            }
        }
    }
}



bool locateButton(Rectangle button)
{
    Vector2 mouse = GetMousePosition();
    if ((mouse.x >= button.x && mouse.x <= button.x + button.width) &&
        (mouse.y >= button.y && mouse.y <= button.y + button.height))
    {
        return true;
    }
    return false;
}

Rectangle expandRectangle(Rectangle button, int border_size)
{
    Rectangle expanded;
    expanded.x = button.x - border_size;
    expanded.y = button.y - border_size;
    expanded.width = button.width + border_size * 2;
    expanded.height = button.height + border_size * 2;
    return expanded;
}

void Emblema(void)
{
    DrawText("Resta Um", inicioX - 60, inicioY, 100, corPeca);
    if (locateButton(startButton))
    {
        borda = expandRectangle(startButton, 4);
        DrawRectangleRec(borda, GREEN);
    }
    DrawRectangleRec(startButton, corBotao);
    DrawText("START", screenWidth / 2 - 43, screenHeight / 2 + 70, 25, BLACK);
}

void Titulo(void)
{
    DrawText("----- RESTA UM -----", 252, 50, 30, corPeca);

    if (locateButton(resetButton))
    {
        borda = expandRectangle(resetButton, 4);
        DrawRectangleRec(borda, GREEN);
    }

    if (locateButton(themeButton))
    {
        borda = expandRectangle(themeButton, 4);
        DrawRectangleRec(borda, GREEN);
    }

    DisplayTimer();

    if (!jogadaValida(tabuleiro))
    {
        if (restaPart == 1)
        {
            DrawText("Vitória", 100, 50, 30, BLUE);
        }
        else
        {
            DrawText("FIM DE JOGO", screenWidth / 2 - 120, 2, 40, RED);
            DrawText(TextFormat("Restaram: %d", restaPart), 25, 70, 30, corPeca);
        }
    }

    DrawRectangleRec(resetButton, corBotao);
    DrawRectangleRec(themeButton, corBotao);
    DrawText("RESET", 835, 515, 20, BLACK);
    DrawText("TEMA", 45, 515, 20, BLACK);
}

void DisplayTimer(void)
{
    if (jogadaValida(tabuleiro))
    {
        timeElapsed = GetTime() - startTime;
        minutos = (int)timeElapsed / 60;
        segundos = (int)timeElapsed % 60;

        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 675, 20, 25, corTime);
    }
    if (!jogadaValida(tabuleiro))
    {
        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 675, 20, 25, corTime);
    }
}
