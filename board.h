#ifndef BOARD_H
#define BOARD_H
#include "piece.h"

struct Player;

struct Board {
    Piece* board[8][8];
    Board();
    void clear();
    void place_player(Player* p);
    void print();
    bool empty(int x, int y);
    bool enemy(int x, int y, Color color);
};

#endif