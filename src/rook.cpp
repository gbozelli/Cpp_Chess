#include "include\rook.hpp"

bool Rook::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim();
  int j = this->position_y+1;
  for(int i = this->lim_inf_x+1; i <= this->lim_sup_x-1; i++){
    if(gameBoard[i][this->position_y]==NULL){
      moves.insert(it, i);
      it++;
      moves.insert(it, this->position_y);
      it++;
    }
  }
  for(int i = this->lim_inf_y+1; i <= this->lim_sup_y-1; i++){
    if(gameBoard[this->position_x][i]==NULL){
      moves.insert(it, this->position_x);
      it++;
      moves.insert(it, i);
      it++;
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

bool Rook::atkIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int i = this->position_x;
  int j = this->position_y;
  this->lim();
  moves.insert(it, this->lim_sup_x);it++;moves.insert(it, j);it++;
  moves.insert(it, this->lim_inf_x);it++;moves.insert(it, j);it++;
  moves.insert(it, i);it++;moves.insert(it, this->lim_sup_y);it++;
  moves.insert(it, i);it++;moves.insert(it, this->lim_inf_y);it++;
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Rook::lim() {
  for (int i = this->position_x; i < 7; i++){
    if(gameBoard[i][this->position_y]!=NULL){
      this->lim_sup_x = i;
      break;
    }
  }
   for (int i = this->position_x; i > 0; i--){
    if(gameBoard[i][this->position_y]!=NULL){
      this->lim_inf_x = i;
      break;
    }
  }
   for (int i = this->position_y; i < 7; i++){
    if(gameBoard[this->position_x][i]!=NULL){
      this->lim_sup_y = i;
      break;
    }
  }
   for (int i = this->position_y; i > 0; i--){
    if(gameBoard[this->position_x][i]!=NULL){
      this->lim_inf_y = i;
      break;
    }
  }
}

Rook::Rook(int x, int y) {
  this->position_x = x;
  this->position_y = y;
  this->name = 'r';
}