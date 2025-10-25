#include "raylib.h"
#include "projeto.h"

//----------------------
// VARIÁVEIS GLOBAIS
//----------------------
float startTime = 0.0f;  // TIMER SIMPLES
float timeElapsed;
int minutos;
int segundos;
char textoTimer[50];




Part tabuleiro[TAM][TAM];
int Ic = 0, Jc = 0;
int clique_atual = CLIQUE_PRIMEIRO;

bool temaAtual = true;// Começa com Tema 1
Color corBotao = BROWN;    // Botao 1: Marrom Claro
Color corFundo = BEIGE;    // Fundo 1: Beige
Color corPeca = DARKBROWN; // Peça  1: Marrom Escuro
Color corTabu = BROWN;     // tabu  1: Marrom claro
Color corTabuF = DARKBROWN;   // tabu  1: Marrom claro
Color corTime = BLACK;     // Time  1: Preto
   // Tema 1: Roxo

int inicioX = screenWidth/3.5, inicioY = screenHeight/4;
Rectangle restart = {700, 500, 100, 45}; // posiçoes dos botaos
Rectangle start_Button = {350, 350, 150, 70}; 
Rectangle Muda = {30, 500, 100, 45};

const int button_border_size = 5;

//----------------------------------------------------------------------------
//            ----> IMPLEMENTAÇÃO DE FUNÇÕES E PROCEDIMENTOS <----
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// PROCEDIMENTO inicializar_tabuleiro
//----------------------------------------------------------------------------
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].pos = {(float)inicioX + i * (diametro + espaco),
                                   (float)inicioY + j * (diametro + espaco)};
            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = N_EXIST; // Parte transparente, sem nada
            else
                tabuleiro[i][j].state = EXIST;  // peças do jogo
        }
    }
    tabuleiro[3][3].state = VAZIO; // posição do meio vazia
}
//----------------------------------------------------------------------------
// FUNÇÃO TROCA TEMA -- > PARA MUDAR OS TEMAS 
//---------------------------------------------------------------------------
bool trocarTema(void) {
    temaAtual = !temaAtual;  // ALTERNAR TRUE/FALSE

    
      if(temaAtual){
        // tema 1: claro
        corFundo = BEIGE;
        corPeca = DARKBROWN;
        corBotao = BROWN;
        corTabu = BROWN;
        corTabuF = DARKBROWN;
        corTime = BLACK;
        }
        else{
        // tama 2: escuro
        corFundo = BLACK;
        corPeca = PURPLE;
        corBotao = DARKPURPLE;
        corTabu = BLACK;
        corTabuF = BLACK;
        corTime = GOLD;
        }

    return temaAtual;  // Retorna o novo tema
}

//----------------------------------------------------------------------------
// PROCEDIMENTO desenha_tabuleiro --->  PARA DESENHAR O TABULEIRO
//----------------------------------------------------------------------------
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, int clique_atual){
    DrawRectangle(inicioX-50, inicioY-50, 460, 460, corTabuF);  //| QUADRADO FUNDO
    DrawRectangle(inicioX-40, inicioY-40, 440, 440, corTabu);   //| QUADRADO TABULEIRO
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tabuleiro[i][j].state == N_EXIST) continue;

            Color cor = (tabuleiro[i][j].state == VAZIO) ? LIGHTGRAY : corPeca; 
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);

            for(int o = 0; o < 3; o++)
                DrawCircleLinesV(tabuleiro[i][j].pos, raio + o, BLACK);//contorno

            int r;
            if(jogada_Valida(tabuleiro,r)){

                int movimento = calcule_movimento(Ic, Jc, i_atual, j_atual); // Mostra onde a peça pode se mover
                if(movimento == MOVIMENTO_VALIDO && tabuleiro[i_atual][j_atual].state == VAZIO) {
                    for(int i = 0;i<4;i++)
                        DrawCircleLinesV(tabuleiro[i_atual][j_atual].pos,raio+i,GREEN);
                }  

                if (i == i_atual && j == j_atual) {
                    int aux = 0;
                    bool Mov = valida_Part(tabuleiro, i, j, aux);

                    Color Cor = Mov ? GREEN : RED;

                    // Se o clique for o segundo, ele foi validado por calcule_movimento, então pinta de vermelho
                    if (clique_atual == CLIQUE_SEGUNDO)
                    Cor = RED;
                    for (int k = 0; k < 4; k++)
                        DrawCircleLinesV(tabuleiro[i][j].pos, (float)raio + k, Cor);              
                }            
            }
        }
    }
}

//----------------------------------------------------------------------------
// Função calcule_movimento
//----------------------------------------------------------------------------
int calcule_movimento(int Ic, int Jc, int Ifim, int jfim) {
    if (Ic == Ifim && Jc == jfim) return MOVIMENTO_NENHUM; // se clicar na mesma peça

    else if (Ic != Ifim && Jc != jfim) return MOVIMENTO_INVALIDO; //se nao clicar em uma peça valdida, para o movimento

    else if (abs(Ifim - Ic) == 2 || abs(jfim - Jc) == 2) return MOVIMENTO_VALIDO; //se seguir a regra do jogo

    return MOVIMENTO_INVALIDO; // se tentar jogar em diagonal
}

