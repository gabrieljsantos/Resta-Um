#include "geometry.h"

bool checks_if_the_mouse_is_in_an_area(Vector2 cp, Rectangle sri) {
    // cp = comparison_position
    // sri = square_region_interval
    if ((cp.x >= sri.x && cp.x <= sri.x + sri.width) &&
        (cp.y >= sri.y && cp.y <= sri.y + sri.height)) {
        return true; // dentro da área
    }
    return false;
}


Rectangle ExpandRectangle(Rectangle original, int border_size) {
    Rectangle expanded;
    expanded.x = original.x - border_size;
    expanded.y = original.y - border_size;
    expanded.width  = original.width + border_size * 2;
    expanded.height = original.height + border_size * 2;
    return expanded;
}