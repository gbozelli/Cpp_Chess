#include "piece.h"
#include "board.h"

Piece::Piece() : x(0), y(0), color(WHITE), type(PAWN), moved(false), symbol("♙") {}

Piece::Piece(PieceType t, int x, int y, Color c) : x(x), y(y), color(c), type(t), moved(false) {
    if (t == PAWN) symbol = c == WHITE ? "♙" : "♟";
    if (t == ROOK) symbol = c == WHITE ? "♖" : "♜";
    if (t == KNIGHT) symbol = c == WHITE ? "♘" : "♞";
    if (t == BISHOP) symbol = c == WHITE ? "♗" : "♝";
    if (t == QUEEN) symbol = c == WHITE ? "♕" : "♛";
    if (t == KING) symbol = c == WHITE ? "♔" : "♚";
}

int Piece::valid_moves(Board* board, int moves[64][2]) {
    int count = 0;
    if (type == PAWN) {
        int dir = color == WHITE ? -1 : 1;
        int nx = x + dir;
        if (board->empty(nx, y)) {
            moves[count][0] = nx; moves[count++][1] = y;
            if (!moved && board->empty(x + 2 * dir, y)) {
                moves[count][0] = x + 2 * dir; moves[count++][1] = y;
            }
        }
        if (board->enemy(x + dir, y - 1, color)) {
            moves[count][0] = x + dir; moves[count++][1] = y - 1;
        }
        if (board->enemy(x + dir, y + 1, color)) {
            moves[count][0] = x + dir; moves[count++][1] = y + 1;
        }
    }
    return count;
}