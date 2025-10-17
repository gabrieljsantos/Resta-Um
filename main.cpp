

/*******************************************************************************************

********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> // usar booleanos
#include <vector>
#include <stdbool.h> // imprimir booleano
#include <math.h>


struct Part { // Criando uma estrutura para criar um vetor
    int index;
    int posX;
    int posY;
    bool state;
};

struct Part parts[32]; // criando um vetor, do tipo struct part, qual foi definido anterioemente.
struct Part empty_place[33];



void parts_generator(struct Part parts[], int size, bool state, bool empty_place = false){
    int index = 0;
    for (int i = -3; i <= 3; i++){
        for(int j = -3; j <= 3; j++){
            bool is_center = (i == 0 && j == 0);           // Verdadeiro se for a posição central
            bool is_corner = (abs(i) > 1 && abs(j) > 1);  // Verdadeiro se for a posição dos cantos, maior que 1.
            if (empty_place) { // força para falso para gerar a do meio se for do tipo de item vazio.
                if (!(is_corner)){
                    if (index == size){
                        return;
                    }
                    parts[index].posX = i;
                    parts[index].posY = j;
                    if (is_center){
                        parts[index].state = true;
                    } else {
                        parts[index].state = false;
                    }                        
                    index++;
                }
            } else {
                if (!((is_center) || (is_corner))){
                    if (index == size){
                        return;
                    }
                    parts[index].posX = i;
                    parts[index].posY = j;
                    parts[index].state = state;                           
                    index++;
                }
            }

        }
    }
};



void parts_print_cosole(struct Part parts[], int size){
    int index = 0;
    for (int i = 0; i < size; i++){
        printf("%d , %d, %d, %d \n", i, parts[i].posX, parts[i].posY, parts[i].state);
    }
};

int translate_cartesian_to_screen(int value, int screen_size){
    return value + (screen_size/2);
}

int translate_screen_to_cartesian(int value, int screen_size){
    return value - (screen_size/2);
}


// tá 0, 1, 2 ou 3, 0 100, 200,  300, -2 
int scaled_to_screen(int value, int screen_size, int spacing){
    return translate_cartesian_to_screen((value * spacing), screen_size);
}

int scaled_to_screen_reverse(int value, int screen_size, int spacing){
    int new_position_centralized = translate_screen_to_cartesian(value, screen_size);
    return new_position_centralized/spacing;
}

int get_distance(int x, int y, int x1, int y1){
    int dx = x1 - x;
    int dy = y1 - y;
    return sqrt((dx*dx)+(dy*dy));
};

struct selection {
    int index;
    int Xcartesian;
    int Ycartesian;
    int X;
    int Y;
    bool state;
    
};
selection get_selected(Vector2 mouse, int R, int spacing, Vector2 screen, struct Part parts[], int size){
    selection selected;
    for (int i = 0; i < size; i++){
        if (parts[i].state == true){
            if ( get_distance(
                    scaled_to_screen(parts[i].posX,screen.x,spacing),
                    scaled_to_screen(parts[i].posY,screen.y,spacing),
                    mouse.x,
                    mouse.y
                        ) < R) {
                            selected.index = i;
                            selected.Xcartesian = parts[i].posX;
                            selected.Ycartesian = parts[i].posY;
                            selected.X = scaled_to_screen(parts[i].posX,screen.x,spacing);
                            selected.Y = scaled_to_screen(parts[i].posY,screen.y,spacing);
                            selected.state = true;

            }
        } else {
            selected.state = false;
        }
    } return selected;

};

struct Orthogonal_Neighborhood {
    struct Part *up;
    struct Part *down;
    struct Part *left;
    struct Part *right;
};

Orthogonal_Neighborhood get_neighbors(int index, struct Part *parts[], int size_of_parts){
        // Existem duas peças ou espaços vizinhos nessa direção?
    for(int j = 0; j < size_of_parts; j++){
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

struct MoveOptions {
    bool right;
    bool left;
    bool up;
    bool down;
};

MoveOptions possibility_of_moving(
    // função mal organizada
    int index,
    struct Part parts[],
    int size_of_parts ,
    struct Part empty_place[],
    int size_of_empty_place)
    {
        MoveOptions possibility = {false, false, false, false};
        
        int x_seleted = parts[index].posX;
        int y_seleted = parts[index].posY;

        int index_right;
        int index_left;
        int index_up;
        int index_down;

        int index_1;
        bool is_right_1 = false;
        bool is_left_1 = false;
        bool is_up_1 = false;
        bool is_down_1 = false;

        int index_2;
        bool is_right_2 = false;
        bool is_left_2 = false;
        bool is_up_2 = false;
        bool is_down_2 = false;

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

        if (is_right_1 && is_right_2){
            if(empty_place[index_right].state){
                possibility.right = true;
            }
            
        }
        if (is_left_1 && is_left_2){
            if(empty_place[index_left].state){
                possibility.left = true;
            }
        }
        if (is_up_1 && is_up_2){
            if(empty_place[index_up].state){
                possibility.up = true;
            }
        }
        if (is_down_1 && is_down_2){
            if(empty_place[index_down].state){
                possibility.down = true;
            }
        }
    return possibility;
    }
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const Vector2 screenSize =  {800, 800};

    int R = 40;
    int spacing = 95;
    int fontSize = 30;


    InitWindow(screenSize.x, screenSize.y, "Resta Um");

    parts_generator(parts, 32, true);
    parts_generator(empty_place, 33, true, true);
    parts_print_cosole(parts, 32);
    parts_print_cosole(empty_place, 33);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        Vector2 MousePos;
        MousePos.x = GetMouseX();   
        MousePos.y = GetMouseY(); 
        selection Selection;
        Selection = get_selected(MousePos,R,spacing,screenSize, parts, 32);
        MoveOptions Options = possibility_of_moving(Selection.index,parts,32,empty_place,33);
        if (Selection.state == true) {
            printf (" %d , %d , up: %d, down: %d, left: %d, right: %d \n" ,
                Selection.Xcartesian ,
                Selection.Ycartesian , 
                Options.up,Options.down,Options.left,Options.right);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            char* title = " - - - Resta Um - - -";
            int text_width = MeasureText(title, fontSize);
            DrawText(
                title,
                translate_cartesian_to_screen(0,screenSize.x)  - (text_width/2),
                10,
                fontSize, LIGHTGRAY);
            if (Selection.state == true) {
                DrawCircle(
                    Selection.X,
                    Selection.Y,
                     R+5, RED);
            }

            for(int i = 0; i < 33; i++){
                int x = scaled_to_screen(empty_place[i].posX,screenSize.x,spacing);
                int y = scaled_to_screen(empty_place[i].posY,screenSize.y,spacing);
                DrawCircle(x, y, R, LIGHTGRAY);

            }
            
            for(int i = 0; i < 32;i++){
                int x = scaled_to_screen(parts[i].posX,screenSize.x,spacing);
                int y = scaled_to_screen(parts[i].posY,screenSize.y,spacing);
                int state = parts[i].state;
                if (state == true) {
                    DrawCircle(x, y, R, PURPLE);
                }

            }



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
