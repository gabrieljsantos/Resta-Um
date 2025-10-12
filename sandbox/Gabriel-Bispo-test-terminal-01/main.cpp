
#include <stdio.h>
#include <stdlib.h>

#define COLUNA 10
#define LINHA 11
/*
    0 1 2 3 4 5 6 7 8
    1     +--------+
    2     |  o o o |
    3  +--+  o o o +---+
    4  | o o o o o o o |
    5  | o o o _ o o o |
    6  | o o o o o o o |
    7  +---+ o o o +---+
    8      | o o o |
    9      +-------+ 

*/


char int_para_char(int numero) {
    if (numero >= 0 && numero <= 9){
        return numero + '0'; 

    }
    else
        return '?';
}

void preenche_Tabu(char tabu[LINHA][COLUNA]) {

    for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; j++) {
            if ((i < 4 && j < 4) || (i < 4 && j > 6) ||
                (i > 6 && j < 4) || (i > 6 && j > 6) ||
                (i == 1)||(i>8)||(j==9) || j==1)  {
                    tabu[i][j] = ' ';

                if ((i<10 &&j==0) ||((3<i && i<7) && j==0)){
                    tabu[i][j]= int_para_char(i); 
                }   
                
                if ((i==0 &&j<10)||((3<j && j<7) && i==0 )){
                    tabu[i][j]= int_para_char(j);
                }   
                }else {
                    tabu[i][j] ='O';
            }
        }
    }

    // Centro vazio
    tabu[5][5] = '_';
}

void imprime_Tabu(char tabu[LINHA][COLUNA]) {

    for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; j++) {
            printf("%c ", tabu[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabu[LINHA][COLUNA];

    preenche_Tabu(tabu);
    imprime_Tabu(tabu); 

    return 0;
}