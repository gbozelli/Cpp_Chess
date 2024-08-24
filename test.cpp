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
    virtual bool movIsValid(int x, int y, vector<vector<Piece*>> board) = 0;
    virtual bool atkIsValid(int x, int y, vector<vector<Piece*>> board) = 0;
};

class Rook: public Piece{
  private:
    int lim_inf_x;
    int lim_inf_y;
    int lim_sup_x;
    int lim_sup_y;
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board) override;
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board) override;
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
    bool movIsValid(int x, int y, vector<vector<Piece*>> board) override;
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board) override;
    void lim(vector<vector<Piece*>> board);
    Queen(int x, int y, int type);
};

class Pawn: public Piece{
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board) override;
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board) override;
    Pawn(int x, int y, int type);
};

class Knight: public Piece{
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board) override;
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board) override;
    Knight(int x, int y, int type);
};

class King: public Piece{
  public:
    bool movIsValid(int x, int y, vector<vector<Piece*>> board) override;
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board) override;
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
    bool movIsValid(int x, int y, vector<vector<Piece*>> board) override;
    bool atkIsValid(int x, int y, vector<vector<Piece*>> board) override;
    void lim(vector<vector<Piece*>> board);
    Bishop(int x, int y, int type);
};

class Board {
public:
    vector<vector<Piece*>> board; // Tablero de juego
    // Constructor
    Board(int a, int b);
};

Board::Board(int a, int b) {
    // Inicializar el tablero con un tamaño estándar de 8x8
    board.resize(8, vector<Piece*>(8, nullptr));

    // Inicializar las piezas blancas
    board[0][0] = new Rook(0,0,a);
    board[0][1] = new Knight(0,1,a);
    board[0][2] = new Bishop(0,2,a);
    board[0][3] = new Queen(0,3,a);
    board[0][4] = new King(0,4,a);
    board[0][5] = new Bishop(0,5,a);
    board[0][6] = new Knight(0,6,a);
    board[0][7] = new Rook(0,7,a);
    for (int col = 0; col < 8; col++) {
        board[1][col] = new Pawn(1,col,a);
    }

    // Inicializar las piezas negras
    board[7][0] = new Rook(7,0,b);
    board[7][1] = new Knight(7,1,b);
    board[7][2] = new Bishop(7,2,b);
    board[7][3] = new Queen(7,3,b);
    board[7][4] = new King(7,4,b);
    board[7][5] = new Bishop(7,5,b);
    board[7][6] = new Knight(7,6,b);
    board[7][7] = new Rook(7,7,b);

    for (int col = 0; col < 8; col++) {
        board[6][col] = new Pawn(6,col,b);
    }
    for (int col = 0; col < 8; col++) {
      for (int row = 2; row < 6; row++)
        board[row][col] = NULL;
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
      board[this->position_x][this->position_y] = NULL;
      board[x][y] = new Bishop(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Bishop(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new King(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new King(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Knight(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Knight(x, y, this->type);
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
  cout << 0;
  if(y==this->position_y+1 && 
    board[this->position_x][this->position_y+1]==NULL){
    board[this->position_x][this->position_y] = NULL;
    this->position_x = x;
    this->position_y = y;
    board[x][y] = new Pawn(x, y, this->type);
    for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      if(board[i][j]!=NULL)
        cout << board[i][j]->type;
      else cout << 0; 
    }
    cout << endl;
  }
    return true;
  } else {
    return false;
  }
};

bool Pawn::atkIsValid(int x, int y, vector<vector<Piece*>> board){
  cout << 0;
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
      board[this->position_x][this->position_y] = NULL;
      this->position_x = x;
      this->position_y = y;
      
      board[x][y] = new Pawn(x, y, this->type);
      return true;
    } else {
      it++;
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Queen(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Queen(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Rook(x, y, this->type);
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
      board[this->position_x][this->position_y] = NULL;      this->position_x = x;
      this->position_y = y;
      board[x][y] = new Rook(x, y, this->type);
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
      if(board[i][j]!=NULL)
        cout << board[i][j]->type;
      else cout << 0; 
    }
    cout << endl;
  }
}

class Player{

  public:
  int type;
  Player(int type);
};

Player::Player(int type) {
  this->type = type; 
};

void Play(Player p, int x_0, int y_0, int x_1, int y_1, vector<vector<Piece*>> board) {
  if(board[x_0][y_0]!=NULL){
    bool b = board[x_0][y_0]->movIsValid(x_1, y_1, board);
  }
}

int main(){
  bool checkMate = true;
  Player p1 = Player(1);
  Player p2 = Player(2);
  Board b = Board(p1.type, p2.type);
  int current_player = 0;
  cout << 0;
  Play(p2, 1,0,2,0,b.board);
  

  return 0;
}
