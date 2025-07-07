#include "../include/pawn.hpp"
#include "../include/board.hpp"

bool Pawn::isValidMove(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int forwardDir = isWhite ? 1 : -1; // Peças brancas movem y+, pretas movem y-

  // Movimento de uma casa para frente
  if (newX == position_x && newY == position_y + forwardDir)
  {
    return board.getPieceAt(newX, newY) == nullptr; // Casa de destino deve estar vazia
  }

  // Movimento inicial de duas casas
  if (!hasMoved && newX == position_x && newY == position_y + 2 * forwardDir)
  {
    // Casas à frente e no destino devem estar vazias
    return board.getPieceAt(newX, position_y + forwardDir) == nullptr &&
           board.getPieceAt(newX, newY) == nullptr;
  }

  // En Passant e promoção são tratados em isValidCapture ou na lógica do jogo principal
  return false;
}

bool Pawn::isValidCapture(int newX, int newY, const Board &board)
{
  if (newX == position_x && newY == position_y)
    return false;

  int forwardDir = isWhite ? 1 : -1;

  // Ataque diagonal
  if (abs(newX - position_x) == 1 && newY == position_y + forwardDir)
  {
    Piece *targetPiece = board.getPieceAt(newX, newY);
    return targetPiece != nullptr && targetPiece->isWhite != this->isWhite; // Deve ser peça inimiga
  }

  // TODO: Implementar En Passant aqui ou na classe Game.
  // En Passant seria um caso especial onde a casa de destino está vazia,
  // mas uma peça inimiga foi capturada na casa adjacente.
  // Requer que a Board saiba o último movimento de duas casas de um peão.

  return false;
}