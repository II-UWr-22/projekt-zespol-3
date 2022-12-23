#include "Move.h"

Move::Move(string &move) {
    stringMoveToCords(move);
}

void Move::stringMoveToCords(string &move) {
    startingSquare = {7-(move[1]-'1'), charToCol(move[0])};
    targetSquare = {7-(move[3]-'1'), charToCol(move[2])};
}

Move::Move(pair<int, int> start, pair<int, int> end) {
    startingSquare = start;
    targetSquare = end;
}

Move::Move(int x1, int y1, int x2, int y2) {
    startingSquare = pair<int,int>(x1, y1);
    targetSquare = pair<int,int>(x2, y2);
}

int Move::charToCol(char ch) {
    return (ch-'a');
}

string Move::toString() {
    string res = "____";
    res[0] = (startingSquare.second + 'a');
    res[1] = ('8'-startingSquare.first);
    res[2] = (targetSquare.second + 'a');
    res[3] = ('8'-targetSquare.first);
    return res;
}

Move::Move(const Move &other) {
    startingSquare = other.startingSquare;
    targetSquare = other.targetSquare;
    secondaryMove = other.secondaryMove;
}
