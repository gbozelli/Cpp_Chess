#ifndef PIECE_H
#define PIECE_H
#include <string>

enum Color { WHITE, BLACK };
enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

struct Board;

struct Piece {
    int x, y;
    Color color;
    PieceType type;
    bool moved;
    std::string symbol;

    Piece();
    Piece(PieceType type, int x, int y, Color color);
    int valid_moves(Board* board, int moves[64][2]);
};

#endif