#include "../include/rook.hpp"
#include "../include/board.hpp"

bool Rook::isValidMove(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  // Movimento horizontal ou vertical
  if (newX == position_x && newY != position_y)
  { // Vertical
    int stepY = (newY > position_y) ? 1 : -1;
    for (int i = position_y + stepY; i != newY; i += stepY)
    {
      if (board.getPieceAt(position_x, i) != nullptr)
      {
        return false; // Caminho bloqueado
      }
    }
    return board.getPieceAt(newX, newY) == nullptr; // Destino vazio
  }
  else if (newY == position_y && newX != position_x)
  { // Horizontal
    int stepX = (newX > position_x) ? 1 : -1;
    for (int i = position_x + stepX; i != newX; i += stepX)
    {
      if (board.getPieceAt(i, position_y) != nullptr)
      {
        return false; // Caminho bloqueado
      }
    }
    return board.getPieceAt(newX, newY) == nullptr; // Destino vazio
  }
  return false; // Nem horizontal nem vertical
}

bool Rook::isValidCapture(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  // Ataque horizontal ou vertical
  if (newX == position_x && newY != position_y)
  { // Vertical
    int stepY = (newY > position_y) ? 1 : -1;
    for (int i = position_y + stepY; i != newY; i += stepY)
    {
      if (board.getPieceAt(position_x, i) != nullptr)
      {
        return false; // Caminho bloqueado antes de chegar à peça a ser capturada
      }
    }
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Destino tem peça inimiga
  }
  else if (newY == position_y && newX != position_x)
  { // Horizontal
    int stepX = (newX > position_x) ? 1 : -1;
    for (int i = position_x + stepX; i != newX; i += stepX)
    {
      if (board.getPieceAt(i, position_y) != nullptr)
      {
        return false; // Caminho bloqueado
      }
    }
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Destino tem peça inimiga
  }
  return false;
}