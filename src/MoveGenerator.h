#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "Board.h"
#include "Move.h"
#include <vector>

using std::pair;
using std::vector;

class MoveGenerator {
private:
    Board board;
    vector<Move> moves;

    int friendlyColor;
private:
    void generateKingMoves(pair<int, int> square);
    void generateDiagonalMoves(pair<int, int> square);
    void generateStraightMoves(pair<int, int> square);
    void generateKnightMoves(pair<int, int> square);
    void generatePawnMoves(pair<int, int> square);

    bool inBounds(pair<int,int> square);

    void generatePseudoLegalMoves();

    bool isSquareThreatened(pair<int,int> square, Board& board);


public:

    vector<Move> generateMoves(const Board& p_board);
    void init();

};

#endif
