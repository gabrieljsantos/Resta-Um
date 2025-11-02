#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED
///////////////////
// --> CRIAÇÃO DA BIBILIOTECA --> projeto.h

// --> BIBLIOTECAS ULTILIZADAS
#include "raylib.h" // --> GRAFICA ULTILIZADA NO PROJETO RESTA UM
#include <iostream> // --> PARA USO DO C++
#include <math.h>   // PARA USO DE FUNÇÕES MATEMÁTICAS

///////////////////
const int fps = 144;
// Constantes
const int screenWidth = 850;   // PROPORÇÃO DA TELA
const int screenHeight = 600;  /////////////////////
const int TAM = 7;             // --> PARA TAMANHO DO TABULEIIRO
const int raio = 25;           // RAIO DA PEÇA
const int diametro = raio * 2; // DIAMETRO DA PEÇA
const int espaco = 10;         // ESPAÇO ENTRE UMA PEÇA E OUTRA
const int Movimentos[4][2] = {
    // MOVIMENTOS PARA TESTE SE A PEÇA PODE SE MOVER
    {-2, 0}, // Cima
    {+2, 0}, // Baixo
    {0, -2}, // Esquerda
    {0, +2}  // Direita
};
extern Color corFundo; // Fundo (Preto/Beige)
extern Color corPeca;  // Peças (Roxo/Marrom)
extern bool temaAtual; // TRUE = Tema 1, FALSE = Tema 2

// Estruturas:
typedef struct
{
    int state;   // 0 = N_Existe, 1 = Vazio, 2 = Peça
    Vector2 pos; // posição X e Y
} Part;          // estrutura da Peça

extern Rectangle startButton; // Botao Start
extern Rectangle themeButton; // Botao Troca de Tema
extern Rectangle resetButton; // Botao restart
extern Rectangle borda;       // Borda dos botoes

// Enumeradores:
enum Clique
{
    CLIQUE_PRIMEIRO,
    CLIQUE_SEGUNDO
}; // Enumerado para logica dos cliques
enum Movimento
{
    MOVIMENTO_VALIDO,
    MOVIMENTO_INVALIDO,
    MOVIMENTO_NENHUM
}; // logica dos movimentos
enum Resta
{
    NAO_RESTA_JOGADA,
    RESTA_JOGADA
}; // logica Para usar se resta jogada ou não
enum PART_STATE
{
    N_EXIST,
    VAZIO,
    PART
}; // logica das peças do tabuleiro
enum stateJogo
{
    main_Menu,
    STARTGAME,
    RESETGAME,
    ENDGAME
}; // logica do loop do jogo
//---

// Variáveis globais:
extern Part tabuleiro[TAM][TAM]; // tabuleiro do tipo Part(PEÇA), de tamanho 7*7
extern float startTime;          // inicio do tempo, para todos
extern int clique_atual;         // para receber a logica dos cliques
//---

// Protótipos de funções e pricedimento:
bool locateButton(Rectangle sri); // recebe o Botão como parametro

Rectangle expandRectangle(Rectangle original, float border_size); // recebe o botão como parametro e o tamanho da borda

bool trocarTema(void); // procedimento

bool jogadaValida(Part (&tabuleiro)[TAM][TAM], int(&Resta));
/**
 * @brief Verifica se ainda existem jogadas válidas no tabuleiro.
 *
 * Esta função percorre todo o tabuleiro do jogo "Resta Um" e analisa
 * se pelo menos uma peça ainda pode realizar um movimento válido.
 *
 * Para cada posição que contém uma peça (`PART`), é chamada a função
 * `validaPart()` para verificar suas possíveis jogadas (cima, baixo,
 * esquerda e direita). Se alguma peça puder se mover, a função indica
 * que o jogo ainda não terminou.
 *
 * @param tabuleiro Matriz bidimensional de estruturas Part representando
 *        o estado atual de jogas no tabuleiro.
 *
 * @param Resta Parâmetro passado por referência que indica quantas peças ('PART'),
 *          estão sem movimento válido
 *        - .
 *
 * @return `true` se existir pelo menos uma jogada válida no tabuleiro.
 *         `false` se todas as peças estiverem travadas.
 *
 * @note Esta função não executa nenhum movimento — apenas verifica
 *       a condição global de jogabilidade.
 *
 * @warning Caso `Resta` seja definido como 0, o jogo deve ser considerado
 *          encerrado. A contagem de peças restantes deve ser tratada
 *          separadamente por outras funções.
 *
 * @see validaPart(), Jogada(), calcule_movimento()
 */

