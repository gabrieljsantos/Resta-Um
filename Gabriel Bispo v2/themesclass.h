#ifndef THEMESCLASS_H_INCLUDED
#define THEMESCLASS_H_INCLUDED

#include "raylib.h"

// Definição da estrutura de cores do tema
struct Theme {
    Color BackgroundColor;
    Color PartColor;
    Color ButtonColor;
    Color BoardColor;
    Color BoardBorderColor;
    Color TimeColor;
    Color ButtonBoardColor; // novo
    Color TextColor;        // novo
};

// Valores diretos em RGBA
Theme white_beige = {
    {245, 245, 220, 255}, // BackgroundColor
    {101, 67, 33, 255},   // PartColor
    {165, 42, 42, 255},   // ButtonColor
    {165, 42, 42, 255},   // BoardColor
    {101, 67, 33, 255},   // BoardBorderColor
    {0, 0, 0, 255},       // TimeColor
    {210, 180, 140, 255}, // ButtonBoardColor
    {0, 0, 0, 255}        // TextColor
};

Theme dark_purple = {
    {0, 0, 0, 255},       // BackgroundColor
    {128, 0, 128, 255},   // PartColor
    {75, 0, 130, 255},    // ButtonColor
    {0, 0, 0, 255},       // BoardColor
    {0, 0, 0, 255},       // BoardBorderColor
    {255, 215, 0, 255},   // TimeColor
    {75, 0, 130, 255},    // ButtonBoardColor
    {255, 255, 255, 255}  // TextColor
};

Theme ocean_blue = {
    {28, 107, 160, 255},  // BackgroundColor
    {0, 191, 255, 255},   // PartColor
    {0, 128, 255, 255},   // ButtonColor
    {0, 105, 148, 255},   // BoardColor
    {0, 82, 117, 255},    // BoardBorderColor
    {255, 255, 255, 255}, // TimeColor
    {0, 128, 255, 255},   // ButtonBoardColor
    {255, 255, 255, 255}  // TextColor
};

Theme forest_green = {
    {34, 139, 34, 255},   // BackgroundColor
    {0, 100, 0, 255},     // PartColor
    {46, 139, 87, 255},   // ButtonColor
    {0, 128, 0, 255},     // BoardColor
    {0, 100, 0, 255},     // BoardBorderColor
    {255, 255, 255, 255}, // TimeColor
    {46, 139, 87, 255},   // ButtonBoardColor
    {255, 255, 255, 255}  // TextColor
};

Theme sunset_orange = {
    {255, 99, 71, 255},   // BackgroundColor
    {255, 140, 0, 255},   // PartColor
    {255, 165, 0, 255},   // ButtonColor
    {255, 127, 80, 255},  // BoardColor
    {255, 99, 71, 255},   // BoardBorderColor
    {0, 0, 0, 255},       // TimeColor
    {255, 165, 0, 255},   // ButtonBoardColor
    {0, 0, 0, 255}        // TextColor
};

#endif
