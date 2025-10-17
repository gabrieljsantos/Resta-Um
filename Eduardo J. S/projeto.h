#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

#include "raylib.h"
#include <stdio.h>
#include <iostream>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm> // Para std::sort

#define TAM 7
#define MAX_RECORDES 10

typedef struct {
    char nome;      // Apenas 1 letra identificando o jogador
    float tempo;    // Tempo em segundos
} Recorde;

//--------------------------------------------------------------------------------------
// Constantes gráficas
//--------------------------------------------------------------------------------------
const int raio = 25;
const int diametro = raio * 2;
const int espaco = 10;

//--------------------------------------------------------------------------------------
// Enumeração de estados de movimento da peça
//--------------------------------------------------------------------------------------
enum Movimento {
    MOVIMENTO_VALIDO,
    MOVIMENTO_INVALIDO,
    MOVIMENTO_NENHUM
};

//--------------------------------------------------------------------------------------
// Estruturas auxiliares para índice e peças do tabuleiro
//--------------------------------------------------------------------------------------
typedef struct {
    int i;
    int j;
} Index2;

///-----> Tipo peça
typedef struct {
    int state;   /// 0 = inválido, 1 = vazio, 2 = peça
    Vector2 pos; /// posição X e Y em pixels
} part;

//--------------------------------------------------------------------------------------
// Função: inicializa_tabuleiro
// Cria o tabuleiro com valores lógicos e posiciona as peças em coordenadas de tela.
//--------------------------------------------------------------------------------------
void inicializa_tabuleiro(part (&tabuleiro)[TAM][TAM]) {
    int inicioX = 280, inicioY = 150;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            /// Transforma as coordenadas em PIXEL
            
            tabuleiro[i][j].pos = { 
             (float)(inicioX + i * (diametro + espaco)), 
             (float)(inicioY + j * (diametro + espaco))
};

            if ((i < 2 || i > 4) && (j < 2 || j > 4))
                tabuleiro[i][j].state = 0; // parte inválida = 0
            else
                tabuleiro[i][j].state = 2; // peça = 2
        }
    }

    tabuleiro[3][3].state = 1; // centro vazio = 1
}

//--------------------------------------------------------------------------------------
// Função: desenha_tabuleiro
// Desenha o tabuleiro na tela e destaca a posição atual do mouse.
//--------------------------------------------------------------------------------------
void desenha_tabuleiro(part (&tabuleiro)[TAM][TAM], int i_atual, int j_atual) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == 0) continue;

            Color cor = (tabuleiro[i][j].state == 1) ? LIGHTGRAY : PURPLE;
            DrawCircleV(tabuleiro[i][j].pos, raio, cor);

            // Desenha 3 linhas ao redor do círculo que o mouse sobrepõe
            if (i == i_atual && j == j_atual) {
                for (int k = 0; k < 3; k++)
                    DrawCircleLinesV(tabuleiro[i][j].pos, raio + k, WHITE);
            }
        }
    }
}

//--------------------------------------------------------------------------------------
// Função: calcule_movimento
// Calcula se o movimento da peça é válido, inválido ou nulo.
//--------------------------------------------------------------------------------------
int calcule_movimento(int i_inicial, int j_inicial, int i_final, int j_final) {
    if (i_inicial == i_final && j_inicial == j_final) {
        return MOVIMENTO_NENHUM; // Nenhum movimento
    } else if (i_inicial != i_final && j_inicial != j_final) {
        return MOVIMENTO_INVALIDO; // Movimento diagonal é inválido
    } else if (abs(i_final - i_inicial) == 2 || abs(j_final - j_inicial) == 2) {
        return MOVIMENTO_VALIDO; // Movimento válido (pula 1 casa)
    }

    return MOVIMENTO_INVALIDO;
}

//--------------------------------------------------------------------------------------
// Função: localize_peca
// Localiza a peça mais próxima do mouse. Retorna true se o clique estiver dentro de uma peça.
//--------------------------------------------------------------------------------------
bool localize_peca(part (&tabuleiro)[TAM][TAM], int* ii, int* jj, int state = -1) {
    Vector2 Mouse = { (float)GetMouseX(), (float)GetMouseY() };

    double menor = diametro;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == state || state == -1) {
                double a = tabuleiro[i][j].pos.x - Mouse.x;
                double b = tabuleiro[i][j].pos.y - Mouse.y;
                double c = sqrt(pow(a, 2) + pow(b, 2));

                if (c < menor) {
                    menor = c;
                    *ii = i;
                    *jj = j;
                }
            }
        }
    }

    return (menor <= (double)raio);
}

