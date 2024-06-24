#pragma once

#include<iostream>
#include <list>

using namespace std;

int gameBoard[8][8] = {};

class Piece {
  public:
    int position_x;
    int position_y;
    void setPosition(int x, int y, bool (*func)(int, int));
};