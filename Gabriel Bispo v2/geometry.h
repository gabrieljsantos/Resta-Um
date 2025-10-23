#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "raylib.h"
#include "structs.h"

// Função para verificar se um ponto está dentro de uma área
bool checks_if_the_mouse_is_in_an_area(Vector2 cp, Rectangle sri);

// Expande um retângulo adicionando borda
Rectangle ExpandRectangle(Rectangle original, int border_size);

#endif
