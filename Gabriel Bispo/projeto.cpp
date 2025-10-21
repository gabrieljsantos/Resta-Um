#include "raylib.h"
#include "projeto.h"

//----------------------
// Variáveis globais
//----------------------
int i_inicial=0, j_inicial=0;
int pode=0;
Part tabuleiro[TAM][TAM];
int Ic = 0, Jc= 0;
int clique_atual = CLIQUE_PRIMEIRO;

int inicioX = screenWidth/3.5, inicioY = screenHeight/4; // TENTA PEGAR A MELHOR POSIÇÃO DA TELA PARA O TABULEIRO 
                                                         // PARA CENTRALIZAR O TABULEIRO
Rectangle restart = {
    700.0f,500.0f,
    100.0f,45.0f

};

Rectangle start_P = { // coordenadas do botao
      350, 350,   // X e Y inicio
      150.0f, 70.0f    // X e Y UM EMCREMENTO PARA CRIAR O RETANGULO
  };
//----------------------------------------------------------------------------
// IMPLEMENTAÇÕES DE FUNÇÕES E PROCEDIMENTOS NO GERAL
//----------------------------------------------------------------------------
// PROCEDIMENTO inicializar_tabuleiro ---> Para Gerar Tudo Do Jogo
//----------------------------------------------------------------------------
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].pos ={ (float)inicioX + i * (diametro + espaco),
                                   (float)inicioY + j * (diametro + espaco) };
            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = N_EXIST; // NAO EXISTE
            else
                tabuleiro[i][j].state = EXIST; // PEÇA VIVA
        }
    }
    tabuleiro[3][3].state = VAZIO; // AREA LIVRE
}
//----------------------------------------------------------------------------
// PROCEDIMENTO desenha_tabuleiro ---> Para Mostar Graficamente as Peças
//----------------------------------------------------------------------------
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, bool red){
    //DrawRectangle(inicioX-40,inicioY-40,440,440,BROWN);
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            
            
            if (tabuleiro[i][j].state == 0) continue;
           

            Color cor = (tabuleiro[i][j].state == 1) ? LIGHTGRAY : PURPLE; // COR DAS PEÇAS 
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);
            if (i == i_atual && j == j_atual) {
                
       /*aux*/  int aux = 0;//PARA FUNÇAO (VALIDA PART)
   /*MOVIMENTO*/bool Mov = valida_Part(tabuleiro, i,j, aux);
                Color Cor = (Mov)? GREEN:RED;
                for (int k = 0; k < 4; k++)
                    DrawCircleLinesV(tabuleiro[i][j].pos, (float)raio + k, Cor);
                    
            }
        }
    }
}
//----------------------------------------------------------------------------
// Função calcule_movimento ---> Para Calcular Movimento valido
//----------------------------------------------------------------------------
int calcule_movimento(int Ic, int Jc
    , int Ifim
    , int jfim) {
    if (Ic == Ifim && Jc== jfim) return MOVIMENTO_NENHUM;

    else if (Ic != Ifim&& Jc!= jfim)return MOVIMENTO_INVALIDO;

    else if (abs(Ifim- Ic) == 2 || abs(jfim - Jc) == 2) return MOVIMENTO_VALIDO;
    return MOVIMENTO_INVALIDO;
}
//----------------------------------------------------------------------------
// Função localiza_BOTAO ---> Para Localizar possiveis Botões
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
    return menor <= (double)raio;
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

            if ((tabuleiro[Id][Jd].state == 1 )&&(tabuleiro[Im][Jm].state != VAZIO)){
                S = 1; // um movimento valido
                return true; //Existe alguma jogada valida
            }
        }
        // se chegou ate aqui
        S = 0; 

    return false;
}
//----------------------------------------------------------------------------
// PROCEDIMENTO Jogada ---> Para Fazer o Movimento no Jogo
//CAPITURA OS CLIQUES E VERIFICA SE PODE JOGAR
//----------------------------------------------------------------------------