bool validaPart(Part (&tabuleiro)[TAM][TAM], int iTest, int jTest);
/**
 * @brief Verifica se uma peça específica do tabuleiro possui jogadas válidas.
 *
 * Esta função analisa a peça localizada nas coordenadas @p iTest , @p jTest
 * e verifica se ela pode realizar pelo menos um movimento válido
 * de acordo com as regras do jogo "Resta Um".
 *
 * São considerados os quatro movimentos possíveis:
 * cima, baixo, esquerda e direita — conforme definidos
 * na matriz constante `Movimentos[4][2]`.
 *
 * @param tabuleiro Matriz bidimensional de estruturas Part representando
 *        o tabuleiro de jogo. Cada elemento contém o estado e a posição
 *        gráfica de uma peça.
 *
 * @param iTest Índice da linha (i) da peça a ser analisada.
 * @param jTest Índice da coluna (j) da peça a ser analisada.
 *
 * @param achou Parâmetro passado por referência que indica se há jogada válida:
 *        - `achou = 1` → Há pelo menos uma jogada possível.
 *        - `achou = 0` → Nenhuma jogada possível (peça travada).
 *
 * @return `true` se a peça nas coordenadas (iTest, jTest) pode se mover
 *         para alguma posição válida segundo as regras do jogo.
 *         `false` caso contrário.
 *
 * @note A função verifica se o movimento
 *       não ultrapassa os limites da matriz (usando verificações de faixa).
 *       Um movimento é considerado válido se:
 *       - A posição destino está dentro do tabuleiro (`TAM`);
 *       - Há uma peça intermediária (`PART`) entre origem e destino;
 *       - A posição final está vazia (`VAZIO`).
 *
 * @warning Esta função não realiza o movimento — apenas verifica se ele é possível.
 *          A execução do movimento é feita pela função `Jogada()`.
 *
 * @see Jogada(), jogada_Valida(), calcule_movimento()
 */

bool localizePart(Part (&tabuleiro)[TAM][TAM], int *ii, int *jj, int state = -1); // >>>
/**
 * @brief Localiza a peça do tabuleiro clicada pelo jogador.
 *
 * @param tabuleiro Matriz de estruturas Part representando o tabuleiro.
 * @param ii Ponteiro para a linha (índice i) da peça localizada.
 * @param jj Ponteiro para a coluna (índice j) da peça localizada.
 * @param state (opcional) Tipo de célula a ser considerada (-1 para qualquer uma).
 *
 * @return true se o clique ocorreu dentro do raio de uma peça válida.
 * @return false caso contrário.
 *
 * @note Usa a função GetMousePosition() da Raylib para detectar o clique.
 * @see calcule_movimento(), valida_Part(), Jogada()
 */

int calculeMovimento(int i_inicial, int j_inicial, int i_fim, int j_fim);

void Titulo(void); // procedimento: Mostra BOTOES e Nome do JOGO

void Emblema(void); // procedimento: Mostra BOTÃO e nome do jogo

void Jogada(void); // procedimento: atualiza os cliques e faz a logica do jogo(Mediante as regras)

void inicializaTabuleiro(Part (&tabuleiro)[TAM][TAM]);

void desenhaTabuleiro(Part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual, int clique_atual);

void DisplayTimer(void); // procedimento

#endif // PROJETO_H_INCLUDED
