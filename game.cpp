#include "game.h"
#include <iostream>

Game::Game() : p1("celta", WHITE), p2("uno", BLACK), board() {}

void Game::round(Player& player, Player& opponent) {
    std::cout << player.name << ", jogue agora\n";
    int ux, uy, tx, ty;
    Piece* chosen = nullptr;

    while (!chosen) {
        std::cout << "Escolha x: ";
        std::cin >> ux;
        std::cout << "Escolha y: ";
        std::cin >> uy;
        int x = 8 - ux;
        int y = uy - 1;
        for (auto& p : player.pieces) {
            if (p.x == x && p.y == y) { chosen = &p; break; }
        }
        if (!chosen) std::cout << "Escolha invalida\n";
    }

    int moves[64][2];
    int count = chosen->valid_moves(&board, moves);
    bool ok = false;

    while (!ok) {
        std::cout << "Mover para x: ";
        std::cin >> tx;
        std::cout << "Mover para y: ";
        std::cin >> ty;
        int x = 8 - tx;
        int y = ty - 1;
        for (int i = 0; i < count; i++) {
            if (moves[i][0] == x && moves[i][1] == y) ok = true;
        }
        if (!ok) std::cout << "Movimento invalido\n";
        else {
            if (board.board[x][y]) {
                for (auto it = opponent.pieces.begin(); it != opponent.pieces.end(); ++it) {
                    if (&(*it) == board.board[x][y]) {
                        opponent.pieces.erase(it);
                        break;
                    }
                }
            }
            chosen->x = x;
            chosen->y = y;
            chosen->moved = true;
        }
    }
}

void Game::play() {
    while (true) {
        board.clear();
        board.place_player(&p1);
        board.place_player(&p2);
        board.print();
        round(p1, p2);
        if (!p2.has_king()) { std::cout << p1.name << " venceu!\n"; break; }

        board.clear();
        board.place_player(&p1);
        board.place_player(&p2);
        board.print();
        round(p2, p1);
        if (!p1.has_king()) { std::cout << p2.name << " venceu!\n"; break; }
    }
}