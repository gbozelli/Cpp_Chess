#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece
{
public:
  Pawn(int x, int y, bool white) : Piece(x, y, white ? 'p' : 'P', white) {}
  Pawn() : Piece() {} // Construtor padrão

  bool isValidMove(int newX, int newY, const Board &board) override;
  bool isValidCapture(int newX, int newY, const Board &board) override;

  // Para En Passant (a board precisaria rastrear o último movimento)
  // bool canEnPassant(int newX, int newY, const Board& board); // Mais complexo, talvez adiar
};

#endif // PAWN_HPP