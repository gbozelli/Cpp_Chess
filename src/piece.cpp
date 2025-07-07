#include "../include/piece.hpp"

// Não precisamos mais do ponteiro para função aqui,
// já que a validação agora é feita nos métodos virtuais das peças.
void Piece::setPosition(int x, int y)
{
  this->position_x = x;
  this->position_y = y;
  this->hasMoved = true; // Marca que a peça se moveu
}