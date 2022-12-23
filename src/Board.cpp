#include "Board.h"
Board::Board(const string& fen) {
    init();
    loadPositionFromFen(fen);
}

Board::Board(string&& fen) {
    init();
    loadPositionFromFen(fen);
}

Board::~Board() {

}

void Board::makeMove(Move& move) {

    _board[move.targetSquare.first][move.targetSquare.second] =
            _board[move.startingSquare.first][move.startingSquare.second];
    _board[move.startingSquare.first][move.startingSquare.second] = Piece::None;

    if(move.secondaryMove != nullptr){
        _board[move.secondaryMove->targetSquare.first][move.secondaryMove->targetSquare.second] =
                _board[move.secondaryMove->startingSquare.first][move.secondaryMove->startingSquare.second];
        _board[move.secondaryMove->startingSquare.first][move.secondaryMove->startingSquare.second] = Piece::None;
    }
    colorToMove = colorToMove == Piece::White ? Piece::Black : Piece::White;
    lastMove = move;
    hasMoved[move.startingSquare.first][move.startingSquare.second] = true;
}

void Board::loadPositionFromFen(const string& fen) {

}

array<int, 8> Board::operator[](int row) {
    return _board[row];
}


Board::Board() {
    init();
    for(int col = 0; col < 8; col++){
        _board[6][col] = Piece::Pawn | Piece::White;
        _board[1][col] = Piece::Pawn | Piece::Black;
    }
    _board[0][0] = _board[0][7] = Piece::Rook | Piece::Black;
    _board[7][0] = _board[7][7] = Piece::Rook | Piece::White;

    _board[0][1] = _board[0][6] = Piece::Knight | Piece::Black;
    _board[7][1] = _board[7][6] = Piece::Knight | Piece::White;

    _board[0][2] = _board[0][5] = Piece::Bishop | Piece::Black;
    _board[7][2] = _board[7][5] = Piece::Bishop | Piece::White;

    _board[0][3] = Piece::Queen | Piece::Black;
    _board[0][4] = Piece::King | Piece::Black;

    _board[7][3] = Piece::Queen | Piece::White;
    _board[7][4] = Piece::King | Piece::White;
}

Board::Board(const Board &other) {
    // Copy constructor
    _board = other._board;
    colorToMove = other.colorToMove;
    lastMove = other.lastMove;
    hasMoved = other.hasMoved;
}

void Board::init() {
    _board = array<array<int, 8>, 8>();
    colorToMove = Piece::White;
    lastMove = Move(0, 0, 0, 0);
    hasMoved = array<array<bool, 8>, 8>();
}