//--------------------------------------------------------------------------------------
// Função: reset_tabuleiro
// Reinicia o estado do tabuleiro para o padrão inicial (como no início do jogo).
//--------------------------------------------------------------------------------------
void reset_tabuleiro(part (&tabuleiro)[TAM][TAM]) {
    inicializa_tabuleiro(tabuleiro);
    std::cout << "Tabuleiro reiniciado!" << std::endl;
}

//-------------------------------------------------------------------------------------
// Função salvar recorde 
// Salva o melhor tempo atual em uma especie ranking
//-------------------------------------------------------------------------------------
void salvarRecorde(const char* nome, float tempo) {
    FILE* arquivo = fopen("recordes.txt", "a"); // abre em modo append
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo de recordes!\n");
        return;
    }

    fprintf(arquivo, "%c %.2f\n", nome[0], tempo); // Usa apenas a primeira letra
    fclose(arquivo);
}

//-------------------------------------------------------------------------------------
// Função: carrega_recordes
// Carrega os recordes do arquivo para um array e retorna o número de recordes carregados.
//-------------------------------------------------------------------------------------
int carrega_recordes(Recorde recordes[MAX_RECORDES]) {
    FILE* arquivo = fopen("recordes.txt", "r");
    if (arquivo == NULL) {
        return 0;
    }

    int count = 0;
    while (count < MAX_RECORDES && fscanf(arquivo, " %c %f", &recordes[count].nome, &recordes[count].tempo) == 2) {
        count++;
    }

    fclose(arquivo);
    return count;
}

//-------------------------------------------------------------------------------------
// Função: ordena_recordes
// Ordena o array de recordes por tempo ascendente (melhores tempos primeiro).
//-------------------------------------------------------------------------------------
void ordena_recordes(Recorde recordes[], int count) {
    std::sort(recordes, recordes + count, [](const Recorde& a, const Recorde& b) {
        return a.tempo < b.tempo;
    });
}

//-------------------------------------------------------------------------------------
// Função Mostra o record (modificada para ordenar e ajustar posição)
// lê e exibe os recordes na tela usando Raylib, agora ordenados.
//-------------------------------------------------------------------------------------
void mostrarRecordesOrdenados() {
    Recorde recordes[MAX_RECORDES];
    int count = carrega_recordes(recordes);

    if (count == 0) {
        DrawText("Nenhum recorde salvo ainda!", 50, 70, 20, WHITE); // Ajustado para y=70, acima do jogador
        return;
    }

    ordena_recordes(recordes, count);

    int y = 130; // Ajustado para começar abaixo do nome do jogador
    DrawText("==== RECORDES ====", 50, y, 20, YELLOW);
    y += 30;

    for (int i = 0; i < count; ++i) {
        char linha[50];
        int minutos = (int)recordes[i].tempo / 60;
        int segundos = (int)recordes[i].tempo % 60;
        sprintf(linha, "%c - %02d:%02d", recordes[i].nome, minutos, segundos);
        DrawText(linha, 50, y, 20, WHITE);
        y += 25;
    }
}

//-------------------------------------------------------------------------------------
// Função: conta_pecas_restantes
// Conta o número de peças (state == 2) restantes no tabuleiro.
//-------------------------------------------------------------------------------------
int conta_pecas_restantes(part (&tabuleiro)[TAM][TAM]) {
    int count = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j].state == 2) {
                count++;
            }
        }
    }
    return count;
}

//-------------------------------------------------------------------------------------
// Função: get_nova_letra
// Retorna uma letra única para identificar o jogador, baseada nos recordes existentes.
//-------------------------------------------------------------------------------------
char get_nova_letra() {
    static char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    static int indice = 0;

    Recorde recordes[MAX_RECORDES];
    int count = carrega_recordes(recordes);

    // Verifica letras já usadas
    bool usado[10] = {false};
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (recordes[i].nome == letras[j]) {
                usado[j] = true;
            }
        }
    }

    // Encontra a próxima letra não usada
    while (indice < 10 && usado[indice]) {
        indice = (indice + 1) % 10;
    }

    char letra = letras[indice];
    indice = (indice + 1) % 10; // Avança para a próxima letra
    return letra;
}

//--------------------------------------------------------------------------------------
// Protótipo: AtualizaTabu
// (Ainda não implementada)
//--------------------------------------------------------------------------------------
void AtualizaTabu();

#endif // PROJETO_H_INCLUDED
