#include "projeto.h"

float startTime = 0.0f;
float timeElapsed;
int minutos;
int segundos;
char textoTimer[50];
int restaPart;

Part tabuleiro[TAM][TAM];

int i_atual = 0, j_atual = 0;
int aux_i, aux_j;
int clique_atual = CLIQUE_PRIMEIRO;

bool temaAtual = true;
Color corBotao = BROWN;
Color corFundo = BEIGE;
Color corPeca = DARKBROWN;
Color corTabu = BROWN;
Color corTabuF = DARKBROWN;
Color corTime = BLACK;
Color corERRO = WHITE;

int inicioX = screenWidth / 3.5;
int inicioY = screenHeight / 4;

Rectangle resetButton = {700.0f, 500.0f, 100.0f, 45.0f};
Rectangle startButton = {350, 350, 150.0f, 70.0f};
Rectangle themeButton = {30.0f, 500.0f, 100.0f, 45.0f};

Rectangle borda;
Rectangle fundoMaior = {191, 100, 460, 460};
Rectangle fundoMenor = {201, 110, 440,440};

void inicializaTabuleiro(Part tabuleiro[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            tabuleiro[i][j].pos = {(float)inicioX + i * (diametro + espaco),
                                   (float)inicioY + j * (diametro + espaco)};
            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = N_EXIST;
            else
                tabuleiro[i][j].state = PART;
        }
    }
    tabuleiro[3][3].state = VAZIO;
}

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
        corTabu = BLACK;
        corTabuF = BLACK;
        corTime = GOLD;
        corERRO = RED;
    }

    return temaAtual;
}

void desenhaTabuleiro(Part tabuleiro[TAM][TAM], int i_aux, int j_aux, int clique_atual)
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

            for (float o = 0; o < 3; o++)
                DrawCircleLinesV(tabuleiro[i][j].pos, raio + o, BLACK);

            if (jogadaValida(tabuleiro))
            {
                int movimento = calculeMovimento(i_atual, j_atual, i_aux, j_aux);
                if (movimento == MOVIMENTO_VALIDO && tabuleiro[i_aux][j_aux].state == VAZIO)
                {
                    for (float i = 0; i < 4; i++)
                        DrawCircleLinesV(tabuleiro[i_aux][j_aux].pos, raio + i, GOLD);
                }

                if (i == i_aux && j == j_aux)
                {
                    bool Mov = validaPart(tabuleiro, i, j);
                    Color Cor = Mov ? GREEN : RED;
                    if (clique_atual == CLIQUE_SEGUNDO)
                        Cor = RED;
                    for (float k = 0; k < 4; k++)
                        DrawCircleLinesV(tabuleiro[i][j].pos, raio + k, Cor);
                }
            }
        }
    }
}

int calculeMovimento(int Ic, int Jc, int i_fim, int j_fim)
{
    int i_alvo = (Ic + i_fim) / 2;
    int j_alvo = (Jc + j_fim) / 2;

    if (Ic == i_fim && Jc == j_fim)
        return MOVIMENTO_NENHUM;
    else if (Ic != i_fim && Jc != j_fim)
        return MOVIMENTO_INVALIDO;
    else if ((abs(i_fim - Ic) == 2 || abs(j_fim - Jc) == 2) && (tabuleiro[i_alvo][j_alvo].state == PART))
        return MOVIMENTO_VALIDO;

    return MOVIMENTO_INVALIDO;
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

bool localizePart(Part tabuleiro[TAM][TAM], int &ii, int &jj, int state)
{
    Vector2 mouse = GetMousePosition();
    double menor = raio;
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (tabuleiro[i][j].state == state || state == -1)
            {
                double a = tabuleiro[i][j].pos.x - mouse.x;
                double b = tabuleiro[i][j].pos.y - mouse.y;
                double c = sqrt(pow(a, 2) + pow(b, 2));
                if (c < menor)
                {
                    ii = i;
                    jj = j;
                    menor = c;
                }
            }
        }
    }
    return menor <= (double)raio;
}

bool validaPart(Part tabuleiro[TAM][TAM], int iTest, int jTest)
{
    int i_destino, j_destino, i_meio, j_meio;

    if (tabuleiro[iTest][jTest].state == N_EXIST)
        return false;

    if (tabuleiro[iTest][jTest].state == VAZIO)
        return false;

    for (int i = 0; i < 4; i++)
    {
        int delta_i = Movimentos[i][0];
        int delta_j = Movimentos[i][1];
        i_destino = iTest + delta_i;
        j_destino = jTest + delta_j;

        i_meio = iTest + delta_i / 2;
        j_meio = jTest + delta_j / 2;

        if (i_destino < 0 || i_destino >= TAM || j_destino < 0 || j_destino >= TAM)
            continue;
        if (i_meio < 0 || i_meio >= TAM || j_meio < 0 || j_meio >= TAM)
            continue;

        if ((tabuleiro[i_destino][j_destino].state == VAZIO) && (tabuleiro[i_meio][j_meio].state != VAZIO))
        {
            return true;
        }
    }
    return false;
}


void Jogada(void)
{
    clique_atual = (i_atual == 0 && j_atual == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (clique_atual == CLIQUE_PRIMEIRO)
        {
            if (localizePart(tabuleiro, i_atual, j_atual, PART))
            {
                aux_i = i_atual;
                aux_j = j_atual;
            }
        }
        else
        {
            int i_fim = 0, j_fim = 0;
            if (localizePart(tabuleiro, i_fim, j_fim, VAZIO))
            {
                int movimento = calculeMovimento(i_atual, j_atual, i_fim, j_fim);

                if (movimento == MOVIMENTO_INVALIDO)
                {
                    SetTargetFPS(2);
                    DrawText("MOVIMENTO INVALIDO", 250, 90, 30, corERRO);
                }
                else
                {
                    int i_alvo = (i_atual + i_fim) / 2;
                    int j_alvo = (j_atual + j_fim) / 2;

                    if (tabuleiro[i_alvo][j_alvo].state == PART)
                    {
                        tabuleiro[i_alvo][j_alvo].state = VAZIO;
                        tabuleiro[i_fim][j_fim].state = PART;
                        tabuleiro[i_atual][j_atual].state = VAZIO;
                    }
                }
                if (movimento != MOVIMENTO_NENHUM)
                {
                    i_atual = 0;
                    i_fim = 0;
                    j_atual = 0;
                    j_fim = 0;
                }
            }
        }
    }
}

bool jogadaValida(Part tabuleiro[TAM][TAM])
{
    int Nvalido = 0, Valido = 0;

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if ((tabuleiro)[i][j].state == N_EXIST)
                continue;

            if (validaPart(tabuleiro, i, j))
            {
                Valido++;
            }
            else
            {
                if (tabuleiro[i][j].state == 2)
                    Nvalido++;
            }
        }
    }
    restaPart = Nvalido;

    if (Valido > 0)
    {
        return RESTA_JOGADA;
    }
    else
    {
        return NAO_RESTA_JOGADA;
    }
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
    DrawText("RESET", 715, 515, 20, BLACK);
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
        DrawText(textoTimer, 640, 20, 25, corTime);
    }
    if (!jogadaValida(tabuleiro))
    {
        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 640, 20, 25, corTime);
    }
}
