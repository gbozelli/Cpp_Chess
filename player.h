#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "piece.h"

struct Player {
    std::string name;
    Color color;
    std::vector<Piece> pieces;

    Player();
    Player(const std::string& name, Color color);
    void print_pieces();
};

#endif