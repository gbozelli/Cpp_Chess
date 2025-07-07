#ifndef BOARD_HPP
#define BOARD_HPP

#pragma once // Garante que o arquivo seja incluído apenas uma vez

#include "piece.hpp"   // Garante que a classe base Piece seja totalmente definida
#include "rook.hpp"    // Full definition of Rook
#include "pawn.hpp"    // Full definition of Pawn
#include "king.hpp"    // Full definition of King
#include "queen.hpp"
#include "bishop.hpp"
#include "knight.hpp"

// Se gameBoard for uma variável global definida em outro .cpp, declare-a aqui como extern
extern char gameBoard[8][8]; // Adapte para onde gameBoard é realmente declarado

// Forward declarations para evitar inclusões circulares se as peças
// precisarem de uma referência ao Board (o que é o caso)
class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;

class Board
{
private:
  // O tabuleiro agora guarda ponteiros para Piece
  Piece *squares[8][8]; // Armazena as peças no tabuleiro
  // Para xeque e xeque-mate, precisamos saber a posição dos reis
  int whiteKingX, whiteKingY;
  int blackKingX, blackKingY;

  // Para En Passant: rastreia o último movimento de peão de duas casas
  int lastPawnMovedX = -1;
  int lastPawnMovedY = -1;
  int lastPawnMovedPrevY = -1; // Posição Y inicial do peão antes do movimento de 2 casas

public:
  void setPieceAt(int x, int y, Piece *piece);
  Board();
  ~Board(); // Destrutor para liberar a memória das peças

  void initializeBoard();
  void printBoard() const;

  Piece *getPieceAt(int x, int y) const;// Usado para mover ou remover peças

  // Funções para verificar xeque
  bool isKingInCheck(bool isWhiteKing) const;
  bool isSquareAttacked(int x, int y, bool byWhitePieces) const;

  // Para simular movimentos e verificar xeque
  bool simulateMoveAndCheck(int startX, int startY, int endX, int endY, bool isWhiteTurn);

  // Getters para a posição do rei
  int getWhiteKingX() const { return whiteKingX; }
  int getWhiteKingY() const { return whiteKingY; }
  int getBlackKingX() const { return blackKingX; }
  int getBlackKingY() const { return blackKingY; }

  // Setters para a posição do rei (chamados quando o rei se move)
  void setWhiteKingPosition(int x, int y)
  {
    whiteKingX = x;
    whiteKingY = y;
  }
  void setBlackKingPosition(int x, int y)
  {
    blackKingX = x;
    blackKingY = y;
  }

  // En Passant
  void setLastPawnMove(int x, int y, int prevY);
  int getLastPawnMovedX() const { return lastPawnMovedX; }
  int getLastPawnMovedY() const { return lastPawnMovedY; }
  int getLastPawnMovedPrevY() const { return lastPawnMovedPrevY; }
  void resetLastPawnMove(); // Resetar após cada turno
};

#endif // BOARD_HPP