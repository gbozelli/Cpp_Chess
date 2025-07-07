#pragma once

#include<iostream>
#include <list>

using namespace std;

class Piece {
  public:
    int position_x;
    int position_y;
    char name;

    void setPosition(int x, int y, bool (*func)(int, int));
    void setName(string s);
};

char gameBoard[8][8];