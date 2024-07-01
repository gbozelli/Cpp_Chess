#include "piece.hpp"

class Knight: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    Knight(int x, int y);
};