//-----------------------------------------
#include "raylib.h"
#include "projeto.h"

//----------------------
// VARIÁVEIS GLOBAIS
//----------------------
float startTime = 0.0f;  
float timeElapsed;
int minutos;
int segundos;
char textoTimer[50];
//--> Para Mostrar o tempo parado, ou seja, qundo para de atualizar.
///////////////////////////////////////////////////////////////////

Part tabuleiro[TAM][TAM]; //Tabuleiro Global para dar acesso em todas a funçoes que necessita 
  
int i_atual = 0, j_atual = 0; //vareaveis para guardar o I e J do primeioro clique na peça escolhida
     
int clique_atual = CLIQUE_PRIMEIRO; // esperando primeiro clique

bool temaAtual = true;// Começa com Tema 1
Color corBotao = BROWN;    // Botao 1: Marrom Claro
Color corFundo = BEIGE;    // Fundo 1: Beige
Color corPeca = DARKBROWN; // Peça  1: Marrom Escuro
Color corTabu = BROWN;     // tabu  1: Marrom claro
Color corTabuF = DARKBROWN;   // tabu  1: Marrom claro
Color corTime = BLACK;     // Time  1: Preto
   // Tema 1: Beige/Marrom

int inicioX = screenWidth/3.5; //POSIÇÃO "ABICISSA" (x), ONDE INICIA A IMPREÇÃO DO TABULEIRO
int inicioY = screenHeight/4;  //POSIÇÃO "ORDENADA" (y), ONDE INICIA A IMPREÇÃO DO TABULEIRO 
 
//                                                            BOTÕES E SUAS COORDENADAS{
Rectangle restartButton = {700.0f, 500.0f, 100.0f, 45.0f}; // RESTART --> RENICIAR JOGO
Rectangle startButton = {350, 350, 150.0f, 70.0f};         // START --> INICIAR JOGO
Rectangle themeButton = {30.0f, 500.0f, 100.0f, 45.0f};    // THEME --> TEMA            }

