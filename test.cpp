#include<iostream>
#include <list>

using namespace std;

class Piece {
  public:
    int position_x;
    int position_y;
    char name;

    void setPosition(int x, int y, bool (*func)(int, int));
};

class Rook: public Piece{
  private:
    int lim_inf_x;
    int lim_inf_y;
    int lim_sup_x;
    int lim_sup_y;
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    void lim();
    Rook(int x, int y);
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
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    void lim();
    Queen(int x, int y);
};

char gameBoard[8][8] = {'0'};

class Pawn: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    Pawn(int x, int y);
};

class Knight: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    Knight(int x, int y);
};

class King: public Piece{
  public:
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    King(int x, int y);
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
    bool movIsValid(int x, int y);
    bool atkIsValid(int x, int y);
    void lim();
    Bishop(int x, int y);
};

class Player{
  public:
  Rook r1 = Rook(0,0); Rook r2 = Rook(0,7);
  Knight k1 = Knight(0,1); Knight k2 = Knight(0,6);
  Bishop b1 = Bishop(0,2); Bishop b2 = Bishop(0,5);
  Queen q = Queen(0,3);King K = King(0,4);
  Pawn p1 = Pawn(1,0); Pawn p2 = Pawn(1,1);
  Pawn p3 = Pawn(1,2); Pawn p4 = Pawn(1,3);
  Pawn p5 = Pawn(1,4); Pawn p6 = Pawn(1,5);
  Pawn p7 = Pawn(1,6); Pawn p8 = Pawn(1,7);
  Player(int i) {
    
    if(i==1){
      this->r1 = Rook(0,0); this->r2 = Rook(0,7);
      this->k1 = Knight(0,1); this->k2 = Knight(0,6);
      this->b1 = Bishop(0,2); this->b2 = Bishop(0,5);
      this->q = Queen(0,3);this->K = King(0,4);
      this->p1 = Pawn(1,0); this->p2 = Pawn(1,1);
      this->p3 = Pawn(1,2); this->p4 = Pawn(1,3);
      this->p5 = Pawn(1,4); this->p6 = Pawn(1,5);
      this->p7 = Pawn(1,6); this->p8 = Pawn(1,7);
    } else if(i==2){
      this->r1 = Rook(7,0); this->r2 = Rook(7,7);
      this->k1 = Knight(7,1); this->k2 = Knight(7,6);
      this->b1 = Bishop(7,2); this->b2 = Bishop(7,5);
      this->q = Queen(7,3);this->K = King(7,4);
      this->p1 = Pawn(6,0); this->p2 = Pawn(6,1);
      this->p3 = Pawn(6,2); this->p4 = Pawn(6,3);
      this->p5 = Pawn(6,4); this->p6 = Pawn(6,5);
      this->p7 = Pawn(6,6); this->p8 = Pawn(6,7);
    }
  };
  void Play(char piece, int x, int y) {
    switch (piece)
    {
    case 'p':
      
      break;
    
    case 'r':
      
      break;
    case 'k':
      
      break;
    case 'K':
      
      break;
    case 'b':
      
      break;
    case 'q':
      
      break;
    }
  }
};

