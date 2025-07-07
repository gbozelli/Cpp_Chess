#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece
{
public:
  Rook(int x, int y, bool white) : Piece(x, y, white ? 'r' : 'R', white) {}
  Rook() : Piece() {} // Construtor padrão

  bool isValidMove(int newX, int newY, const Board &board) override;
  bool isValidCapture(int newX, int newY, const Board &board) override;
};

#endif // ROOK_HPP