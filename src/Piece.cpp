#include "Piece.h"
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

const std::map<char, int> Piece::pieceSymbol = {
        {'p', Piece::Pawn},
        {'r', Piece::Rook},
        {'n', Piece::Knight},
        {'b', Piece::Bishop},
        {'q', Piece::Queen},
        {'k', Piece::King}
};