bool Bishop::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim();
  int delta = this->lim_sup_r_x - this->lim_inf_l_x;
  for(int i = 0; i < delta; i++){
    if(gameBoard[lim_inf_l_x+i][lim_inf_l_y+i]=='0'){
      moves.insert(it, lim_inf_l_x+i);
      it++;
      moves.insert(it, lim_inf_l_y+i);
      it++;
    } 
  }
  delta = this->lim_sup_l_x - this->lim_inf_r_x;
  for(int i = 0; i < delta; i++){
    if(gameBoard[lim_sup_l_x-i][lim_sup_l_y-i]=='0'){
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
      gameBoard[x][y] = this->name;
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
      this->position_x = x;
      this->position_y = y;
      gameBoard[x][y] = this->name;
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
    if(gameBoard[i][j]!='0'){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[i][j]!='0'){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_y; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[j][i]!='0'){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[j][i]!='0'){
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

bool King::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(gameBoard[i][j]=='0'){
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
      gameBoard[x][y] = this->name;
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool King::atkIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(gameBoard[i][j]!='0'){
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
      gameBoard[x][y] = this->name;
      return true;
    } else {
      it++;
    }
  }
  return false;
};

King::King(int x, int y) {
  this->position_x = x;
  this->position_y = y;
  this->name = 'K';
}

bool Knight::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int j = this->position_y+1;
  for(int i = this->position_x-1; i <= this->position_x+1; i++){
    for(int j = this->position_y-1; j <= this->position_y+1; j++){
      if(gameBoard[i][j]=='0'){
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
      gameBoard[x][y] = this->name;
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
      if(gameBoard[i][j]!='0'){
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
      gameBoard[x][y] = this->name;
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

bool Pawn::movIsValid(int x, int y){
  if(y==this->position_y+1 && 
    gameBoard[this->position_x][this->position_y+1]=='0'){
    this->position_x = x;
    this->position_y = y;
    gameBoard[x][y] = this->name;
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
    if(gameBoard[i][j]!='0'){
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
      gameBoard[x][y] = this->name;
      return true;
    } else {
      it++;
    }
  }
  return false;
};

Pawn::Pawn(int x, int y) {
  this->position_x = x;
  this->position_y = y;
  this->name = 'p';
}

void Piece::setPosition(int x, int y, bool (*func)(int, int)){
  if(func(x, y)==true) {
    this->position_x = x;
    this->position_y = y;
  } else {

  }
};

bool Queen::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim();
  int delta = this->lim_sup_r_x - this->lim_inf_l_x;
  for(int i = 0; i < delta; i++){
    if(gameBoard[lim_inf_l_x+i][lim_inf_l_y+i]=='0'){
      moves.insert(it, lim_inf_l_x+i);
      it++;
      moves.insert(it, lim_inf_l_y+i);
      it++;
    } 
  }
  delta = this->lim_sup_l_x - this->lim_inf_r_x;
  for(int i = 0; i < delta; i++){
    if(gameBoard[lim_sup_l_x-i][lim_sup_l_y-i]=='0'){
      moves.insert(it, lim_sup_l_x-i);
      it++;
      moves.insert(it, lim_sup_l_y-i);
      it++;
    } 
  }

  int j = this->position_y+1;
  for(int i = this->lim_inf_x+1; i <= this->lim_sup_x-1; i++){
    if(gameBoard[i][this->position_y]=='0'){
      moves.insert(it, i);
      it++;
      moves.insert(it, this->position_y);
      it++;
    }
  }
  for(int i = this->lim_inf_y+1; i <= this->lim_sup_y-1; i++){
    if(gameBoard[this->position_x][i]=='0'){
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
      gameBoard[x][y] = this->name;
      return true;
    } else {
      it++;
    }
  }
  return false;
};

bool Queen::atkIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  int i = this->position_x;
  int j = this->position_y;
  this->lim();
  this->lim();
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
      gameBoard[x][y] = this->name;
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Queen::lim() {
  for (int i = this->position_x; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[i][j]!='0'){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[i][j]!='0'){
      this->lim_sup_r_x = i;
      this->lim_sup_r_y = j;
      break;
    }
  }
  for (int i = this->position_y; i < 7; i++){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[j][i]!='0'){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i > 0; i--){
    int j = this->position_x - i + this->position_y;
    if(gameBoard[j][i]!='0'){
      this->lim_sup_r_x = j;
      this->lim_sup_r_y = i;
      break;
    }
  }
  for (int i = this->position_x; i < 7; i++){
    if(gameBoard[i][this->position_y]!='0'){
      this->lim_sup_x = i;
      break;
    }
  }
   for (int i = this->position_x; i > 0; i--){
    if(gameBoard[i][this->position_y]!='0'){
      this->lim_inf_x = i;
      break;
    }
  }
   for (int i = this->position_y; i < 7; i++){
    if(gameBoard[this->position_x][i]!='0'){
      this->lim_sup_y = i;
      break;
    }
  }
   for (int i = this->position_y; i > 0; i--){
    if(gameBoard[this->position_x][i]!='0'){
      this->lim_inf_y = i;
      break;
    }
  }
}

Queen::Queen(int x, int y) {
  this->position_x = x;
  this->position_y = y;
  this->name = 'q';
}

bool Rook::movIsValid(int x, int y){
  list<int> moves{};
  std::list<int>::iterator it;
  it = moves.begin();
  this->lim();
  int j = this->position_y+1;
  for(int i = this->lim_inf_x+1; i <= this->lim_sup_x-1; i++){
    if(gameBoard[i][this->position_y]=='0'){
      moves.insert(it, i);
      it++;
      moves.insert(it, this->position_y);
      it++;
    }
  }
  for(int i = this->lim_inf_y+1; i <= this->lim_sup_y-1; i++){
    if(gameBoard[this->position_x][i]=='0'){
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
      gameBoard[x][y] = this->name;
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
      this->position_x = x;
      this->position_y = y;
      gameBoard[x][y] = this->name;
      return true;
    } else {
      it++;
    }
  }
  return false;
};

void Rook::lim() {
  for (int i = this->position_x; i < 7; i++){
    if(gameBoard[i][this->position_y]!='0'){
      this->lim_sup_x = i;
      break;
    }
  }
   for (int i = this->position_x; i > 0; i--){
    if(gameBoard[i][this->position_y]!='0'){
      this->lim_inf_x = i;
      break;
    }
  }
   for (int i = this->position_y; i < 7; i++){
    if(gameBoard[this->position_x][i]!='0'){
      this->lim_sup_y = i;
      break;
    }
  }
   for (int i = this->position_y; i > 0; i--){
    if(gameBoard[this->position_x][i]!='0'){
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

void setPiece(char name, int x, int y){
  if(x!=(-1))
    gameBoard[x][y] = name;
}

void setGameBoard(Player p1) {
  setPiece(p1.r1.name, p1.r1.position_x, p1.r1.position_y);
  setPiece(p1.r2.name, p1.r2.position_x, p1.r2.position_y);
  setPiece(p1.k1.name, p1.k1.position_x, p1.k1.position_y);
  setPiece(p1.k2.name, p1.k2.position_x, p1.k2.position_y);
  setPiece(p1.b1.name, p1.b1.position_x, p1.b1.position_y);
  setPiece(p1.b2.name, p1.b2.position_x, p1.b2.position_y);
  setPiece(p1.q.name, p1.q.position_x, p1.q.position_y);
  setPiece(p1.K.name, p1.K.position_x, p1.K.position_y);
  setPiece(p1.p1.name, p1.p1.position_x, p1.p1.position_y);
  setPiece(p1.p2.name, p1.p2.position_x, p1.p2.position_y);
  setPiece(p1.p3.name, p1.p3.position_x, p1.p3.position_y);
  setPiece(p1.p4.name, p1.p4.position_x, p1.p4.position_y);
  setPiece(p1.p5.name, p1.p5.position_x, p1.p5.position_y);
  setPiece(p1.p6.name, p1.p6.position_x, p1.p6.position_y);
  setPiece(p1.p7.name, p1.p7.position_x, p1.p7.position_y);
  setPiece(p1.p8.name, p1.p8.position_x, p1.p8.position_y);
}

void printGameBoard(){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      cout << gameBoard[i][j];
    }
    cout << endl;
  }
}

int main(){
  Player p1 = Player(1);
  Player p2 = Player(2);
  setGameBoard(p1);  
  setGameBoard(p2);
  printGameBoard();
  
  return 0;
}
