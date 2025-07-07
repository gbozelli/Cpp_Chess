#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece
{
public:
  Knight(int x, int y, bool white) : Piece(x, y, white ? 'n' : 'N', white) {} // 'n'/'N' para cavalo
  Knight() : Piece() {}                                                       // Construtor padrão

  bool isValidMove(int newX, int newY, const Board &board) override;
  bool isValidCapture(int newX, int newY, const Board &board) override;
};

#endif // KNIGHT_HPP