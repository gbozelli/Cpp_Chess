#include "piece.hpp"

class Pawn: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
};