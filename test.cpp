#include<iostream>
#include <list>
#include <array>
#include <vector>

using namespace std;

class Piece {
  public:
    int position_x;
    int position_y;
    int type;

    void setPosition(int x, int y, bool (*func)(int, int));
};

class Rook: public Piece{
  private:
    int lim_inf_x;
    int lim_inf_y;
    int lim_sup_x;
    int lim_sup_y;
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board);
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board);
    void lim(vector<vector<Piece*>> board);
    Rook(int x, int y, int type);
};

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
    bool movIsValid(int x, int y, vector<vector<Piece*>> board);
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board);
    void lim(vector<vector<Piece*>> board);
    Queen(int x, int y, int type);
};

class Pawn: public Piece{
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board);
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board);
    Pawn(int x, int y, int type);
};

class Knight: public Piece{
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board);
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board);
    Knight(int x, int y, int type);
};

class King: public Piece{
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board);
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board);
    King(int x, int y, int type);
};

class Bishop: public Piece{
  private:
    int lim_sup_r_x;
    int lim_sup_r_y;
    int lim_sup_l_x;
    int lim_sup_l_y;
    int lim_inf_r_x;
    int lim_inf_r_y;
    int lim_inf_l_x;
    int lim_inf_l_y;

  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board);
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board);
    void lim(vector<vector<Piece*>> board);
    Bishop(int x, int y, int type);
};

class Board {
    vector<vector<Piece*>> board; // Tablero de juego

public:
    // Constructor
    Board();
};

Board::Board() {
    // Inicializar el tablero con un tamaño estándar de 8x8
    board.resize(8, vector<Piece*>(8, nullptr));

    // Inicializar las piezas blancas
    board[0][0] = new Rook(0,0,0);
    board[0][1] = new Knight(0,1,0);
    board[0][2] = new Bishop(0,2,0);
    board[0][3] = new Queen(0,3,0);
    board[0][4] = new King(0,4,0);
    board[0][5] = new Bishop(0,5,0);
    board[0][6] = new Knight(0,6,0);
    board[0][7] = new Rook(0,7,0);
    for (int col = 0; col < 8; col++) {
        board[1][col] = new Pawn(1,col,0);
    }

    // Inicializar las piezas negras
    board[7][0] = new Rook(7,0,1);
    board[7][1] = new Knight(7,1,1);
    board[7][2] = new Bishop(7,2,1);
    board[7][3] = new Queen(7,3,1);
    board[7][4] = new King(7,4,1);
    board[7][5] = new Bishop(7,5,1);
    board[7][6] = new Knight(7,6,1);
    board[7][7] = new Rook(7,7,1);

    for (int col = 0; col < 8; col++) {
        board[6][col] = new Pawn(6,col,1);
    }

}

