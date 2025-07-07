#include "../include/game.hpp"
#include <iostream>
#include <limits>    // Para numeric_limits
#include <algorithm> // Para std::tolower

Game::Game() : isWhiteTurn(true), gameOver(false), whiteKing(nullptr), blackKing(nullptr),
               whiteRook1(nullptr), whiteRook2(nullptr), blackRook1(nullptr), blackRook2(nullptr)
{
  setupGame();
}

void Game::setupGame()
{
  board.initializeBoard();
  // Encontrar os reis e torres no tabuleiro para o roque
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      Piece *p = board.getPieceAt(i, j);
      if (p != nullptr)
      {
        if (p->name == 'K')
        { // Rei branco
          whiteKing = static_cast<King *>(p);
        }
        else if (p->name == 'k')
        { // Rei preto
          blackKing = static_cast<King *>(p);
        }
        else if (p->name == 'r')
        { // Torre branca
          if (p->position_y == 0)
            whiteRook1 = static_cast<Rook *>(p);
          else if (p->position_y == 7)
            whiteRook2 = static_cast<Rook *>(p);
        }
        else if (p->name == 'R')
        { // Torre preta
          if (p->position_y == 0)
            blackRook1 = static_cast<Rook *>(p);
          else if (p->position_y == 7)
            blackRook2 = static_cast<Rook *>(p);
        }
      }
    }
  }
}

void Game::run()
{
  while (!gameOver)
  {
    board.printBoard();
    std::cout << (isWhiteTurn ? "Turno das Brancas (minúsculas)" : "Turno das Pretas (MAIÚSCULAS)") << std::endl;
    std::cout << "Digite seu movimento (ex: e2 e4, ou o-o para roque pequeno, o-o-o para roque grande): ";

    handlePlayerInput();

    if (!gameOver)
    { // Checa se o jogo não terminou após o movimento
      checkGameEndConditions();
    }
  }
  board.printBoard();
  std::cout << "Fim de Jogo! " << winner << std::endl;
}

void Game::handlePlayerInput()
{
  std::string input;
  std::getline(std::cin, input);

  // Limpar o buffer de entrada para a próxima leitura
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  // Tentar Roque
  if (input == "o-o")
  { // Roque pequeno
    if (attemptCastle(whiteKing->position_x, whiteKing->position_y, whiteKing->position_x + 2, whiteKing->position_y))
    {
      switchTurn();
      return;
    }
    else if (attemptCastle(blackKing->position_x, blackKing->position_y, blackKing->position_x - 2, blackKing->position_y))
    {
      switchTurn();
      return;
    }
    else
    {
      std::cout << "Movimento de roque inválido." << std::endl;
      return; // Permite ao jogador tentar novamente
    }
  }
  else if (input == "o-o-o")
  { // Roque grande
    if (attemptCastle(whiteKing->position_x, whiteKing->position_y, whiteKing->position_x - 2, whiteKing->position_y))
    {
      switchTurn();
      return;
    }
    else if (attemptCastle(blackKing->position_x, blackKing->position_y, blackKing->position_x + 2, blackKing->position_y))
    {
      switchTurn();
      return;
    }
    else
    {
      std::cout << "Movimento de roque inválido." << std::endl;
      return;
    }
  }

  int startX, startY, endX, endY;
  if (!parseMove(input, startX, startY, endX, endY))
  {
    std::cout << "Entrada inválida. Tente novamente no formato 'e2 e4'." << std::endl;
    return;
  }

  if (!makeMove(startX, startY, endX, endY))
  {
    std::cout << "Movimento inválido. Tente novamente." << std::endl;
  }
  else
  {
    switchTurn();
  }
}

bool Game::parseMove(const std::string &input, int &startX, int &startY, int &endX, int &endY)
{
  if (input.length() != 5 || input[2] != ' ')
  {
    return false;
  }

  startY = getColInt(std::tolower(input[0]));
  startX = getRowInt(input[1]);
  endY = getColInt(std::tolower(input[3]));
  endX = getRowInt(input[4]);

  // Validar limites do tabuleiro
  if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
      endX < 0 || endX >= 8 || endY < 0 || endY >= 8)
  {
    return false;
  }
  return true;
}

