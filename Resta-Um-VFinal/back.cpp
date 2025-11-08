
# include "dec_back.h"

void imprimeTabuleiro(Part tabuleiro[TAM][TAM])
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

void jogada(void)
{
    clique_atual = (i_atual == 0 && j_atual == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (clique_atual == CLIQUE_PRIMEIRO)
        {
            if (localizePart(tabuleiro, i_atual, j_atual, PART))
            {
                aux_ci = i_atual;
                aux_cj = j_atual;
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
                    DrawText("MOVIMENTO INVALIDO", screenWidth/3, 90, 30, corERRO);
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

bool jogadaValida(Part tabuleiro[TAM][TAM], int iTest, int jTest)
{
    int i_destino, j_destino, i_meio, j_meio;

    if (tabuleiro[iTest][jTest].state == VAZIO)
        return false;

        int mov_i[4] = {cima, baixo, atual, atual};
        int mov_j[4] = {atual, atual, esquerda, direita};

    for (int i = 0; i < 4; i++)
    {
        // int delta_i = mov_i[i];
        // int delta_j = mov_j[i];

        i_destino = abs(iTest + mov_i[i]);
        j_destino = abs(jTest + mov_j[i]);

        i_meio = abs(iTest + mov_i[i] / 2);
        j_meio = abs(jTest + mov_j[i] / 2);

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

bool jogadaValida(Part tabuleiro[TAM][TAM])
{
    int Nvalido = 0, Valido = 0;

    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if ((tabuleiro)[i][j].state == N_EXIST)
                continue;

            if (jogadaValida(tabuleiro, i, j))
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

    return (Valido > 0) ? RESTA_JOGADA : NAO_RESTA_JOGADA;
    
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

    return (menor <= (double)raio) ? true: false;
}

int calculeMovimento(int Ic, int Jc, int i_fim, int j_fim)
{
    int i_alvo = (Ic + i_fim) / 2;
    int j_alvo = (Jc + j_fim) / 2;

    if (Ic == i_fim && Jc == j_fim) return MOVIMENTO_NENHUM;

    else if (Ic != i_fim && Jc != j_fim) return MOVIMENTO_INVALIDO;
    
    else if ((abs(i_fim - Ic) == 2 || abs(j_fim - Jc) == 2) && (tabuleiro[i_alvo][j_alvo].state == PART))
        return MOVIMENTO_VALIDO;

    return MOVIMENTO_INVALIDO;
}