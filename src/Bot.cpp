#include "Bot.h"
#include <limits.h>
#include <algorithm>
#include <ctime>

int Bot::evalPosition(Board &board) {
    int res = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(Piece::color(board[i][j]) == board.colorToMove){
                res += value[Piece::pieceType(board[i][j])]*1000;
            }
            else{
                res -= value[Piece::pieceType(board[i][j])]*1000;
            }
        }
    }

    vector<Move> legalMoves = generator.generateMoves(board);
    res += (int)legalMoves.size();
    return res;
}

int Bot::defense(Board &board, int depth, int alpha){
    vector<Move> legalMoves = generator.generateMoves(board);
    int beta = INT_MAX;
    for(auto m : legalMoves){
        auto new_board = board;
        new_board.makeMove(m);
        auto score = attack(new_board, depth-1, beta);
        if(score < beta){
            beta = score;
        }
        if(beta <= alpha){
            break;
        }
    }
    return beta;
}

int Bot::attack(Board &board, int depth, int beta){
    if(depth == 0){
        return evalPosition(board);
    }
    vector<Move> legalMoves = generator.generateMoves(board);
    int alpha = INT_MIN;
    for(auto m : legalMoves){
        auto new_board = board;
        new_board.makeMove(m);
        auto score = defense(new_board, depth-1, alpha);
        if(score > alpha){
            alpha = score;
        }
        if(alpha >= beta){
            break;
        }
    }
    return alpha;
}

Move Bot::bestMove(Board board) {
    int depth = 4, alpha = INT_MIN;
    vector<Move> legalMoves = generator.generateMoves(board);
    srand(time(0));
    random_shuffle(legalMoves.begin(), legalMoves.end());
    Move best = Move();
    for(auto m : legalMoves){
        auto new_board = board;
        new_board.makeMove(m);
        auto score = defense(new_board, depth-1, alpha);
        if(score > alpha){
            alpha = score;
            best = m;
        }
    }
    return best;
}

Bot::Bot() {
    generator = MoveGenerator();
}
