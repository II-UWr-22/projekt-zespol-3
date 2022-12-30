#ifndef MOVE_H
#define MOVE_H

#include <string>
using std::pair;
using std::string;
class Move{
private:
    void stringMoveToCords(string& move);
    int charToCol(char ch);
public:
    // for castling and En Passant
    Move* secondaryMove = nullptr;


    pair<int,int> startingSquare;
    pair<int,int> targetSquare;

    Move() = default;
    Move(string& move);
    Move(pair<int,int> start, pair<int,int> end);
    Move(int x1, int y1, int x2, int y2);
    Move(const Move& other);

    string toString();
};

#endif