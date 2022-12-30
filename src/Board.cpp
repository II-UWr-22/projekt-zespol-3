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
    if(move.promotion != Piece::None)
        _board[move.targetSquare.first][move.targetSquare.second] = move.promotion;
    colorToMove = colorToMove == Piece::White ? Piece::Black : Piece::White;
    lastMove = move;
    hasMoved[move.startingSquare.first][move.startingSquare.second] = true;
    hasMoved[move.targetSquare.first][move.targetSquare.second] = true;
}

void Board::loadPositionFromFen(const string& fen) {
    int col = 0;
    int row = 0;
    
    const int board_fen_end = fen.find(' ') == string::npos ? fen.size() : fen.find(' ');
    for (int i = 0; i < board_fen_end; i++){
        if (fen[i] == '/') {
            row++;
            col = 0;
        }
        else if ('0' <= fen[i] and fen[i] <= '9') {
            col += (int)(fen[i] - '0');
        }
        else if ('a' <= fen[i] and fen[i] <= 'z') {
            _board[row][col] = Piece::Black | Piece::pieceSymbol.at(fen[i]);
            col++;
        }
        else if ('A' <= fen[i] and fen[i] <= 'Z') {
            _board[row][col] = Piece::White | Piece::pieceSymbol.at(fen[i] + ((int)'a' - (int)'A'));
            col++;
        }
    }

    if (board_fen_end + 1 < (int)fen.size()) {
        if (fen[board_fen_end + 1] == 'w')
            colorToMove = Piece::White;
        else
            colorToMove = Piece::Black;
    }
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