Rectangle borda; //Vareavel Borda, do TIPO Retangle para mostrar identificar botao com cor VERDE
//(No momento, vazia) criada 1 vez somente
//----------------------------------------------------------------------------
//            ----> IMPLEMENTAÇÃO DE FUNÇÕES E PROCEDIMENTOS <----
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// PROCEDIMENTO inicializar_tabuleiro
//----------------------------------------------------------------------------
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) { // POSIÇÃO INICIAL(x,y) + ("I,J"  *  "(DIAMETRO + ESPAÇO)")
            tabuleiro[i][j].pos = {(float)inicioX + i * (diametro + espaco), 
                                   (float)inicioY + j * (diametro + espaco)};
            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = N_EXIST; // Parte transparente, sem nada!
            else
                tabuleiro[i][j].state = EXIST;  // peças do jogo
        }
    }
    tabuleiro[3][3].state = VAZIO; // posição do tabuleiro (meio) vazia
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
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_aux, int j_aux, int clique_atual){
    DrawRectangle(inicioX-50, inicioY-50, 460, 460, corTabuF);  //| QUADRADO FUNDO
    DrawRectangle(inicioX-40, inicioY-40, 440, 440, corTabu);   //| QUADRADO TABULEIRO
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            if (tabuleiro[i][j].state == N_EXIST) continue;

            Color cor = (tabuleiro[i][j].state == VAZIO) ? LIGHTGRAY : corPeca; 
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);

            for(int o = 0; o < 3; o++)
                DrawCircleLinesV(tabuleiro[i][j].pos, raio + o, BLACK);//contorno

            int r_aux;
            if(jogada_Valida(tabuleiro,r_aux)){

                int movimento = calcule_movimento(i_atual, j_atual, i_aux, j_aux); // Mostra onde a peça pode se mover
                if(movimento == MOVIMENTO_VALIDO && tabuleiro[i_aux][j_aux].state == VAZIO) {
                    for(int i = 0;i<4;i++)
                        DrawCircleLinesV(tabuleiro[i_aux][j_aux].pos,raio+i,GREEN);
                }  

                if (i == i_aux && j == j_aux) {
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
        // abs retorna o modulo do valor 
    return MOVIMENTO_INVALIDO; // se tentar jogar em diagonal
}

//--------------------------------------------------------------------------
// Função locateButton ---> PARA LOCALIZAR OS BOTOES 
//----------------------------------------------------------------------------
bool locateButton(Rectangle sri) { // --> Passa o Botao como parametro
    Vector2 mouse = GetMousePosition(); // recebe a posição do mouse
    // para comparação 
    // sri = square_region_interval
    if ((mouse.x >= sri.x && mouse.x <= sri.x + sri.width) &&
        (mouse.y >= sri.y && mouse.y <= sri.y + sri.height)) {
        return true; // dentro da área
    }
    return false;
}
//--------------------------------------------------------------------------
// Função ExpandRectangle ---> Uma borda no botao localizado
//----------------------------------------------------------------------------
Rectangle expandRectangle(Rectangle original, int border_size) {
    Rectangle expanded;
    expanded.x = original.x - border_size;
    expanded.y = original.y - border_size;
    expanded.width  = original.width + border_size * 2;
    expanded.height = original.height + border_size * 2;
    return expanded;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Função localize_Part ---> Para Localizar Peças Existentes
// DENTRO DO RAIO DA PEÇA
//----------------------------------------------------------------------------

bool localize_Part(Part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state) {
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

bool valida_Part(Part(&tabuleiro)[TAM][TAM], int I_origem, int j_origem, int (&estado)){

    int i_destino, j_destino, i_meio,j_meio; /*-- I, J origem, I,J Destinho, I,J Meio --*/

       estado = 0; // nao tem movimento valido
       // estado retorna o valor por referencia
        if(tabuleiro[I_origem][j_origem].state == N_EXIST) //parte que esta fora (em branco)
            return false;

        if(tabuleiro[I_origem][j_origem].state != EXIST) // nao é uma peça valida
            return false;

        //---------------------------------------------------------------------

        //agora tenta os movimentos valido para achar a peça sem estar travada
        //---------------------------------------------------------------------
        for (int i = 0; i < 4; i++) {
            int delta_i = Movimentos[i][0]; //|DELTA ESTA RECEBENDO MOVIMENTOS DO TIPO (I-2, I+2, J-2, J+2)
            int delta_j = Movimentos[i][1]; //| QUE SAO MOVIMENTOS(ESQUERDA, DIREITA, CIMA, BAIXO)
            i_destino = I_origem + delta_i; // i destinho = pos. atual + Delta i
            j_destino = j_origem + delta_j; // j destinho = pos. atual + Delta j

            i_meio = I_origem + delta_i/2; // i meio = i origem + Delta /2 
            j_meio = j_origem + delta_j/2; // j meio = i origem + Delta /2 
            
            //--------------------------------------------------------------
            //Testa para ver se as possiveis jogadas estao no limite do tabu
            if (i_destino < 0 || i_destino >= TAM || j_destino < 0 || j_destino >= TAM) continue;
            if (i_meio < 0 || i_meio >= TAM || j_meio < 0 || j_meio >= TAM) continue;
            //verifica se a jogada da peça pode sair do tabuleiro
            //---------------------------------------------------------------

            if ((tabuleiro[i_destino][j_destino].state == VAZIO )&& (tabuleiro[i_meio][j_meio].state != VAZIO)){
                estado = 1; // um movimento valido
                return true; //Existe alguma jogada valida
            }
        }
        // Se nao tem movimento
        estado = 0; 

    return false;
}

//----------------------------------------------------------------------------
// PROCEDIMENTO Jogada ---> Para Fazer o Movimento no Jogo
//CAPITURA OS CLIQUES E VERIFICA SE PODE JOGAR
//----------------------------------------------------------------------------
int aux_i,aux_j;
void Jogada(void){
     clique_atual = (i_atual == 0 && j_atual == 0) ? CLIQUE_PRIMEIRO : CLIQUE_SEGUNDO; // atualização do clique

    if(clique_atual == CLIQUE_SEGUNDO)
        for(int i = 0; i < 4;i++)
            DrawCircleLinesV(tabuleiro[aux_i][aux_j].pos,raio+i,BLUE); 


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    
        if (clique_atual == CLIQUE_PRIMEIRO) {
            if (localize_Part(tabuleiro, &i_atual, &j_atual, EXIST)) {
                aux_i = i_atual;
                aux_j = j_atual;
            }
         } else {
            int i_fim = 0, j_fim = 0;
            if (localize_Part(tabuleiro, &i_fim, &j_fim, VAZIO)) {
                
            
               int movimento = calcule_movimento(i_atual, j_atual, i_fim, j_fim);

                if (movimento == MOVIMENTO_INVALIDO) {
                    DrawText("MOVIMENTO INVALIDO",250,90,30,RED);
                } else {
                    int i_alvo = (i_atual + i_fim) / 2; //i meio = i origem + Delta i /2
                    int j_alvo = (j_atual + j_fim) / 2;//i meio = i origem + Delta j /2

                    if (tabuleiro[i_alvo][j_alvo].state == EXIST) {
                        //-----------------------------------//
                        tabuleiro[i_alvo][j_alvo].state = VAZIO; //
                        tabuleiro[i_fim][j_fim].state = EXIST;     //  atualiza o estado das peças movidas
                        tabuleiro[i_atual][j_atual].state = VAZIO;         //
                        //-----------------------------------//
                    } 
                }
                if (movimento != MOVIMENTO_NENHUM) {i_atual = 0; i_fim = 0; j_atual= 0; j_fim = 0;
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
            int achou = 0;
            if ((tabuleiro)[i][j].state == N_EXIST) continue;
            //NAO PODE TESTAR PARTE EM BRAMCO DA ERRO!!!!
            valida_Part(tabuleiro, i, j, achou);
                
            if (achou == 1) {
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
    DrawText("Resta Um", inicioX-60, inicioY, 100, corPeca);
//---{Para Criar uma Borda no Botão a ser selecionado    
    if(locateButton(startButton)){
        borda = expandRectangle(startButton,4);
        DrawRectangleRec(borda,GREEN);
    }
//----------------------------------------------------
// Botão desenhado
    DrawRectangleRec(startButton, corBotao);//Botao Start
    DrawText("START", screenWidth/2-43, screenHeight/2+70, 25, BLACK);
}
//----------------------------------------------------------------------------
// PROCEDIMENTO Titulo --> Para Mostrar GAMEOVER/VITORIA, BOTOES, e TITULO
//----------------------------------------------------------------------------
void Titulo(void){
    int resta;
    DrawText("----- RESTA UM -----", 252, 50, 30, corPeca); // ----> Titulo

//---{Para Criar uma Borda no Botão a ser selecionado 
    if(locateButton(restartButton)){
        borda = expandRectangle(restartButton,4);
        DrawRectangleRec(borda,GREEN);
    }
     
    if(locateButton(themeButton)){
        borda = expandRectangle(themeButton,4);
        DrawRectangleRec(borda,GREEN);
    }
//---}
    // TIMER - SEM PARÂMETRO
    DisplayTimer();

    // logica de VITORIA OU GAME OVER
    if(!jogada_Valida(tabuleiro, resta)){ 
        if (resta == 1) {
            DrawText("Vitória", 100, 50, 30, BLUE);
        } else {
            DrawText("GAME OVER", screenWidth/2 -120, screenHeight/2, 40, RED);
            DrawText(TextFormat("Restaram: %d", resta), 25, 70, 30, corPeca);
        }
    }
    //Botões que serao desenhados THEME e RESTART
    DrawRectangle(restartButton.x, restartButton.y, restartButton.width, restartButton.height, corBotao);
    DrawRectangle(themeButton.x, themeButton.y, themeButton.width, themeButton.height, corBotao);
     //--------------------------------------{ nome e posições do botão
    DrawText("RESET", 715, 515, 20, BLACK); //NOME
    DrawText("TEMA", 45, 515, 20, BLACK); // NOME
    //--------------------------------------}
}
    
//----------------------------------------------------------------------------
// Função DisplayTimer ---> PARA mostar Tempo 
//----------------------------------------------------------------------------
void DisplayTimer(void) {
    int resta;
    if(jogada_Valida(tabuleiro,resta)){
         timeElapsed = GetTime() - startTime;
         minutos = (int)timeElapsed / 60;
         segundos = (int)timeElapsed % 60;

        //Mostra o tempo em atualização
        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 640, 20, 25, corTime);
    }
    if (!jogada_Valida(tabuleiro,resta)){
    
        //Mostra o tempo parado
        sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
        DrawText(textoTimer, 640, 20, 25, corTime);
    }
}