bool Game::makeMove(int startX, int startY, int endX, int endY)
{
  Piece *pieceToMove = board.getPieceAt(startX, startY);

  if (pieceToMove == nullptr)
  {
    std::cout << "Não há peça na posição inicial." << std::endl;
    return false;
  }

  // Verificar se é a vez do jogador correto
  if (pieceToMove->isWhite != isWhiteTurn)
  {
    std::cout << "Não é a sua vez de mover esta peça." << std::endl;
    return false;
  }

  // Verificar se o movimento é válido para a peça específica
  bool isCapture = (board.getPieceAt(endX, endY) != nullptr);
  bool isValidPieceMove;

  if (isCapture)
  {
    isValidPieceMove = pieceToMove->isValidCapture(endX, endY, board);
  }
  else
  {
    isValidPieceMove = pieceToMove->isValidMove(endX, endY, board);
  }

  if (!isValidPieceMove)
  {
    std::cout << "Movimento ou captura inválida para esta peça." << std::endl;
    return false;
  }

  // Verificação de xeque: o movimento não pode colocar ou deixar o próprio rei em xeque
  if (board.simulateMoveAndCheck(startX, startY, endX, endY, isWhiteTurn))
  {
    std::cout << "Este movimento deixaria seu rei em xeque." << std::endl;
    return false;
  }

  // Se o movimento for válido e não resultar em xeque, execute-o
  Piece *capturedPiece = board.getPieceAt(endX, endY);
  if (capturedPiece != nullptr)
  {
    delete capturedPiece;                  // Libera a memória da peça capturada
    board.setPieceAt(endX, endY, nullptr); // Limpa a posição antiga da peça capturada
  }

  // Tratar En Passant
  if (dynamic_cast<Pawn *>(pieceToMove) && abs(endY - startY) == 1 && abs(endX - startX) == (isWhiteTurn ? 1 : -1) && board.getPieceAt(endX, endY) == nullptr)
  {
    // Isso significa que é um ataque diagonal para uma casa vazia, indicando um En Passant
    int capturedPawnX = endX;
    int capturedPawnY = board.getLastPawnMovedY();         // A posição Y do peão que foi movido 2 casas
    int capturedPawnPrevY = board.getLastPawnMovedPrevY(); // A posição Y original do peão capturado

    // Verificar se é realmente um En Passant válido (se o peão inimigo acabou de mover 2 casas adjacentes)
    if (board.getPieceAt(capturedPawnX, capturedPawnY) != nullptr &&
        dynamic_cast<Pawn *>(board.getPieceAt(capturedPawnX, capturedPawnY)) &&
        board.getPieceAt(capturedPawnX, capturedPawnY)->isWhite != isWhiteTurn &&
        abs(capturedPawnPrevY - capturedPawnY) == 2 &&               // Peão moveu 2 casas
        capturedPawnX == (isWhiteTurn ? (startX) : (startX)) &&      // Mesma coluna do peão que moveu 2 casas
        capturedPawnY == (isWhiteTurn ? (startY + 1) : (startY - 1)) // Peão capturado está adjacente
    )
    {
      Piece *enPassantCaptured = board.getPieceAt(capturedPawnX, capturedPawnY);
      delete enPassantCaptured;
      board.setPieceAt(capturedPawnX, capturedPawnY, nullptr);
      std::cout << "En Passant!" << std::endl;
    }
    else
    {
      std::cout << "Movimento de peão inválido. (Não é En Passant)" << std::endl;
      return false;
    }
  }

  // Mover a peça
  board.setPieceAt(endX, endY, pieceToMove);
  board.setPieceAt(startX, startY, nullptr);
  pieceToMove->setPosition(endX, endY);

  // Atualizar a posição do rei se ele se moveu
  if (pieceToMove->name == (isWhiteTurn ? 'K' : 'k'))
  {
    if (isWhiteTurn)
    {
      board.setWhiteKingPosition(endX, endY);
    }
    else
    {
      board.setBlackKingPosition(endX, endY);
    }
  }

  // Checar promoção de peão
  if (dynamic_cast<Pawn *>(pieceToMove) && (endY == 7 || endY == 0))
  {
    attemptPromotion(pieceToMove, endX, endY);
  }

  // Registrar último movimento de peão para En Passant
  if (dynamic_cast<Pawn *>(pieceToMove) && abs(startY - endY) == 2)
  {
    board.setLastPawnMove(endX, endY, startY);
  }
  else
  {
    board.resetLastPawnMove(); // Resetar se não for um movimento de peão de 2 casas
  }

  return true;
}

