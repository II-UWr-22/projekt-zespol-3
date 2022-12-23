#include "Piece.h"
const map<char,int> Piece::pieceSymbol =  Piece::createMap();
bool Piece::isColor(int piece, int color) {
    return (piece & colourMask) == color;
}

int Piece::color(int piece) {
    return piece & colourMask;
}

int Piece::pieceType(int piece) {
    return piece & typeMask;
}

bool Piece::isSlidingPiece(int piece) {
    return (piece & 0b100) != 0;
}
