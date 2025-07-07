#include "../include/knight.hpp"
#include "../include/board.hpp"

bool Knight::isValidMove(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  // Movimento em L: (1,2) ou (2,1)
  if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
  {
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece == nullptr; // Válido se a casa estiver vazia
  }
  return false;
}

bool Knight::isValidCapture(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  if ((dx == 1 && dy == 2) || (dx == 2 && dy == 1))
  {
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Válido se for peça inimiga
  }
  return false;
}