void Jogada(void){

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    
        if (clique_atual == CLIQUE_PRIMEIRO) {
            if (localize_Part(tabuleiro, &Ic, &Jc, 2)) {
                std::cout << "Primeiro clique na posição X: " << tabuleiro[Ic][Jc].pos.x << ", Y: " << tabuleiro[Ic][Jc].pos.y << std::endl;
            }
         } else {
            int Ifim = 0, jfim = 0;
            if (localize_Part(tabuleiro, &Ifim, &jfim, 1)) {
               std::cout << "Segundo clique na posição X: " << tabuleiro[Ifim][jfim].pos.x << ", Y: " << tabuleiro[Ifim][jfim].pos.y << std::endl;                
               int movimento = calcule_movimento(Ic, Jc, Ifim, jfim);

                if (movimento == MOVIMENTO_INVALIDO) {
                    //DrawText("MOVIMENTO INVALIDO",250,90,30,RED);
                    
                  //  Sleep(1000);
                } else {
                    int i_alvo = (Ic + Ifim) / 2; //i meio = i origem + Delta i /2
                    int j_alvo = (Jc + jfim) / 2;//i meio = i origem + Delta j /2

                    if (tabuleiro[i_alvo][j_alvo].state == 2) {
                         std::cout << "Deletando em i = " << i_alvo << "; j = " << j_alvo << std::endl;
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
// Função RESTA UM ---> Para verificar quantidade de peças sem movimento valido
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
}//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
// PROCEDIMENTO Titulo ---> Para Mostrar EMBLEMA DO JOGO
//----------------------------------------------------------------------------
void Emblema(void){
    
    DrawText( "Resta Um",inicioX-80 , inicioY, 100, PURPLE);

    DrawRectangleRec(start_P,PURPLE);
    DrawText( "START",screenWidth/2-43 , screenHeight/2+70, 25, BLACK);
    if(locale_Button()){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) inicializa_tabuleiro(tabuleiro);
        for(int i = 0; i<4;i++){ 
             DrawRectangleLines(screenWidth/2-75-i, 350-i,152+i,72+i,GREEN);

        }

    }
   
}
//----------------------------------------------------------------------------
// PROCEDIMENTO Titulo ---> Para Mostrar Titulo
//----------------------------------------------------------------------------
void Titulo(void){
    int R;
    DrawText("----- RESTA UM -----", 252, 50, 30,PURPLE);//
    DrawText("----- RESTA UM -----", 252, 50, 30,PURPLE);///------| Em cima

    DrawRectangle(restart.x,restart.y,restart.width,restart.height,BLUE);
    DrawText("RESET",715,515,20,BLACK);

    if(!jogada_Valida(tabuleiro, R)){ // se nao ouver jogada valida game over ou vitoria

        if (R == 1) DrawText("Vitória", 100, 50, 30, BLUE);
        else{
        DrawText("GAME OVER",900/2 -100,600/2,30,RED);
        DrawText(TextFormat("Restaram: %d", R), 100, 150, 30, PURPLE);
        }
    }    
    
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Atualiza_Informacao ---> Para Verificar OS Cliques no MOUSE
//----------------------------------------------------------------------------
void Atualiza_Imformação(){
    
    clique_atual = (Ic == 0 && Jc== 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO;
    int i_atual = 0, j_atual = 0;
    localize_Part(tabuleiro, &i_atual, &j_atual);
    if (clique_atual == CLIQUE_PRIMEIRO) {
        desenha_tabuleiro(tabuleiro, i_atual, j_atual, tabuleiro[i_atual][j_atual].state != 2);
    } else {
        int movimento = calcule_movimento(Ic, Jc
            , i_atual, j_atual);
        desenha_tabuleiro(tabuleiro, i_atual, j_atual, movimento != MOVIMENTO_VALIDO);
    }
}
//----------------------------------------------------------------------------
// PROCEDIMENTO renderiza Jogo ---> Para Renderizar e Fucionar o JOGO
//----------------------------------------------------------------------------
//SEM USAR NO MOMENTO, POR MOTIVOD DE TESTES
void renderiza_Jogo(){
    Emblema();

    //--------------------------------
    // --> Informações sobre os cliques
     Atualiza_Imformação();
    //------------------------------------
    
    //--------------------------------
    // --> Play GAME
     Jogada();
    //------------------------------------
    int ii;
    
    //---------------------------------
    // --> DESENHOS
    //(pode==0)? Emblema() : Titulo();
    
}
