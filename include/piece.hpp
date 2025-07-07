#ifndef PIECE_HPP
#define PIECE_HPP

#include <list>
#include <cmath> // Para abs()
#include <utility> // Para std::pair

// Forward declaration da classe Board
class Board;

class Piece {
public:
    virtual ~Piece() = default;
    int position_x;
    int position_y;
    char name; // 'p', 'r', 'k', 'b', 'q', 'K' para brancas; 'P', 'R', 'N', 'B', 'Q', 'K' para pretas (Cavalo é 'n'/'N' para evitar conflito com Rei)
    bool isWhite; // true para peças brancas, false para peças pretas
    bool hasMoved; // Para roque e peão (movimento inicial de duas casas)

    Piece(int x, int y, char n, bool white) :
        position_x(x), position_y(y), name(n), isWhite(white), hasMoved(false) {}

    // Construtor padrão (necessário para a classe Player e Board)
    Piece() : position_x(-1), position_y(-1), name(' '), isWhite(false), hasMoved(false) {}

    // Métodos virtuais puros. Eles precisam de uma referência ao tabuleiro para verificar movimentos.
    virtual bool isValidMove(int newX, int newY, const Board& board) = 0;
    virtual bool isValidCapture(int newX, int newY, const Board& board) = 0;
    // virtual void getPossibleMoves(std::list<std::pair<int, int>>& possibleMoves, const Board& board) = 0; // Opcional, para sugerir movimentos

    // Método para atualizar a posição da peça.
    void setPosition(int x, int y);
};

#endif // PIECE_HPP