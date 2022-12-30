#include "MoveGenerator.h"
class Bot {
private:
    int evalPosition(Board &board);
    int defense(Board &borad, int depth);
    int attack(Board &borad, int depth);
    std::vector<int> value = {0, 10, 1, 3, 3, 5, 9};
    std::vector<int> alt = vector<int>(12);
private:
    MoveGenerator generator;
public:
    Move bestMove(Board board);

    Bot();

};



