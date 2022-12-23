#include <array>
#include "Move.h"
#include <string>
#include "Piece.h"
#include <iostream>

using std::array;
using std::string;
class Board{
private:
    array<array<int, 8>, 8> _board;

    void init();
public:
    int colorToMove;
    Move lastMove;
    array<array<bool, 8>, 8> hasMoved;
public:
    Board();
    Board(const string& fen);
    Board(string&& fen);
    Board(const Board& other);
    ~Board();

    void makeMove(Move& move);
    void loadPositionFromFen(const string& fen);

    array<int,8> operator[](int row);
};