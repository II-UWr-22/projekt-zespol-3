#include "MoveGenerator.h"

void MoveGenerator::generateKingMoves(pair<int, int> square) {
    // Zuzia
}


void MoveGenerator::generateKnightMoves(pair<int, int> square) {
    // Szymon
}

void MoveGenerator::generateStraightMoves(pair<int, int> square) {
    // Rooks and Queen
    // Kalina
}

void MoveGenerator::generateDiagonalMoves(pair<int, int> square) {
    // Bishops and Queen
    // Kalina
}

void MoveGenerator::generatePawnMoves(pair<int, int> square) {
    int row = square.first, column = square.second;

    // Instead of checking color in loops we add change to row so -1 for white pawn and 1 for black pawns
    int change = friendlyColor == Piece::White ? -1 : 1;

    // Move forward if there is nothing in front
    if(inBounds({row+change, column}) && board[row+change][column] == Piece::None) {
        Move move = Move(row, column, row + change, column);
        moves.push_back(move);
    }

    // Capture 1
    if(inBounds({row+change, column+1}) && board[row+change][column+1] != Piece::None &&
    Piece::color(board[row+change][column+1]) != friendlyColor) {
        Move move = Move(row, column, row + change, column+1);
        moves.push_back(move);
    }

    // Capture 2
    if(inBounds({row+change, column-1}) && board[row+change][column-1] != Piece::None &&
       Piece::color(board[row+change][column-1]) != friendlyColor) {
        Move move = Move(row, column, row + change, column-1);
        moves.push_back(move);
    }

}

void MoveGenerator::generatePseudoLegalMoves() {
    init();
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            if(!Piece::isColor(board[row][col], friendlyColor))
                continue;
            switch(Piece::pieceType(board[row][col])){
                case Piece::King:
                    generateKingMoves({row,col});
                    break;
                case Piece::Pawn:
                    generatePawnMoves({row, col});
                    break;
                case Piece::Bishop:
                    generateDiagonalMoves({row, col});
                    break;
                case Piece::Knight:
                    generateKnightMoves({row, col});
                    break;
                case Piece::Rook:
                    generateStraightMoves({row, col});
                    break;
                case Piece::Queen:
                    generateDiagonalMoves({row, col});
                    generateStraightMoves({row, col});
                    break;
                default:
                    continue;
            }
        }
    }
}


void MoveGenerator::init() {
    moves = vector<Move>();
    friendlyColor = board.colorToMove;
}

vector<Move> MoveGenerator::generateMoves(const Board &p_board) {
    board = p_board;
    generatePseudoLegalMoves();

    // Piotrek
    for(Move &move : moves){
        // No need to check if castling was correct
        Board copy_board = board;
        copy_board.makeMove(move);
        // find king in copy_board and check if it is not checked
    }

    return moves;
}

bool MoveGenerator::isSquareThreatened(pair<int, int> square, Board& board) {
    int row = square.first, column = square.second;
    int piece = board[row][column];
    int color = Piece::color(piece);
    // Piotrek


    return false;
}

bool MoveGenerator::inBounds(pair<int, int> square) {
    int row = square.first, column = square.second;
    return (row >= 0 && row <= 7 && column >= 0 && column <= 7);
}

