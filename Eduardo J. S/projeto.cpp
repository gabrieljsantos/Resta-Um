#include "raylib.h"
#include "projeto.h"

//----------------------
// VARIÁVEIS GLOBAIS
//----------------------
float startTime = 0.0f;  // TIMER SIMPLES
int i_inicial = 0, j_inicial = 0;
int pode = 0;
Part tabuleiro[TAM][TAM];
int Ic = 0, Jc = 0;
int clique_atual = CLIQUE_PRIMEIRO;

bool temaAtual = true;  // Começa com Tema 1
Color corFundo = BLACK;   // Tema 1: Preto
Color corPeca = PURPLE;   // Tema 1: Roxo

int inicioX = screenWidth/3.5, inicioY = screenHeight/4;
Rectangle restart = {700.0f, 500.0f, 100.0f, 45.0f};
Rectangle start_P = {350, 350, 150.0f, 70.0f};
Rectangle Muda = {30.0f, 500.0f, 100.0f, 45.0f};


//----------------------------------------------------------------------------
// PROCEDIMENTO inicializar_tabuleiro
//----------------------------------------------------------------------------
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].pos = {(float)inicioX + i * (diametro + espaco),
                                   (float)inicioY + j * (diametro + espaco)};
            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = N_EXIST;
            else
                tabuleiro[i][j].state = EXIST;
        }
    }
    tabuleiro[3][3].state = VAZIO;
}

bool trocarTema(void) {
    temaAtual = !temaAtual;  // ALTERNAR TRUE/FALSE
    
    if (temaAtual) {
        // tama 1: escuro 
        corFundo = BLACK;
        corPeca = PURPLE;
        std::cout << "Tema 1: Preto + Roxo" << std::endl;
    } else {
        // tema 2: branco
        corFundo = WHITE;
        corPeca = BROWN;
        std::cout << "Tema 2: Branco + Marrom" << std::endl;
    }
    
    return temaAtual;  // Retorna o novo estado
}


//----------------------------------------------------------------------------
// PROCEDIMENTO desenha_tabuleiro
//----------------------------------------------------------------------------
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, bool red){
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == N_EXIST) continue;
            
            Color cor = (tabuleiro[i][j].state == VAZIO) ? LIGHTGRAY : corPeca;
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);
            
            for(int o = 0; o < 3; o++)
                DrawCircleLinesV(tabuleiro[i][j].pos, raio + o, BLACK);
                
            if (i == i_atual && j == j_atual) {
                int aux = 0;
                bool Mov = valida_Part(tabuleiro, i, j, aux);
                Color Cor = Mov ? GREEN : RED;
                for (int k = 0; k < 4; k++)
                    DrawCircleLinesV(tabuleiro[i][j].pos, (float)raio + k, Cor);
            }
        }
    }
}

//----------------------------------------------------------------------------
// Função calcule_movimento
//----------------------------------------------------------------------------
int calcule_movimento(int Ic, int Jc, int Ifim, int jfim) {
    if (Ic == Ifim && Jc == jfim) return MOVIMENTO_NENHUM;
    else if (Ic != Ifim && Jc != jfim) return MOVIMENTO_INVALIDO;
    else if (abs(Ifim - Ic) == 2 || abs(jfim - Jc) == 2) return MOVIMENTO_VALIDO;
    return MOVIMENTO_INVALIDO;
}

//----------------------------------------------------------------------------
// Função locale_Button
//----------------------------------------------------------------------------
bool locale_Button(){
    Vector2 mouse = GetMousePosition(); 
    
    if ((mouse.x >= 350 && mouse.x <= 350 + 150) &&//|BOTAO START
        (mouse.y >= 350 && mouse.y <= 350 + 70))    //|
        return true;//aarea de clique botão start

    return false;
}

bool locale_Reset(){
    Vector2 mouse = GetMousePosition(); 
    
    if((mouse.x >= 700 && mouse.x <= 700 + 100)&&
        (mouse.y >= 500 && mouse.y <= 500 + 45)) return true; // area de clique do botão reset

    return false;
}

bool locale_Muda(){
    Vector2 mouse = GetMousePosition(); 
    
    if((mouse.x >= 30 && mouse.x <= 30 + 100)&&
        (mouse.y >= 500 && mouse.y <= 500 + 45)) return true; // area de clique do botão reset

    return false;
}


//----------------------------------------------------------------------------
// Função localize_Part
//----------------------------------------------------------------------------
bool localize_Part(Part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state) {
    Vector2 Mouse = GetMousePosition();
    double menor = raio;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == state || state == -1) {
                double a = tabuleiro[i][j].pos.x - Mouse.x;
                double b = tabuleiro[i][j].pos.y - Mouse.y;
                double c = sqrt(pow(a, 2) + pow(b, 2));
                if (c < menor) {
                    *ii = i;
                    *jj = j; 
                    menor = c;
                }
            }
        }
    }
    return menor <= (double)raio;
}