bool Bishop::movIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim(board);
  int delta = this->lim_sup_r_x - this->lim_inf_l_x;
  for(int i = 0; i < delta; i++){
    if(board[lim_inf_l_x+i][lim_inf_l_y+i]==NULL){
      moves.insert(it, lim_inf_l_x+i);
      it++;
      moves.insert(it, lim_inf_l_y+i);
      it++;
    } 
  }
  delta = this->lim_sup_l_x - this->lim_inf_r_x;
  for(int i = 0; i < delta; i++){
    if(board[lim_sup_l_x-i][lim_sup_l_y-i]==NULL){
      moves.insert(it, lim_sup_l_x-i);
      it++;
      moves.insert(it, lim_sup_l_y-i);
      it++;
    } 
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool Bishop::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int i = this->position_x;
  int j = this->position_y;
  this->lim(board);
  moves.insert(it, this->lim_sup_r_x);it++;moves.insert(it, lim_sup_r_y);it++;
  moves.insert(it, this->lim_sup_l_x);it++;moves.insert(it, lim_sup_l_y);it++;
  moves.insert(it, this->lim_inf_r_x);it++;moves.insert(it, lim_inf_r_y);it++;
  moves.insert(it, this->lim_inf_l_x);it++;moves.insert(it, lim_inf_l_y);it++;
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Bishop::lim(vector<vector<Piece*>> board) {
  for (int i = this->position_x; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(board[i][j]!=NULL){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(board[i][j]!=NULL){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_y; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(board[j][i]!=NULL){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(board[j][i]!=NULL){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
}

Bishop::Bishop(int x, int y, int type) {
  this->position_x = x;
  this->position_y = y;
  this->type = type;
  ;
}

bool King::movIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(board[i][j]==NULL){
        moves.insert(it, i);
        it++;
        moves.insert(it, j);
        it++;
      } 
    }
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool King::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(board[i][j]!=NULL){
        moves.insert(it, i);
        it++;
        moves.insert(it, j);
        it++;
      } 
    }
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

King::King(int x, int y, int type) {
  this->position_x = x;
  this->position_y = y;
  this->type = type;
  ;
}

bool Knight::movIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(board[i][j]==NULL){
        moves.insert(it, i);
        it++;
        moves.insert(it, j);
        it++;
      } 
    }
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool Knight::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(board[i][j]!=NULL){
        moves.insert(it, i);
        it++;
        moves.insert(it, j);
        it++;
      } 
    }
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

Knight::Knight(int x, int y, int type) {
  this->position_x = x;
  this->position_y = y;
  this->type = type;
  ;
}

bool Pawn::movIsValid(int x, int y, vector<vector<Piece*>> board){
  if(y==this->position_y+1 && 
    board[this->position_x][this->position_y+1]==NULL){
    this->position_x = x;
    this->position_y = y;
    
    return true;
  } else {
    return false;
  }
};

bool Pawn::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i+=2){
    if(board[i][j]!=NULL){
      moves.insert(it, i);
      it++;
      moves.insert(it, j);
      it++;
    } 
  }
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

Pawn::Pawn(int x, int y, int type) {
  this->position_x = x;
  this->position_y = y;
  this->type = type;
  ;
}

void Piece::setPosition(int x, int y, bool (*func)(int, int)){
  if(func(x, y)==true) {
    this->position_x = x;
    this->position_y = y;
  } else {

  }
};

bool Queen::movIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim(board);
  int delta = this->lim_sup_r_x - this->lim_inf_l_x;
  for(int i = 0; i < delta; i++){
    if(board[lim_inf_l_x+i][lim_inf_l_y+i]==NULL){
      moves.insert(it, lim_inf_l_x+i);
      it++;
      moves.insert(it, lim_inf_l_y+i);
      it++;
    } 
  }
  delta = this->lim_sup_l_x - this->lim_inf_r_x;
  for(int i = 0; i < delta; i++){
    if(board[lim_sup_l_x-i][lim_sup_l_y-i]==NULL){
      moves.insert(it, lim_sup_l_x-i);
      it++;
      moves.insert(it, lim_sup_l_y-i);
      it++;
    } 
  }

  int j = this->position_y+1;
  for(int i = this->lim_inf_x+1; i <= this->lim_sup_x-1; i++){
    if(board[i][this->position_y]==NULL){
      moves.insert(it, i);
      it++;
      moves.insert(it, this->position_y);
      it++;
    }
  }
  for(int i = this->lim_inf_y+1; i <= this->lim_sup_y-1; i++){
    if(board[this->position_x][i]==NULL){
      moves.insert(it, this->position_x);
      it++;
      moves.insert(it, i);
      it++;
    }
  }


  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool Queen::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int i = this->position_x;
  int j = this->position_y;
  this->lim(board);
  this->lim(board);
  moves.insert(it, this->lim_sup_x);it++;moves.insert(it, j);it++;
  moves.insert(it, this->lim_inf_x);it++;moves.insert(it, j);it++;
  moves.insert(it, i);it++;moves.insert(it, this->lim_sup_y);it++;
  moves.insert(it, i);it++;moves.insert(it, this->lim_inf_y);it++;
  moves.insert(it, this->lim_sup_r_x);it++;moves.insert(it, lim_sup_r_y);it++;
  moves.insert(it, this->lim_sup_l_x);it++;moves.insert(it, lim_sup_l_y);it++;
  moves.insert(it, this->lim_inf_r_x);it++;moves.insert(it, lim_inf_r_y);it++;
  moves.insert(it, this->lim_inf_l_x);it++;moves.insert(it, lim_inf_l_y);it++;
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Queen::lim(vector<vector<Piece*>> board) {
  for (int i = this->position_x; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(board[i][j]!=NULL){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(board[i][j]!=NULL){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_y; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(board[j][i]!=NULL){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(board[j][i]!=NULL){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i < 7; i++){
    if(board[i][this->position_y]!=NULL){
      this->lim_sup_x = i;
      break;
    }
  }
   for (int i = this->position_x; i > 0; i--){
    if(board[i][this->position_y]!=NULL){
      this->lim_inf_x = i;
      break;
    }
  }
   for (int i = this->position_y; i < 7; i++){
    if(board[this->position_x][i]!=NULL){
      this->lim_sup_y = i;
      break;
    }
  }
   for (int i = this->position_y; i > 0; i--){
    if(board[this->position_x][i]!=NULL){
      this->lim_inf_y = i;
      break;
    }
  }
}

Queen::Queen(int x, int y, int type) {
  this->position_x = x;
  this->position_y = y;
  this->type = type;
  ;
}

bool Rook::movIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim(board);
  int j = this->position_y+1;
  for(int i = this->lim_inf_x+1; i <= this->lim_sup_x-1; i++){
    if(board[i][this->position_y]==NULL){
      moves.insert(it, i);
      it++;
      moves.insert(it, this->position_y);
      it++;
    }
  }
  for(int i = this->lim_inf_y+1; i <= this->lim_sup_y-1; i++){
    if(board[this->position_x][i]==NULL){
      moves.insert(it, this->position_x);
      it++;
      moves.insert(it, i);
      it++;
    }
  }

  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if(x==*it && y==*(it++)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool Rook::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int i = this->position_x;
  int j = this->position_y;
  this->lim(board);
  moves.insert(it, this->lim_sup_x);it++;moves.insert(it, j);it++;
  moves.insert(it, this->lim_inf_x);it++;moves.insert(it, j);it++;
  moves.insert(it, i);it++;moves.insert(it, this->lim_sup_y);it++;
  moves.insert(it, i);it++;moves.insert(it, this->lim_inf_y);it++;
  for (list<int>::iterator it=moves.begin(); it != moves.end(); it++){
    if((x==*it && y==*(it++))&&(x!=this->position_x && y!=this->position_y)){
      this->position_x = x;
      this->position_y = y;
      
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Rook::lim(vector<vector<Piece*>> board) {
  for (int i = this->position_x; i < 7; i++){
    if(board[i][this->position_y]!=NULL){
      this->lim_sup_x = i;
      break;
    }
  }
   for (int i = this->position_x; i > 0; i--){
    if(board[i][this->position_y]!=NULL){
      this->lim_inf_x = i;
      break;
    }
  }
   for (int i = this->position_y; i < 7; i++){
    if(board[this->position_x][i]!=NULL){
      this->lim_sup_y = i;
      break;
    }
  }
   for (int i = this->position_y; i > 0; i--){
    if(board[this->position_x][i]!=NULL){
      this->lim_inf_y = i;
      break;
    }
  }
}

Rook::Rook(int x, int y, int type) {
  this->position_x = x;
  this->position_y = y;
  this->type = type;
  ;
}

void printboard(vector<vector<Piece*>> board){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      cout << board[i][j];
    }
    cout << endl;
  }
}

class Player{
  int type;
  public:
  Player(int type);
};

Player::Player(int type) {
  this->type = type; 
};

int main(){
  bool checkMate = false;
  Board b = Board();
  Player p1 = Player(0);
  Player p2 = Player(1);
  while(checkMate==false){
    
  }
  return 0;
}
