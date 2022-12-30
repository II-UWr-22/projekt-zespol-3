#include "Move.h"

Move::Move(string &move) {
    stringMoveToCords(move);
}

void Move::stringMoveToCords(string &move) {
    startingSquare = {7-(move[1]-'1'), charToCol(move[0])};
    targetSquare = {7-(move[3]-'1'), charToCol(move[2])};
    if(move.length() == 5){
        promotion = Piece::pieceSymbol.at(move[4]);
        if(targetSquare.second == 7)
            promotion |= Piece::Black;
        else
            promotion |= Piece::White;
    }
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
    if(promotion != Piece::None){
        char p;
        switch(Piece::pieceType(promotion)){
            case Piece::Bishop:
                p = 'b';
                break;
            case Piece::Knight:
                p = 'n';
                break;
            case Piece::Queen:
                p = 'q';
                break;
            case Piece::Rook:
                p = 'r';
                break;
        }
        res += p;
    }
    return res;
}

Move::Move(const Move &other) {
    startingSquare = other.startingSquare;
    targetSquare = other.targetSquare;
    secondaryMove = other.secondaryMove;
    promotion = other.promotion;
}