bool Game::isValidGameMove(int startX, int startY, int endX, int endY)
{
  // Esta função é uma redundância se makeMove for robusta.
  // A lógica de makeMove já valida tudo (peça, turno, validade do movimento da peça, xeque).
  // Poderíamos refatorar para que makeMove retorne true/false e essa função seja o wrapper.
  return makeMove(startX, startY, endX, endY);
}

void Game::switchTurn()
{
  isWhiteTurn = !isWhiteTurn;
}

void Game::checkGameEndConditions()
{
  bool currentKingInCheck = board.isKingInCheck(isWhiteTurn);
  if (currentKingInCheck)
  {
    if (!hasValidMoves(isWhiteTurn))
    {
      gameOver = true;
      winner = isWhiteTurn ? "Pretas vencem por xeque-mate!" : "Brancas vencem por xeque-mate!";
    }
    else
    {
      std::cout << "Xeque!" << std::endl;
    }
  }
  else
  {
    if (!hasValidMoves(isWhiteTurn))
    {
      gameOver = true;
      winner = "Empate por afogamento!";
    }
  }
}

// Implementação dos movimentos especiais

bool Game::attemptCastle(int kingX, int kingY, int newKingX, int newKingY)
{
  King *king = static_cast<King *>(board.getPieceAt(kingX, kingY));
  if (king == nullptr || king->isWhite != isWhiteTurn)
    return false;

  // Verificar se é um movimento de roque válido para o rei
  if (kingX == (isWhiteTurn ? 0 : 7) && kingY == 4)
  { // Posição inicial do rei
    // Roque Kingside
    if (newKingY == 6 && king->canCastleKingside(board))
    {
      Rook *rook = static_cast<Rook *>(board.getPieceAt(kingX, 7));
      if (rook != nullptr && rook->name == (isWhiteTurn ? 'r' : 'R'))
      {
        // Mover rei
        board.setPieceAt(newKingX, newKingY, king);
        board.setPieceAt(kingX, kingY, nullptr);
        king->setPosition(newKingX, newKingY);
        if (isWhiteTurn)
          board.setWhiteKingPosition(newKingX, newKingY);
        else
          board.setBlackKingPosition(newKingX, newKingY);

        // Mover torre
        board.setPieceAt(newKingX, 5, rook); // Torre vai para a coluna 5
        board.setPieceAt(kingX, 7, nullptr);
        rook->setPosition(newKingX, 5);
        std::cout << "Roque Pequeno!" << std::endl;
        return true;
      }
    }
    // Roque Queenside
    else if (newKingY == 2 && king->canCastleQueenside(board))
    {
      Rook *rook = static_cast<Rook *>(board.getPieceAt(kingX, 0));
      if (rook != nullptr && rook->name == (isWhiteTurn ? 'r' : 'R'))
      {
        // Mover rei
        board.setPieceAt(newKingX, newKingY, king);
        board.setPieceAt(kingX, kingY, nullptr);
        king->setPosition(newKingX, newKingY);
        if (isWhiteTurn)
          board.setWhiteKingPosition(newKingX, newKingY);
        else
          board.setBlackKingPosition(newKingX, newKingY);

        // Mover torre
        board.setPieceAt(newKingX, 3, rook); // Torre vai para a coluna 3
        board.setPieceAt(kingX, 0, nullptr);
        rook->setPosition(newKingX, 3);
        std::cout << "Roque Grande!" << std::endl;
        return true;
      }
    }
  }
  return false;
}

