#include "include\piece.hpp"

void Piece::setPosition(int x, int y, bool (*func)(int, int)){
  if(func(x, y)==true) {
    this->position_x = x;
    this->position_y = y;
  } else {

  }
};
