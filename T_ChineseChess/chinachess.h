#ifndef CHINACHESS_H
#define CHINACHESS_H

#include <QPainter>

enum Player {
    RED_PLAYER,
    BLACK_PLAYER
};

enum ChessPiece {
    SOLDIER,
    CANNON,
    CAR,
    HORSE,
    ELEPHANT,
    GUARD,
    GENERAL
};

struct Chess {
    int id = 0;
    int row = 0;//横坐标
    int col = 0;//纵坐标
    Player player = RED_PLAYER;
    ChessPiece chessPiece = SOLDIER;
    bool is_died = false;
};

class ChinaChess
{
public:
    Chess chesses[32] = {
            {1,  7,  1, RED_PLAYER,   SOLDIER},
            {2,  7,  3, RED_PLAYER,   SOLDIER},
            {3,  7,  5, RED_PLAYER,   SOLDIER},
            {4,  7,  7, RED_PLAYER,   SOLDIER},
            {5,  7,  9, RED_PLAYER,   SOLDIER},
            {6,  4,  1, BLACK_PLAYER, SOLDIER},
            {7,  4,  3, BLACK_PLAYER, SOLDIER},
            {8,  4,  5, BLACK_PLAYER, SOLDIER},
            {9,  4,  7, BLACK_PLAYER, SOLDIER},
            {10, 4,  9, BLACK_PLAYER, SOLDIER},
            {11, 8,  2, RED_PLAYER,   CANNON},
            {12, 8,  8, RED_PLAYER,   CANNON},
            {13, 3,  2, BLACK_PLAYER, CANNON},
            {14, 3,  8, BLACK_PLAYER, CANNON},
            {15, 10, 1, RED_PLAYER,   CAR},
            {16, 10, 9, RED_PLAYER,   CAR},
            {17, 1,  1, BLACK_PLAYER, CAR},
            {18, 1,  9, BLACK_PLAYER, CAR},
            {19, 10, 2, RED_PLAYER,   HORSE},
            {20, 10, 8, RED_PLAYER,   HORSE},
            {21, 1,  2, BLACK_PLAYER, HORSE},
            {22, 1,  8, BLACK_PLAYER, HORSE},
            {23, 10, 3, RED_PLAYER,   ELEPHANT},
            {24, 10, 7, RED_PLAYER,   ELEPHANT},
            {25, 1,  3, BLACK_PLAYER, ELEPHANT},
            {26, 1,  7, BLACK_PLAYER, ELEPHANT},
            {27, 10, 4, RED_PLAYER,   GUARD},
            {28, 10, 6, RED_PLAYER,   GUARD},
            {29, 1,  4, BLACK_PLAYER, GUARD},
            {30, 1,  6, BLACK_PLAYER, GUARD},
            {31, 10, 5, RED_PLAYER,   GENERAL},
            {32, 1,  5, BLACK_PLAYER, GENERAL}
    };

};

#endif // CHINACHESS_H
