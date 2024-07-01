#include "piece.hpp"

class King: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    King(int x, int y);
};