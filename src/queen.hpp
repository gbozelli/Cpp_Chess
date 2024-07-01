#include "piece.hpp"

class Queen: public Piece{
  private:
    int lim_inf_x;
    int lim_inf_y;
    int lim_sup_x;
    int lim_sup_y;
    int lim_sup_r_x;
    int lim_sup_r_y;
    int lim_sup_l_x;
    int lim_sup_l_y;
    int lim_inf_r_x;
    int lim_inf_r_y;
    int lim_inf_l_x;
    int lim_inf_l_y;
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    void lim();
    Queen(int x, int y);
};