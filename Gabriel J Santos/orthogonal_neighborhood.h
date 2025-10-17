#ifndef ORTHOGONAL_NEIGHBORHOOD_H
#define ORTHOGONAL_NEIGHBORHOOD_H

#define DIR_COUNT 4 // quantidade das direçõs
#define DEPTH_COUNT 2 // profundidade de verificação

// definições de vizinhos
typedef enum {
    NEIGHBOR_NONE, // Não existe
    NEIGHBOR_EMPTY, // espaço vazio
    NEIGHBOR_OCCUPIED, // ocupado
    NEIGHBOR_EDIBLE // peça que pode ser consumida por outra
} NeighborType;

//
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

struct Neighbor {
    NeighborType type;
    Direction direction;
    int index;  // índice da peça ou posição
};

struct Orthogonal_Neighborhood {
    struct Neighbor up[DEPTH_COUNT];
    struct Neighbor down[DEPTH_COUNT];
    struct Neighbor left[DEPTH_COUNT];
    struct Neighbor right[DEPTH_COUNT];
};

#endif // ORTHOGONAL_NEIGHBORHOOD_H