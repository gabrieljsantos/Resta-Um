#include "orthogonal_neighborhood.h"

Orthogonal_Neighborhood get_Orthogonal_Neighborhood(int index_selection,
    struct Part parts[],
    int size_of_parts ,
    struct Part empty_place[],
    int size_of_empty_place)
    {

    Orthogonal_Neighborhood neighborhood;

    for(int i=0;i<2;i++){
    neighborhood.right[i].type = NEIGHBOR_NONE;
    neighborhood.up[i].type = NEIGHBOR_NONE;
    neighborhood.left[i].type = NEIGHBOR_NONE;
    neighborhood.down[i].type = NEIGHBOR_NONE;
}
    int x_seleted = parts[index_selection].posX;
    int y_seleted = parts[index_selection].posY;
    //encontrar espaços vazios
    for (int i = 0; i < size_of_empty_place; i++)
        // varredura direita
        for(int j = 0; j < 2; j++){
            if ((x_seleted == empty_place[i].posX - 1) && (y_seleted == empty_place[i].posY)){
                neighborhood.right[0].index = i;
            }
        }

        // Existem duas peças ou espaços vizinhos nessa direção?
    for(int j = 0; j < size_of_empty_place; j++){
        if ((x_seleted == empty_place[j].posX - 1) && (y_seleted == empty_place[j].posY)){
            is_right_1 = true;
        }
        if ((x_seleted == empty_place[j].posX - 2) && (y_seleted == empty_place[j].posY)){
            is_right_2 = true;
            index_right = j;
        }
        if ((x_seleted == empty_place[j].posX + 1) && (y_seleted == empty_place[j].posY)){
            is_left_1 = true;
        }
        if ((x_seleted == empty_place[j].posX + 2) && (y_seleted == empty_place[j].posY)){
            is_left_2 = true;
            index_left = j;
        }
        if ((x_seleted == empty_place[j].posX) && (y_seleted == empty_place[j].posY + 1)){
            is_up_1 = true;
        }
        if ((x_seleted == empty_place[j].posX ) && (y_seleted == empty_place[j].posY + 2)){
            is_up_2 = true;
            index_up = j;
        }
        if ((x_seleted == empty_place[j].posX) && (y_seleted == empty_place[j].posY - 1)){
            is_down_1 = true;
        }
        if ((x_seleted == empty_place[j].posX) && (y_seleted == empty_place[j].posY - 2 )){
            is_down_2 = true;
            index_down = j;
        }
    }
}
