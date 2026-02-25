#include "board.h"
#include "player.h"
#include <iostream>

Board::Board() {
    clear();
}

void Board::clear() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = nullptr;
}

void Board::place_player(Player* p) {
    for (auto& piece : p->pieces)
        board[piece.x][piece.y] = &piece;
}

void Board::print() {
    std::cout << "    1  2  3  4  5  6  7  8\n";
    std::cout << "   ------------------------\n";
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << " |";
        for (int j = 0; j < 8; j++) {
            if (!board[i][j]) std::cout << " . ";
            else std::cout << " " << board[i][j]->symbol << " ";
        }
        std::cout << "| " << 8 - i << "\n";
    }
    std::cout << "   ------------------------\n";
    std::cout << "    1  2  3  4  5  6  7  8\n";
}

bool Board::empty(int x, int y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return false;
    return board[x][y] == nullptr;
}

bool Board::enemy(int x, int y, Color color) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return false;
    if (!board[x][y]) return false;
    return board[x][y]->color != color;
}