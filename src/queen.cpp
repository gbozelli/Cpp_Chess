#include "../include/queen.hpp"
#include "../include/board.hpp"

// A Rainha combina a lógica da Torre e do Bispo.

bool Queen::isValidMove(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  // Movimento horizontal ou vertical (como Torre)
  if ((newX == position_x && newY != position_y) || (newY == position_y && newX != position_x))
  {
    int stepX = (newX == position_x) ? 0 : (newX > position_x ? 1 : -1);
    int stepY = (newY == position_y) ? 0 : (newY > position_y ? 1 : -1);

    for (int i = 1;; ++i)
    {
      int currentX = position_x + i * stepX;
      int currentY = position_y + i * stepY;

      if (currentX == newX && currentY == newY)
      {
        return board.getPieceAt(newX, newY) == nullptr; // Destino vazio
      }
      if (board.getPieceAt(currentX, currentY) != nullptr)
      {
        return false; // Caminho bloqueado
      }
    }
  }
  // Movimento diagonal (como Bispo)
  else if (dx == dy)
  {
    int stepX = (newX > position_x) ? 1 : -1;
    int stepY = (newY > position_y) ? 1 : -1;

    for (int i = 1; i < dx; ++i)
    {
      if (board.getPieceAt(position_x + i * stepX, position_y + i * stepY) != nullptr)
      {
        return false; // Caminho bloqueado
      }
    }
    return board.getPieceAt(newX, newY) == nullptr; // Destino vazio
  }

  return false;
}

bool Queen::isValidCapture(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  // Ataque horizontal ou vertical (como Torre)
  if ((newX == position_x && newY != position_y) || (newY == position_y && newX != position_x))
  {
    int stepX = (newX == position_x) ? 0 : (newX > position_x ? 1 : -1);
    int stepY = (newY == position_y) ? 0 : (newY > position_y ? 1 : -1);

    for (int i = 1;; ++i)
    {
      int currentX = position_x + i * stepX;
      int currentY = position_y + i * stepY;

      if (currentX == newX && currentY == newY)
      {
        Piece *targetPiece = board.getPieceAt(newX, newY);
        return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Destino tem peça inimiga
      }
      if (board.getPieceAt(currentX, currentY) != nullptr)
      {
        return false; // Caminho bloqueado antes de chegar à peça a ser capturada
      }
    }
  }
  // Ataque diagonal (como Bispo)
  else if (dx == dy)
  {
    int stepX = (newX > position_x) ? 1 : -1;
    int stepY = (newY > position_y) ? 1 : -1;

    for (int i = 1; i < dx; ++i)
    {
      if (board.getPieceAt(position_x + i * stepX, position_y + i * stepY) != nullptr)
      {
        return false; // Caminho bloqueado
      }
    }
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Destino tem peça inimiga
  }

  return false;
}