#include <include\knight.hpp>

bool Knight::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(gameBoard[i][j]==NULL){
        moves.insert(it, i);
        it++;
        moves.insert(it, j);
        it++;
      } 
    }
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool Knight::atkIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(gameBoard[i][j]!=NULL){
        moves.insert(it, i);
        it++;
        moves.insert(it, j);
        it++;
      } 
    }
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      return true;
    } else {
      it++;
    }
  }
  return false;
};

Knight::Knight(int x, int y) {
  this->position_x = x;
  this->position_y = y;
  this->name = 'k';
}