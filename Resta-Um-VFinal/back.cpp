
#include "dec_back.h"
#include <algorithm>
#include <fstream>       
#include <iomanip>      

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
    if (tabuleiro[iTest][jTest].state != PART)
        return false;

    int mov_i[4] = {cima, baixo, atual, atual};
    int mov_j[4] = {atual, atual, esquerda, direita};

    for (int d = 0; d < 4; d++)
    {
        int i_destino = iTest + mov_i[d];
        int j_destino = jTest + mov_j[d];

        int i_meio    = iTest + mov_i[d] / 2;
        int j_meio    = jTest + mov_j[d] / 2;

        if (i_destino < 0 || i_destino >= TAM ||  j_destino < 0 || j_destino >= TAM)
            continue;

        if (i_meio < 0 || i_meio >= TAM ||  j_meio < 0 || j_meio >= TAM)
            continue;

        if (tabuleiro[i_destino][j_destino].state == VAZIO && tabuleiro[i_meio][j_meio].state == PART)
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
                if (tabuleiro[i][j].state == PART)
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

void salvarRecorde(char letra, float tempo)
{
    std::ofstream arquivo("recordes.txt", std::ios::app); 
    if (!arquivo.is_open()) return;

    //manipula para somente duas casas depois do ponto ↓
    arquivo << letra << " " << std::fixed << std::setprecision(2) << tempo << "\n"; 
}

int carrega_recordes(Recorde recs[MAX_RECORDES])
{
    //abre e le percorrendo o arquivo
    std::ifstream arquivo("recordes.txt");
    if (!arquivo.is_open()) return 0;

    int conta = 0; //quantidade de records
    char nome; // vai receber a letra do player
    float tempo;

    while (conta < MAX_RECORDES && arquivo >> nome >> tempo)
    {
        recs[conta].nome = nome;
        recs[conta].tempo = tempo;
        conta++;
    }

    return conta;
}

void ordena_recordes(Recorde rcds[], int qtd){
    int minIdex;
    Recorde aux;
    for(int i = 0; i < qtd-1;i++){
        minIdex = i;
        for(int j = i; j<qtd;j++){
            if(rcds[j].tempo < rcds[minIdex].tempo){
                minIdex=j;
            }
        }
        aux = rcds[i];
        rcds[i] = rcds[minIdex];
        rcds[minIdex]= aux;
    }
}
void mostrarRecordesOrdenados(void)
{
    //logica de front para exibir os records
    Recorde recordTemp[MAX_RECORDES];
    int qtd = carrega_recordes(recordTemp);

    if (qtd == 0)
    {
        DrawText("Sem recordes", 780, 150, 20, YELLOW);
        return;
    }

    ordena_recordes(recordTemp, qtd);

    const int x = 770;
    const int y = 120;
    const int largura = 160;
    const int total_altura = 40;

    for(int i = 1; i <= qtd;i++)
        DrawRectangle(x, y, largura, total_altura + 23*i, corTabuF);

    DrawText("RECORDES", x + 10, y + 10, 22, GOLD);

    for (int i = 0; i < qtd; i++)
    {
        int linha_y = y + 40 + i * 22;
        if (i < qtd)
        {
            // Converte segundos em minutos:segundos
            int total = (int)(recordTemp[i].tempo);   
            int min = total / 60; 
            int seg = total % 60;
            char linha[16];
            sprintf(linha, "%c %02d:%02d", recordTemp[i].nome, min, seg);
            DrawText(linha, 785, linha_y, 20, WHITE);

        }
    }
}
