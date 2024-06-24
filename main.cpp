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

class Pawn: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
};

bool Pawn::movIsValid(int x, int y){
  if(y==this->position_y+1 && 
    gameBoard[this->position_x][this->position_y+1]==NULL){
    return true;
  } else {
    return false;
  }
};

bool Pawn::atkIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i+=2){
    if(gameBoard[i][j]!=NULL){
      moves.insert(it, i);
      it++;
      moves.insert(it, j);
      it++;
    } 
  }
};

void Piece::setPosition(int x, int y, bool (*func)(int, int)){
  if(func(x, y)==true) {
    this->position_x = x;
    this->position_y = y;
  } else {

  }
};

int main(){
  return 0;
}
