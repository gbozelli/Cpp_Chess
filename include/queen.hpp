#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"

class Queen : public Piece
{
public:
  Queen(int x, int y, bool white) : Piece(x, y, white ? 'q' : 'Q', white) {}
  Queen() : Piece() {} // Construtor padrão

  bool isValidMove(int newX, int newY, const Board &board) override;
  bool isValidCapture(int newX, int newY, const Board &board) override;
};

#endif // QUEEN_HPP