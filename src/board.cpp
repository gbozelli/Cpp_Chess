#include "../include/board.hpp"
#include "../include/pawn.hpp"
#include "../include/rook.hpp"
#include "../include/knight.hpp"
#include "../include/bishop.hpp"
#include "../include/queen.hpp"
#include "../include/king.hpp"
#include <iostream>
#include <cctype> // Para isupper, islower

Board::Board()
{
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      squares[i][j] = nullptr;
    }
  }
}

Board::~Board()
{
  // Liberar a memória de todas as peças no tabuleiro
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      delete squares[i][j];
      squares[i][j] = nullptr;
    }
  }
}

void Board::initializeBoard()
{
  // Limpa o tabuleiro antes de inicializar
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      delete squares[i][j]; // Libera peças existentes
      squares[i][j] = nullptr;
    }
  }

  // Peças brancas
  squares[0][0] = new Rook(0, 0, true);
  squares[0][1] = new Knight(0, 1, true);
  squares[0][2] = new Bishop(0, 2, true);
  squares[0][3] = new Queen(0, 3, true);
  squares[0][4] = new King(0, 4, true);
  this->whiteKingX = 0;
  this->whiteKingY = 4;
  squares[0][5] = new Bishop(0, 5, true);
  squares[0][6] = new Knight(0, 6, true);
  squares[0][7] = new Rook(0, 7, true);
  for (int j = 0; j < 8; ++j)
  {
    squares[1][j] = new Pawn(1, j, true);
  }

  // Peças pretas
  squares[7][0] = new Rook(7, 0, false);
  squares[7][1] = new Knight(7, 1, false);
  squares[7][2] = new Bishop(7, 2, false);
  squares[7][3] = new Queen(7, 3, false);
  squares[7][4] = new King(7, 4, false);
  this->blackKingX = 7;
  this->blackKingY = 4;
  squares[7][5] = new Bishop(7, 5, false);
  squares[7][6] = new Knight(7, 6, false);
  squares[7][7] = new Rook(7, 7, false);
  for (int j = 0; j < 8; ++j)
  {
    squares[6][j] = new Pawn(6, j, false);
  }
}

void Board::printBoard() const
{
  std::cout << "  A B C D E F G H" << std::endl;
  std::cout << "  -----------------" << std::endl;
  for (int i = 7; i >= 0; --i)
  { // Imprimir do 8 para 1 (topo para baixo)
    std::cout << (i + 1) << " |";
    for (int j = 0; j < 8; ++j)
    {
      if (squares[i][j] == nullptr)
      {
        std::cout << "  "; // Duplo espaço para melhor alinhamento
      }
      else
      {
        std::cout << squares[i][j]->name << " ";
      }
    }
    std::cout << "|" << std::endl;
  }
  std::cout << "  -----------------" << std::endl;
}

Piece *Board::getPieceAt(int x, int y) const
{
  if (x < 0 || x >= 8 || y < 0 || y >= 8)
    return nullptr;
  return squares[x][y];
}

void Board::setPieceAt(int x, int y, Piece *piece)
{
  if (x >= 0 && x < 8 && y >= 0 && y < 8)
  {
    squares[x][y] = piece;
  }
}

// Verifica se o rei está em xeque
bool Board::isKingInCheck(bool isWhiteKing) const
{
  int kingX = isWhiteKing ? whiteKingX : blackKingX;
  int kingY = isWhiteKing ? whiteKingY : blackKingY;

  // Um rei está em xeque se alguma peça inimiga puder atacá-lo
  return isSquareAttacked(kingX, kingY, !isWhiteKing); // Verificar se o rei está atacado por peças da cor oposta
}

// Verifica se uma casa específica está sendo atacada por peças de uma determinada cor
bool Board::isSquareAttacked(int x, int y, bool byWhitePieces) const
{
  // Iterar por todas as casas do tabuleiro
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      Piece *attacker = getPieceAt(i, j);
      if (attacker != nullptr && attacker->isWhite == byWhitePieces)
      {
        // Se for um rei, o isValidCapture deve ser capaz de verificar se o rei pode "atacar" uma casa (distância 1)
        // mas sem realmente se mover para ela
        // Para simplificar, vamos usar isValidCapture, que já verifica se há peça inimiga.
        // Aqui, precisamos verificar se a peça 'attacker' *poderia* capturar a casa (x,y)
        // mesmo que não haja uma peça lá, ou se houver uma, se é inimiga.

        // Uma maneira de fazer isso é simular uma peça dummy na posição (x,y)
        // e ver se o attacker a "atacaria". Mas é mais fácil checar se o move/capture
        // da peça atacante alcança a casa (x,y) *e* se o caminho está livre.

        // A forma mais direta é chamar isValidCapture. Se a isValidCapture
        // for projetada para retornar true se puder atingir uma peça inimiga ou uma casa vazia para movimento,
        // teríamos que fazer ajustes. Mas para xeque, precisamos saber se *qualquer* peça atacante
        // pode capturar *nossa* peça (ou seja, o rei).

        // Vamos reavaliar a isValidCapture para um propósito mais genérico: pode alcançar?
        // Para xeque, a lógica é que o rei está em (x,y).
        // Precisamos verificar se qualquer peça inimiga pode alcançar (x,y) como se fosse uma captura.

        // Solução mais robusta para isSquareAttacked:
        // Criar um movimento temporário para testar


      }
    }
  }
  return false;
}

// Simula um movimento para verificar se o rei ficaria em xeque
bool Board::simulateMoveAndCheck(int startX, int startY, int endX, int endY, bool isWhiteTurn) 
{
  Piece *movedPiece = getPieceAt(startX, startY);
  if (movedPiece == nullptr)
    return true; // Erro, não há peça para mover

  // Salvar o estado original do tabuleiro
  Piece *originalStartPiece = squares[startX][startY];
  Piece *originalEndPiece = squares[endX][endY];

  // Realizar o movimento simulado
  squares[endX][endY] = originalStartPiece;
  squares[startX][startY] = nullptr;

  // Atualizar temporariamente a posição do rei se o rei for a peça movida
  int tempKingX = isWhiteTurn ? whiteKingX : blackKingX;
  int tempKingY = isWhiteTurn ? whiteKingY : blackKingY;
  if (movedPiece->name == (isWhiteTurn ? 'K' : 'k'))
  { // É o rei que se moveu
    if (isWhiteTurn)
    {
      whiteKingX = endX;
      whiteKingY = endY;
    }
    else
    {
      blackKingX = endX;
      blackKingY = endY;
    }
  }

  bool kingInCheckAfterMove = isKingInCheck(isWhiteTurn);

  // Desfazer o movimento simulado
  squares[startX][startY] = originalStartPiece;
  squares[endX][endY] = originalEndPiece;

  // Restaurar a posição do rei
  if (movedPiece->name == (isWhiteTurn ? 'K' : 'k'))
  {
    if (isWhiteTurn)
    {
      whiteKingX = tempKingX;
      whiteKingY = tempKingY;
    }
    else
    {
      blackKingX = tempKingX;
      blackKingY = tempKingY;
    }
  }
  return kingInCheckAfterMove;
}

void Board::setLastPawnMove(int x, int y, int prevY)
{
  lastPawnMovedX = x;
  lastPawnMovedY = y;
  lastPawnMovedPrevY = prevY;
}

void Board::resetLastPawnMove()
{
  lastPawnMovedX = -1;
  lastPawnMovedY = -1;
  lastPawnMovedPrevY = -1;
}