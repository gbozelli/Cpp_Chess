#include "../include/bishop.hpp"
#include "../include/board.hpp" // Para acessar métodos da Board, como getPieceAt

bool Bishop::isValidMove(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false; // Não pode mover para a mesma posição

  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  if (dx != dy)
    return false; // Bispo só move na diagonal

  int stepX = (newX > position_x) ? 1 : -1;
  int stepY = (newY > position_y) ? 1 : -1;

  // Verificar caminho livre
  for (int i = 1; i < dx; ++i)
  {
    if (board.getPieceAt(position_x + i * stepX, position_y + i * stepY) != nullptr)
    {
      return false; // Caminho bloqueado
    }
  }

  // Verificar se a casa de destino está vazia ou ocupada por peça amiga
  Piece *targetPiece = board.getPieceAt(newX, newY);
  if (targetPiece == nullptr)
  {
    return true; // Casa vazia, movimento válido
  }
  else
  {
    // Se for para uma casa ocupada, deve ser uma captura (tratado em isValidCapture)
    return false;
  }
}

bool Bishop::isValidCapture(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  if (dx != dy)
    return false; // Bispo só ataca na diagonal

  int stepX = (newX > position_x) ? 1 : -1;
  int stepY = (newY > position_y) ? 1 : -1;

  // Verificar caminho livre até o destino (excluindo o destino em si)
  for (int i = 1; i < dx; ++i)
  {
    if (board.getPieceAt(position_x + i * stepX, position_y + i * stepY) != nullptr)
    {
      return false; // Caminho bloqueado
    }
  }

  // Verificar se a casa de destino tem uma peça inimiga
  Piece *targetPiece = board.getPieceAt(newX, newY);
  if (targetPiece != nullptr && targetPiece->isWhite != this->isWhite)
  {
    return true; // Peça inimiga encontrada, captura válida
  }
  return false;
}