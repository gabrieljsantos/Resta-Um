#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

struct VectorXY {
    int x;
    int y;
};

// Definição da estrutura de cores do tema
struct Theme {
    int BackgroundColor;
    int PieceColor;
    int ButtonColor;
    int BoardColor;
    int BoardBorderColor;
    int TimeColor;
};

#endif