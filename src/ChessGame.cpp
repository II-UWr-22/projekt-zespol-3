#include "ChessGame.h"

ChessGame::ChessGame() {
    _board = Board();
    _bot = Bot();
}

ChessGame::~ChessGame() {

}

void ChessGame::makeMove(std::string move) {
    Move m = Move(move);
    _board.makeMove(m);

}

string ChessGame::getMove() {
    string bestMove = _bot.bestMove(_board).toString();
    return bestMove;
}

void ChessGame::debugBoard() {
    for(int i =0; i < 8; i++){
        for(int j =0; j < 8; j++){
            if(_board[i][j])
                std::cout << _board[i][j] << ' ';
            else
                std::cout << "00" << ' ';
        }
        std::cout << '\n';
    }
}

