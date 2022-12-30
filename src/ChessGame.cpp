#include "ChessGame.h"

ChessGame::ChessGame() {
    _board = Board();
    _bot = Bot();
    _generator = MoveGenerator();
}

ChessGame::~ChessGame() {

}

void ChessGame::makeMove(std::string& move) {
    vector<Move> moves = _generator.generateMoves(_board);
    for(auto mv : moves){
        if(mv.toString() == move)
            _board.makeMove(mv);
    }
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

