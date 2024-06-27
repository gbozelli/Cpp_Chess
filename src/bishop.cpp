#include "include\bishop.hpp"

bool Bishop::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim();
  int delta = this->lim_sup_r_x - this->lim_inf_l_x;
  for(int i = 0; i < delta; i++){
    if(gameBoard[lim_inf_l_x+i][lim_inf_l_y+i]==NULL){
      moves.insert(it, lim_inf_l_x+i);
      it++;
      moves.insert(it, lim_inf_l_y+i);
      it++;
    } 
  }
  int delta = this->lim_sup_l_x - this->lim_inf_r_x;
  for(int i = 0; i < delta; i++){
    if(gameBoard[lim_sup_l_x-i][lim_sup_l_y-i]==NULL){
      moves.insert(it, lim_sup_l_x-i);
      it++;
      moves.insert(it, lim_sup_l_y-i);
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

bool Bishop::atkIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int i = this->position_x;
  int j = this->position_y;
  this->lim();
  moves.insert(it, this->lim_sup_r_x);it++;moves.insert(it, lim_sup_r_y);it++;
  moves.insert(it, this->lim_sup_l_x);it++;moves.insert(it, lim_sup_l_y);it++;
  moves.insert(it, this->lim_inf_r_x);it++;moves.insert(it, lim_inf_r_y);it++;
  moves.insert(it, this->lim_inf_l_x);it++;moves.insert(it, lim_inf_l_y);it++;
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Bishop::lim() {
  for (int i = this->position_x; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[i][j]!=NULL){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[i][j]!=NULL){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_y; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[j][i]!=NULL){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[j][i]!=NULL){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
}

Bishop::Bishop(int x, int y) {
  this->position_x = x;
  this->position_y = y;
  this->name = 'b';
}