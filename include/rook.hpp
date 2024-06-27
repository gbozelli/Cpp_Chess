#include "piece.hpp"

class Rook: public Piece{
  private:
    int lim_inf_x;
    int lim_inf_y;
    int lim_sup_x;
    int lim_sup_y;
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    void lim();
    Rook(int x, int y);
};