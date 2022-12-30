#ifndef PIECE_H
#define PIECE_H

#include <map>
using std::map;

class Piece{
public:
    static const int None = 0;
    static const int King = 1;
    static const int Pawn = 2;
    static const int Knight = 3;
    static const int Bishop = 4;
    static const int Rook = 5;
    static const int Queen = 6;

    static const int White = 8;
    static const int Black = 16;


    // Work around declaring static const map because c++ won't let you
    static const map<char, int> pieceSymbol;
    static map<char,int> createMap()
    {
        map<char, int> m = {
                {'p', Piece::Pawn},
                {'r', Piece::Rook},
                {'n', Piece::Knight},
                {'b', Piece::Bishop},
                {'q', Piece::Queen},
                {'k', Piece::King}
        };
        return m;
    }


private:
    static const int typeMask = 0b00111;
	static const int blackMask = 0b10000;
	static const int whiteMask = 0b01000;
	static const int colourMask = whiteMask | blackMask;
    
public:
	static bool isColor(int piece, int color);

	static int color(int piece);

	static int pieceType(int piece);

    static bool isSlidingPiece(int piece);

};

#endif