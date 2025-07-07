#include "../include/king.hpp"
#include "../include/board.hpp"
#include "../include/rook.hpp" // Para verificar a torre no roque

bool King::isValidMove(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  // Rei move uma casa em qualquer direção
  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  if (dx <= 1 && dy <= 1)
  {
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece == nullptr; // Válido se a casa estiver vazia
  }
  return false;
}

bool King::isValidCapture(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  // Rei captura uma casa em qualquer direção
  int dx = abs(newX - position_x);
  int dy = abs(newY - position_y);

  if (dx <= 1 && dy <= 1)
  {
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Válido se for peça inimiga
  }
  return false;
}

// Lógica para Roque (Kingside - lado do rei)
bool King::canCastleKingside(const Board &board)
{
  if (hasMoved || board.isKingInCheck(isWhite))
    return false; // Rei já se moveu ou está em xeque

  int row = isWhite ? 0 : 7; // Linha do rei (0 para brancas, 7 para pretas)
  // Coordenadas esperadas do rei e da torre para o roque kingside
  int kingStartX = 4;
  int rookStartX = 7;
  int kingPassX1 = 5;
  int kingPassX2 = 6;

  // Verifica se as peças estão nas posições iniciais corretas
  if (position_x != kingStartX || position_y != row)
    return false; // Rei não está na posição inicial
  Piece *rook = board.getPieceAt(rookStartX, row);
  if (rook == nullptr || rook->name != (isWhite ? 'r' : 'R') || rook->hasMoved)
    return false; // Não é torre ou já moveu

  // Verifica se as casas entre o rei e a torre estão vazias
  if (board.getPieceAt(kingPassX1, row) != nullptr || board.getPieceAt(kingPassX2, row) != nullptr)
    return false;

  // Verifica se o rei passa ou termina em xeque (as casas kingPassX1 e kingPassX2 não podem ser atacadas)
  if (board.isSquareAttacked(kingPassX1, row, !isWhite) || board.isSquareAttacked(kingPassX2, row, !isWhite))
    return false;

  return true;
}

// Lógica para Roque (Queenside - lado da rainha)
bool King::canCastleQueenside(const Board &board)
{
  if (hasMoved || board.isKingInCheck(isWhite))
    return false;

  int row = isWhite ? 0 : 7;
  int kingStartX = 4;
  int rookStartX = 0;
  int kingPassX1 = 3;
  int kingPassX2 = 2;
  int rookPassX = 1; // Casa entre a torre e o rei, que também deve estar vazia

  if (position_x != kingStartX || position_y != row)
    return false;
  Piece *rook = board.getPieceAt(rookStartX, row);
  if (rook == nullptr || rook->name != (isWhite ? 'r' : 'R') || rook->hasMoved)
    return false;

  if (board.getPieceAt(kingPassX1, row) != nullptr || board.getPieceAt(kingPassX2, row) != nullptr || board.getPieceAt(rookPassX, row) != nullptr)
    return false;

  if (board.isSquareAttacked(kingPassX1, row, !isWhite) || board.isSquareAttacked(kingPassX2, row, !isWhite))
    return false;

  return true;
}