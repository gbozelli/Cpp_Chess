#include "player.h"
#include <iostream>

Player::Player() : name(""), color(WHITE) {}

Player::Player(const std::string& name, Color color) : name(name), color(color) {
    int row_pawns = color == WHITE ? 6 : 1;
    int row_back  = color == WHITE ? 7 : 0;

    for (int i = 0; i < 8; i++)
        pieces.emplace_back(PAWN, row_pawns, i, color);

    pieces.emplace_back(ROOK, row_back, 0, color);
    pieces.emplace_back(KNIGHT, row_back, 1, color);
    pieces.emplace_back(BISHOP, row_back, 2, color);
    pieces.emplace_back(QUEEN, row_back, 3, color);
    pieces.emplace_back(KING, row_back, 4, color);
    pieces.emplace_back(BISHOP, row_back, 5, color);
    pieces.emplace_back(KNIGHT, row_back, 6, color);
    pieces.emplace_back(ROOK, row_back, 7, color);
}

void Player::print_pieces() {
    std::cout << "Peças de " << name << ": ";
    for (auto& p : pieces) std::cout << p.symbol << " ";
    std::cout << "\n";
}

bool Player::has_king() {
    for (auto& p : pieces) if (p.type == KING) return true;
    return false;
}