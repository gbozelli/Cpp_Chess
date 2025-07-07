#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
// Não precisamos mais de tantos limites privados aqui,
// a lógica de verificação de caminho livre será na Board.

class Bishop : public Piece
{
public:
  Bishop(int x, int y, bool white) : Piece(x, y, white ? 'b' : 'B', white) {}
  Bishop() : Piece() {} // Construtor padrão

  bool isValidMove(int newX, int newY, const Board &board) override;
  bool isValidCapture(int newX, int newY, const Board &board) override;
};

#endif // BISHOP_HPP