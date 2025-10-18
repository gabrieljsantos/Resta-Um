#include "raylib.h"
#include "projeto.h"

//----------------------
// Variáveis globais
//----------------------

int pode=0;
Part tabuleiro[TAM][TAM];
int Ic = 0, Jc= 0;
int clique_atual = CLIQUE_PRIMEIRO;

int inicioX = screenWidth/3.5, inicioY = screenHeight/4; // TENTA PEGAR A MELHOR POSIÇÃO DA TELA PARA O TABULEIRO 
                                                         // PARA CENTRALIZAR O TABULEIRO
Vector2 posição = {(float)inicioX,(float)inicioY};
botao menu[dois] = {
    { true, {740.0f, 530.0f} },
    { true, {830.0f, 530.0f} }
};
//----------------------------------------------------------------------------
// IMPLEMENTAÇÕES DE FUNÇÕES NO GERAL
//----------------------------------------------------------------------------
// Função Botoes ---> Para Criar Botões
//----------------------------------------------------------------------------
void Botoes(botao(&menu)[dois]){
    for(int i = 0; i < 2; i++){
        if(menu[i].state){
            DrawCircle(menu[i].local.x, menu[i].local.y, (float)raio, (i==0)? BLUE : BLACK);
            DrawText("RESET",711, 554, 20, BLACK);
            DrawText("RESET",711, 556, 20, BLACK);   
        }
    }
}
//----------------------------------------------------------------------------
// Função inicializar_tabuleiro ---> Para Gerar Tudo Do Jogo
//----------------------------------------------------------------------------
void inicializa_tabuleiro(Part (&tabuleiro)[TAM][TAM]) {
    //int inicioX = screenWidth/3.5, inicioY = screenHeight/4; 
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j].pos ={ (float)inicioX + i * (diametro + espaco),
                                   (float)inicioY + j * (diametro + espaco) };
            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = 0; // NAO EXISTE
            else
                tabuleiro[i][j].state = 2; // PEÇA VIVA
        }
    }
    tabuleiro[3][3].state = 1; // AREA LIVRE
}
//----------------------------------------------------------------------------
// Função desenha_tabuleiro ---> Para Mostar Graficamente as Peças
//----------------------------------------------------------------------------
void desenha_tabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, bool red) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == 0) continue;
            Color cor = (tabuleiro[i][j].state == 1) ? LIGHTGRAY : BEIGE; // COR DAS PEÇASE VAZIO
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);
            for(int o = 0; o < 3; o++)
                DrawCircleLinesV(tabuleiro[i][j].pos, raio + o, BLACK);
            if (i == i_atual && j == j_atual) {
                for (int k = 0; k < 4; k++)
                    DrawCircleLinesV(tabuleiro[i][j].pos, raio + k, (valida_Part(tabuleiro,i,j, &k))? GREEN: RED);
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

    else if (Ic != Ifim&& Jc!= jfim) return MOVIMENTO_INVALIDO;

    else if (abs(Ifim- Ic) == 2 || abs(jfim - Jc) == 2) return MOVIMENTO_VALIDO;
    return MOVIMENTO_INVALIDO;
}
//----------------------------------------------------------------------------
// Função localiza_BOTAO ---> Para Localizar possiveis Botões
//----------------------------------------------------------------------------
bool localiza_BOTAO(botao (&menu)[dois], int* li){
    Vector2 mouse = GetMousePosition(); // POSIÇÃO DO MOUSE
    double menor = diametro;
    for(int i = 0; i < dois; i++){
        double a = menu[i].local.x - mouse.x;
        double b = menu[i].local.y - mouse.y;
        double c = sqrt( pow(a,2) + pow(b,2));
        if (c < menor){
            *li = i; 
            menor =c;
        }
    }
    return menor <= (double)raio;
}
//----------------------------------------------------------------------------
// Função localize_Part ---> Para Localizar Peças Existentes
//----------------------------------------------------------------------------
bool localize_Part(Part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state) {
    int e;
    if(localiza_BOTAO(menu,&e)){
        for(int i =0;i<4;i++)
            DrawCircleLinesV(menu[e].local,(float)raio +i , (e==0)? GREEN:RED);          
    }
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
// Função Valida_Part ---> Para Validar possiveis jogadas
//----------------------------------------------------------------------------
bool valida_Part(Part(&tabuleiro)[TAM][TAM], int It, int Jt, int* S){

    int Io, Jo, Id, Jd, Im,Jm; /*-- Io,Jo origem, Id,Jd Destinho, Im,Jm Meio --*/
        if(tabuleiro[It][Jt].state ==0){
            return false;
        }

        if((tabuleiro[It][Jt].state !=1 )){//diferente de peça vazia = (1,0)
            
            for (int i = 0; i < 4; i++) {
                int Di = Movimentos[i][0]; //|DELTA ESTA RECEBENDO MOVIMENTOS DO TIPO I-2, I+2, J-2, J+2
                int Dj = Movimentos[i][1]; //| QUE SAO MOVIMENTOS(ESQUERDA, DIREITA, CIMA, BAIXO)

                Id = It + Di; // i destinho = pos. atual + Delta i
                Jd = Jt + Dj; // j destinho = pos. atual + Delta j

                Im = It + Di/2; // i meio = i origem + Delta /2 
                Jm = Jt + Dj/2; // j meio = i origem + Delta /2 

                if ((tabuleiro[Id][Jd].state == 1 )&&(tabuleiro[Im][Jm].state != 1)){
                    *S;
                    return true; //Existe alguma jogada valida
                }

            }

        }
        
    

    return false;
}
//----------------------------------------------------------------------------
// Função Jogada ---> Para Fazer o Movimento no Jogo
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
                    std::cout << "Movimento inválido " << "I: " << Ic << " J: " << Jc
                     << " para I2: " << Ifim
                      << " J2: " << jfim << std::endl;
                } else {
                    int i_alvo = (Ic + Ifim) / 2; //i meio = i origem + Delta i /2
                    int j_alvo = (Jc + jfim) / 2;//i meio = i origem + Delta j /2
                    if (tabuleiro[i_alvo][j_alvo].state == 2) {
                        std::cout << "Deletando em i = " << i_alvo << "; j = " << j_alvo << std::endl;
                        tabuleiro[i_alvo][j_alvo].state = 1;tabuleiro[Ifim][jfim].state = 2;tabuleiro[Ic][Jc].state = 1;
                    } 
                }
                if (movimento != MOVIMENTO_NENHUM) {Ic = 0; Ifim = 0; Jc= 0; jfim = 0;
                }
            
            }
        }
    }
}