//----------------------------------------------------------------------------
// Função valida_Part
//----------------------------------------------------------------------------
bool valida_Part(Part(&tabuleiro)[TAM][TAM], int Io, int Jo, int (&S)){
    S = 0;
    if(tabuleiro[Io][Jo].state == N_EXIST || tabuleiro[Io][Jo].state != EXIST)
        return false;

    for (int i = 0; i < 4; i++) {
        int Di = Movimentos[i][0];
        int Dj = Movimentos[i][1];
        int Id = Io + Di;
        int Jd = Jo + Dj;
        int Im = Io + Di/2;
        int Jm = Jo + Dj/2;
        
        if (Id < 0 || Id >= TAM || Jd < 0 || Jd >= TAM) continue;
        if (Im < 0 || Im >= TAM || Jm < 0 || Jm >= TAM) continue;

        if (tabuleiro[Id][Jd].state == VAZIO && tabuleiro[Im][Jm].state != VAZIO){
            S = 1;
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Jogada
//----------------------------------------------------------------------------
void Jogada(void){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (clique_atual == CLIQUE_PRIMEIRO) {
            if (localize_Part(tabuleiro, &Ic, &Jc, EXIST)) {
                std::cout << "Primeiro clique na posição X: " << tabuleiro[Ic][Jc].pos.x << ", Y: " << tabuleiro[Ic][Jc].pos.y << std::endl;
                clique_atual = CLIQUE_SEGUNDO;
            }
        } else {
            int Ifim = 0, jfim = 0;
            if (localize_Part(tabuleiro, &Ifim, &jfim, VAZIO)) {
                std::cout << "Segundo clique na posição X: " << tabuleiro[Ifim][jfim].pos.x << ", Y: " << tabuleiro[Ifim][jfim].pos.y << std::endl;                
                int movimento = calcule_movimento(Ic, Jc, Ifim, jfim);

                if (movimento == MOVIMENTO_VALIDO) {
                    int i_alvo = (Ic + Ifim) / 2;
                    int j_alvo = (Jc + jfim) / 2;

                    if (tabuleiro[i_alvo][j_alvo].state == EXIST) {
                        std::cout << "Deletando em i = " << i_alvo << "; j = " << j_alvo << std::endl;
                        tabuleiro[i_alvo][j_alvo].state = VAZIO;
                        tabuleiro[Ifim][jfim].state = EXIST;
                        tabuleiro[Ic][Jc].state = VAZIO;
                    }
                }
                // Reset para próximo movimento
                Ic = 0; Jc = 0;
                clique_atual = CLIQUE_PRIMEIRO;
            }
        }
    }
}

//----------------------------------------------------------------------------
// Função jogada_Valida
//----------------------------------------------------------------------------
bool jogada_Valida(Part(&tabuleiro)[TAM][TAM], int (&Resta)) {
    int Nvalido = 0, Valido = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == N_EXIST) continue;
            int S = 0;
            valida_Part(tabuleiro, i, j, S);
                
            if (S == 1) {
                Valido++;
            } else if(tabuleiro[i][j].state == EXIST) {
                Nvalido++;
            }
        }
    }
    Resta = Nvalido;

    return Valido > 0 ? RESTA_JOGADA : NAO_RESTA_JOGADA;
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Emblema
//----------------------------------------------------------------------------
void Emblema(void){
    DrawText("Resta Um", inicioX-80, inicioY, 100, corPeca);
    DrawRectangleRec(start_P, corPeca);
    DrawText("START", screenWidth/2-43, screenHeight/2+70, 25, BLACK);
    
    if(locale_Button()){
        for(int i = 0; i < 4; i++){ 
            DrawRectangleLines(350-i, 350-i, 152+i, 72+i, GREEN);
        }
    }
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Titulo
//----------------------------------------------------------------------------
void Titulo(void){
    int R;
    DrawText("----- RESTA UM -----", 252, 50, 30, corPeca);
    DrawRectangle(restart.x, restart.y, restart.width, restart.height, BLUE);
    DrawRectangle(Muda.x, Muda.y, Muda.width, Muda.height, BLUE);
    DrawText("RESET", 715, 515, 20, BLACK);
    DrawText("Tema", 45, 515, 20, BLACK);

    // TIMER SIMPLES - SEM PARÂMETRO
    DisplayTimer();

    if(!jogada_Valida(tabuleiro, R)){
        if (R == 1) {
            DrawText("Vitória", 100, 50, 30, BLUE);
        } else {
            DrawText("GAME OVER", 900/2 -100, 600/2, 30, RED);
            DrawText(TextFormat("Restaram: %d", R), 100, 150, 30, corPeca);
        }
    }    
}

//----------------------------------------------------------------------------
// Função DisplayTimer - SIMPLES
//----------------------------------------------------------------------------
void DisplayTimer(void) {
    float timeElapsed = GetTime() - startTime;
    int minutos = (int)timeElapsed / 60;
    int segundos = (int)timeElapsed % 60;
    char textoTimer[50];
    sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
    DrawText(textoTimer, 650, 20, 20, YELLOW);
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Atualiza_Imformação
//----------------------------------------------------------------------------
void Atualiza_Imformação(){
    clique_atual = (Ic == 0 && Jc == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;
    int i_atual = 0, j_atual = 0;
    localize_Part(tabuleiro, &i_atual, &j_atual);
    if (clique_atual == CLIQUE_PRIMEIRO) {
        desenha_tabuleiro(tabuleiro, i_atual, j_atual, tabuleiro[i_atual][j_atual].state != EXIST);
    } else {
        int movimento = calcule_movimento(Ic, Jc, i_atual, j_atual);
        desenha_tabuleiro(tabuleiro, i_atual, j_atual, movimento != MOVIMENTO_VALIDO);
    }
}
