#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "piece.hpp"
#include "king.hpp" // Para roque

#include <string>

class Game
{
private:
  Board board;
  bool isWhiteTurn; // true se for a vez das brancas, false para as pretas
  bool gameOver;
  std::string winner;

  // Para o roque, precisamos de acesso direto às instâncias do Rei e das Torres
  // (Poderíamos ter uma lista de peças, mas para simplificar agora, direto)
  King *whiteKing;
  King *blackKing;
  Rook *whiteRook1;
  Rook *whiteRook2;
  Rook *blackRook1;
  Rook *blackRook2;

public:
  Game();
  void run(); // Loop principal do jogo

private:
  void setupGame(); // Configura o tabuleiro e as peças
  void handlePlayerInput();
  bool parseMove(const std::string &input, int &startX, int &startY, int &endX, int &endY);
  bool makeMove(int startX, int startY, int endX, int endY);        // Tenta fazer um movimento
  bool isValidGameMove(int startX, int startY, int endX, int endY); // Verifica a validade do movimento no contexto do jogo
  void switchTurn();
  void checkGameEndConditions(); // Xeque-mate, afogamento, etc.

  // Helper functions
  char getColChar(int y) const { return 'a' + y; }
  int getColInt(char c) const { return c - 'a'; }
  int getRowInt(char r) const { return r - '1'; } // '1' a '8'

  // Movimentos especiais
  bool attemptCastle(int startX, int startY, int endX, int endY);
  bool attemptPromotion(Piece *pawn, int newX, int newY);
  bool attemptEnPassant(int startX, int startY, int endX, int endY);

  // Xeque-mate
  bool isCheckmate(bool isWhiteKing) const;
  bool hasValidMoves(bool isWhitePieces);
};

#endif // GAME_HPP