//--------------------------------------------------------------------------
// Função locale_Button ---> PARA LOCALIZAR OS BOTOES 
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
}//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Função localize_Part ---> Para Localizar Peças Existentes
// DENTRO DO RAIO DA PEÇA
//----------------------------------------------------------------------------

bool localize_Part(Part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state) {
    int e;
    Vector2 Mouse = GetMousePosition();// POSIÇÃO DO MOUSE
    double menor = raio;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == state || state == -1) {
                double a = tabuleiro[i][j].pos.x -  Mouse.x; // a É DELTA X
                double b = tabuleiro[i][j].pos.y -  Mouse.y; // b É DELTA Y
                double c = sqrt(pow(a, 2) + pow(b, 2)); //RAIZ QUADRADA DE DELTA a + DELTA b 
                if (c < menor) {
                    *ii = i;
                    *jj = j; 
                    menor = c;
                }
            }
        }
    }
    return menor <= (double)raio; // retorne TRUE se MENOR for <= RAIO, caso contarrio FALSE
}

//----------------------------------------------------------------------------
// FUNÇÃO SUPER IMPORTANTE
// Função Valida_Part ---> Para Validar possiveis jogadas
//----------------------------------------------------------------------------

bool valida_Part(Part(&tabuleiro)[TAM][TAM], int Io, int Jo, int (&S)){

    int Id, Jd, Im,Jm; /*-- Io,Jo origem, Id,Jd Destinho, Im,Jm Meio --*/

       S = 0; // nao tem movimento valido
       // S retorna o valor por referencia
        if(tabuleiro[Io][Jo].state == N_EXIST) //parte que esta fora (em branco)
            return false;
        if(tabuleiro[Io][Jo].state != EXIST) // nao é uma peça valida
            return false;

        //---------------------------------------------------------------------

        //agora tenta os movimentos valido para achar a peça sem estar travada
        //---------------------------------------------------------------------
        for (int i = 0; i < 4; i++) {
            int Di = Movimentos[i][0]; //|DELTA ESTA RECEBENDO MOVIMENTOS DO TIPO (I-2, I+2, J-2, J+2)
            int Dj = Movimentos[i][1]; //| QUE SAO MOVIMENTOS(ESQUERDA, DIREITA, CIMA, BAIXO)
            Id = Io + Di; // i destinho = pos. atual + Delta i
            Jd = Jo + Dj; // j destinho = pos. atual + Delta j

            Im = Io + Di/2; // i meio = i origem + Delta /2 
            Jm = Jo + Dj/2; // j meio = i origem + Delta /2 
            
            //--------------------------------------------------------------
            //Testa para ver se as possiveis jogadas estao no limite do tabu
            if (Id < 0 || Id >= TAM || Jd < 0 || Jd >= TAM) continue;
            if (Im < 0 || Im >= TAM || Jm < 0 || Jm >= TAM) continue;
            //verifica se a jogada da peça pode sair do tabuleiro
            //---------------------------------------------------------------

            if ((tabuleiro[Id][Jd].state == VAZIO )&& (tabuleiro[Im][Jm].state != VAZIO)){
                S = 1; // um movimento valido
                return true; //Existe alguma jogada valida
            }
        }
        // Se nao tem movimento
        S = 0; 

    return false;
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Jogada ---> Para Fazer o Movimento no Jogo
//CAPITURA OS CLIQUES E VERIFICA SE PODE JOGAR
//----------------------------------------------------------------------------
int TX,TY;
void Jogada(void){
     clique_atual = (Ic == 0 && Jc == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;

    if(clique_atual == CLIQUE_SEGUNDO)
        for(int i = 0; i < 4;i++)
            DrawCircleLinesV(tabuleiro[TX][TY].pos,raio+i,BLUE); 


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    
        if (clique_atual == CLIQUE_PRIMEIRO) {
            if (localize_Part(tabuleiro, &Ic, &Jc, EXIST)) {
                TX = Ic;
                TY = Jc;
            }
         } else {
            int Ifim = 0, jfim = 0;
            if (localize_Part(tabuleiro, &Ifim, &jfim, VAZIO)) {
                
            
               int movimento = calcule_movimento(Ic, Jc, Ifim, jfim);

                if (movimento == MOVIMENTO_INVALIDO) {
                    DrawText("MOVIMENTO INVALIDO",250,90,30,RED);
                } else {
                    int i_alvo = (Ic + Ifim) / 2; //i meio = i origem + Delta i /2
                    int j_alvo = (Jc + jfim) / 2;//i meio = i origem + Delta j /2

                    if (tabuleiro[i_alvo][j_alvo].state == 2) {
                        //-----------------------------------//
                        tabuleiro[i_alvo][j_alvo].state = VAZIO; //
                        tabuleiro[Ifim][jfim].state = EXIST;     //  atualiza o estado das peças movidas
                        tabuleiro[Ic][Jc].state = VAZIO;         //
                        //-----------------------------------//
                    } 
                }
                if (movimento != MOVIMENTO_NENHUM) {Ic = 0; Ifim = 0; Jc= 0; jfim = 0;
                }
            
            }
        }
    }
}

//----------------------------------------------------------------------------
// Função Jogada Valida---> Para verificar quantidade de peças sem movimento valido
//----------------------------------------------------------------------------

bool jogada_Valida(Part(&tabuleiro)[TAM][TAM], int (&Resta)) {
    int Nvalido = 0, Valido = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            int S = 0;
            if ((tabuleiro)[i][j].state == 0) continue;
            //NAO PODE TESTAR PARTE EM BRAMCO DA ERRO!!!!
            valida_Part(tabuleiro, i, j, S);
                
            if (S == 1) {
                 Valido++;
            }
            else{
            // PEÇAS SEM MOVIMENTO VALIDO
                if(tabuleiro[i][j].state==2)
                    Nvalido++;
            }           
        }
    }
    Resta = Nvalido;

    if (Valido > 0) {
        //std::cout << "RESTA JOGO\n";
        return RESTA_JOGADA; // ainda há jogadas possíveis
    } else {
        //std::cout << "NAO RESTA\n";
        return NAO_RESTA_JOGADA; // jogo terminou
    }
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Emblema ---> Para Mostrat botoe e Emblema
//----------------------------------------------------------------------------
void Emblema(void){

    Vector2 mouse = GetMousePosition();
    if(checks_if_the_mouse_is_in_an_area(mouse,start_Button)){
        DrawRectangleRec(
            ExpandRectangle(start_Button,button_border_size),
                BLACK);
                }
    
    DrawText("Resta Um", inicioX-60, inicioY, 100, corPeca);
    DrawRectangleRec(start_Button, corBotao);
    DrawText("START", screenWidth/2-43, screenHeight/2+70, 25, BLACK);
}
//----------------------------------------------------------------------------
// PROCEDIMENTO Titulo --> Para Mostrar GAMEOVER/VITORIA, BOTOES, e TITULO
//----------------------------------------------------------------------------
void Titulo(void){
    int R;
    DrawText("----- RESTA UM -----", 252, 50, 30, corPeca);
    DrawRectangle(restart.x, restart.y, restart.width, restart.height, corBotao);
    DrawRectangle(Muda.x, Muda.y, Muda.width, Muda.height, corBotao);
    DrawText("RESET", 715, 515, 20, BLACK);
    DrawText("Tema", 45, 515, 20, BLACK);

    if(locale_Reset()){
        for(int i = 0; i < 4; i++) 
            //Cor em volta do botao RESET
            DrawRectangleLines(700-i, 500-i, 102+i, 45+i, GREEN);
    }

if(locale_Muda()){
        for(int i = 0; i < 4; i++) 
            //Cor em volta do botao TEMA
            DrawRectangleLines(30-i, 500-i, 102+i, 45+i, GREEN);
    }

    // TIMER SIMPLES - SEM PARÂMETRO
    DisplayTimer();

    if(!jogada_Valida(tabuleiro, R)){
        if (R == 1) {
            DrawText("Vitória", 100, 50, 30, BLUE);
        } else {
            DrawText("GAME OVER", screenWidth/2 -120, screenHeight/2, 40, RED);
            DrawText(TextFormat("Restaram: %d", R), 25, 70, 30, corPeca);
        }
    }
}
    
