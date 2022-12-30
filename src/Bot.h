#include "MoveGenerator.h"
class Bot {
private:
    int evalPosition(Board &board);
    int defense(Board &borad, int depth, int alpha);
    int attack(Board &borad, int depth, int beta);
    std::vector<int> value = {0, 10, 1, 3, 3, 5, 9};
private:
    MoveGenerator generator;
public:
    Move bestMove(Board board);

    Bot();

};