bool Game::attemptPromotion(Piece *pawn, int newX, int newY)
{
  if (dynamic_cast<Pawn *>(pawn) == nullptr)
    return false; // Não é um peão

  // Verifica se o peão atingiu a última fileira
  if ((pawn->isWhite && newX == 7) || (!pawn->isWhite && newX == 0))
  {
    std::cout << "Peão promovido! Escolha a peça (Q/R/B/N): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa buffer

    Piece *newPiece = nullptr;
    bool validChoice = false;

    switch (std::tolower(choice))
    {
    case 'q':
      newPiece = new Queen(newX, newY, pawn->isWhite);
      validChoice = true;
      break;
    case 'r':
      newPiece = new Rook(newX, newY, pawn->isWhite);
      validChoice = true;
      break;
    case 'b':
      newPiece = new Bishop(newX, newY, pawn->isWhite);
      validChoice = true;
      break;
    case 'n':
      newPiece = new Knight(newX, newY, pawn->isWhite);
      validChoice = true;
      break;
    default:
      std::cout << "Escolha inválida. Peão se tornará uma Rainha por padrão." << std::endl;
      newPiece = new Queen(newX, newY, pawn->isWhite);
      validChoice = true;
      break;
    }

    if (validChoice)
    {
      delete pawn;                            // Libera o peão original
      board.setPieceAt(newX, newY, newPiece); // Coloca a nova peça no tabuleiro

      // Se for o rei que está sendo promovido (embora não deva acontecer), atualiza a posição do rei
      // Não é o caso aqui.

      std::cout << "Peão promovido para " << newPiece->name << "!" << std::endl;
      return true;
    }
  }
  return false;
}

// A lógica de En Passant deve ser integrada no makeMove, pois envolve a captura de uma peça que não está no destino final
bool Game::attemptEnPassant(int startX, int startY, int endX, int endY)
{
  // Esta função não é mais chamada diretamente como um movimento "especial" separado.
  // A lógica de En Passant foi movida para dentro de makeMove.
  return false;
}

// Verifica se o jogador atual tem algum movimento válido para evitar o xeque ou para não estar afogado.
bool Game::hasValidMoves(bool isWhitePieces)
{
  // Itera por todas as peças do jogador atual
  for (int startX = 0; startX < 8; ++startX)
  {
    for (int startY = 0; startY < 8; ++startY)
    {
      Piece *piece = board.getPieceAt(startX, startY);
      if (piece != nullptr && piece->isWhite == isWhitePieces)
      {
        // Para cada peça, verifica todas as casas possíveis de destino
        for (int endX = 0; endX < 8; ++endX)
        {
          for (int endY = 0; endY < 8; ++endY)
          {
            // Tentar movimento normal ou captura
            bool isCaptureAttempt = (board.getPieceAt(endX, endY) != nullptr);
            bool isValidPieceMove = false;

            if (isCaptureAttempt)
            {
              isValidPieceMove = piece->isValidCapture(endX, endY, board);
            }
            else
            {
              isValidPieceMove = piece->isValidMove(endX, endY, board);
            }

            if (isValidPieceMove)
            {
              // Se o movimento for válido para a peça, simula e verifica se o rei ainda estaria em xeque
              if (!board.simulateMoveAndCheck(startX, startY, endX, endY, isWhitePieces))
              {
                return true; // Encontrou um movimento válido que tira o rei do xeque ou não o coloca em xeque
              }
            }
          }
        }
      }
    }
  }
  return false; // Nenhuma jogada válida encontrada
}