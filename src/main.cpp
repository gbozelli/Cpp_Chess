#include<iostream>
#include <list>
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"

using namespace std;

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
};

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