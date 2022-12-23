#include "MoveGenerator.h"
class Bot {
private:
    double evalPosition(Board board);
    Move search(Board board, int depth);
private:
    MoveGenerator generator;
public:
    Move bestMove(Board board);

    Bot();

};



