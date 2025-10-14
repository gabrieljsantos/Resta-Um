

/*******************************************************************************************

********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h> // usar booleanos
#include <vector>
#include <stdbool.h> // imprimir booleano
#include <math.h>


struct Part { // Criando uma estrutura para criar um vetor
    int posX;
    int posY;
    bool state;
};

struct Part parts[32]; // criando um vetor, do tipo struct part, qual foi definido anterioemente.
struct Part empty_place[32];



void parts_generator(struct Part parts[], int size, bool state){
    int index = 0;
    for (int i = -3; i <= 3; i++){
        for(int j = -3; j <= 3; j++){
            if (!(((i == 0) && (j == 0)) || ((abs(i) > 1) && (abs(j) > 1)))){
                if (index == size){
                    return;
                }
                parts[index].posX = i;
                parts[index].posY = j;
                parts[index].state = true;
                index++;
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
    parts_print_cosole(parts, 32);
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

        if (Selection.state == true) {
            printf (" %d , %d \n" ,Selection.Xcartesian ,Selection.Ycartesian);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
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


            for(int i = 0; i < 32;i++){
                int x = scaled_to_screen(parts[i].posX,screenSize.x,spacing);
                int y = scaled_to_screen(parts[i].posY,screenSize.y,spacing);
                int state = parts[i].state;
                if (state == true) {
                    DrawCircle(x, y, R, LIGHTGRAY);
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