//----------------------------------------------------------------------------
// Função DisplayTimer ---> PARA mostar Tempo SIMPLES
//----------------------------------------------------------------------------
void DisplayTimer(void) {
    int R;
    if(jogada_Valida(tabuleiro,R)){
         timeElapsed = GetTime() - startTime;
         minutos = (int)timeElapsed / 60;
         segundos = (int)timeElapsed % 60;

        //Mostra o tempo em atualização
        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 640, 20, 25, corTime);
    }
    if (!jogada_Valida(tabuleiro,R)){
    
        //Mostra o tempo parado
        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 640, 20, 25, corTime);
    }
}
    
bool checks_if_the_mouse_is_in_an_area(Vector2 cp, Rectangle sri) {
    // cp = comparison_position
    // sri = square_region_interval
    if ((cp.x >= sri.x && cp.x <= sri.x + sri.width) &&
        (cp.y >= sri.y && cp.y <= sri.y + sri.height)) {
        return true; // dentro da área
    }
    return false;
}


Rectangle ExpandRectangle(Rectangle original, int border_size) {
    Rectangle expanded;
    expanded.x = original.x - border_size;
    expanded.y = original.y - border_size;
    expanded.width  = original.width + border_size * 2;
    expanded.height = original.height + border_size * 2;
    return expanded;
}