// FALTA TERMINAR
bool Resta_Um(Part(&tabuleiro)[TAM][TAM], int *R) {
    int Nvalido = 0, Valido = 0, S = 0,aux;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (valida_Part(tabuleiro, i, j, &S)) {
                Valido++;
                if (S == 1) {
                    Nvalido++;
                }
            }
        }
    }

    aux = Nvalido;
    std::cout << aux<< "\n";


    if (Valido > 0) {
        std::cout << "RESTA JOGO\n";
        return RESTA_JOGADA; // ainda há jogadas possíveis
    } else {
        std::cout << "NAO RESTA\n";
        return NAO_RESTA_JOGADA; // jogo terminou
    }
}

//----------------------------------------------------------------------------
// Função Titulo ---> Para Mostrar Titulo
//----------------------------------------------------------------------------
void Emblema(void){
    
    DrawText( "Resta Um",inicioX-80 , inicioY, 100, BLACK);
}
//----------------------------------------------------------------------------
// Função Titulo ---> Para Mostrar Titulo
//----------------------------------------------------------------------------
void Titulo(void){
    int R;
    DrawText("----- RESTA UM -----", 252, 50, 30,BLACK);//
    DrawText("----- RESTA UM -----", 252, 50, 30,BLACK);///------| Em cima
   // DrawText("----- RESTA UM -----", 256, 53, 30,BLACK);//------| do tabuleiro
    //DrawText("----- RESTA UM -----", 256, 53, 30,BLACK);//
    if(Resta_Um(tabuleiro, &R))
        std :: cout << R;
    else
    DrawText("GAME OVER",900/4,100,50,RED);

    int ii;
}

// void TIME(void){
//       // Exibe o timer no canto superior direito
//         int minutos = (int)tempoFinal / 60;
//         int segundos = (int)tempoFinal % 60;
//         char textoTimer[50];
//         sprintf(textoTimer, "Tempo: %02d:%02d", minutos, segundos);
//         DrawText(textoTimer, 750, 20, 20, YELLOW);
// }



//----------------------------------------------------------------------------
// Função Capitura_Informacao ---> Para Verificar OS Cliques no MOUSE
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
// Função Valida_Part ---> Para Validar possiveis jogadas
//----------------------------------------------------------------------------
void renderiza_Jogo(){
    
    //--------------------------------
    // --> Play GAME
    Jogada();
    int ii;
    
    if(localiza_BOTAO(menu,&ii)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&ii==0) {
            inicializa_tabuleiro(tabuleiro);
            pode++;}
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&ii==1) std::cout << "CLICK "<< ii << "\n";
    } 
    //---------------------------------
    // --> DESENHOS
    Botoes(menu);
    (pode==0)? Emblema() : Titulo();
    
    if(localiza_BOTAO(menu,&ii)){
        for(int i =0;i<4;i++)
            DrawCircleLinesV(menu[ii].local,(float)raio +i , (ii==0)? GREEN:RED);
    }
}
