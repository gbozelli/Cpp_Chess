#include <pawn.hpp>

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