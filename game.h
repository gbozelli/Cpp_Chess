#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "board.h"

struct Game {
    Player p1;
    Player p2;
    Board board;

    Game();
    void play();
    void round(Player& player, Player& opponent);
};

#endif