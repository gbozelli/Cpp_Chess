#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

class King : public Piece
{
public:
  King(int x, int y, bool white) : Piece(x, y, white ? 'K' : 'k', white) {}
  King() : Piece() {} // Construtor padrão

  bool isValidMove(int newX, int newY, const Board &board) override;
  bool isValidCapture(int newX, int newY, const Board &board) override;

  // Para o Roque
  bool canCastleKingside(const Board &board);
  bool canCastleQueenside(const Board &board);
};

#endif // KING_HPP