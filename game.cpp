#include "game.h"

Game::Game() : p1("celta", WHITE), p2("uno", BLACK), board() {}

void Game::play() {
    board.clear();
    board.place_player(&p1);
    board.place_player(&p2);
    board.print();
}