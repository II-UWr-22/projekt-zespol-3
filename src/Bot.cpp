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
    for(auto m : legalMoves){
        if(Piece::pieceType(board[m.startingSquare.first][m.startingSquare.second]) == Piece::Knight){
            res += 3;
        }
        if(Piece::pieceType(board[m.startingSquare.first][m.startingSquare.second]) == Piece::Bishop){
            res += 3;
        }
        if(Piece::pieceType(board[m.startingSquare.first][m.startingSquare.second]) == Piece::Queen){
            res += 1;
        }
        res++;
    }
    return res;
}

int Bot::defense(Board &board, int depth){
    vector<Move> legalMoves = generator.generateMoves(board);
    int best = INT_MAX;
    for(auto m : legalMoves){
        auto new_board = board;
        new_board.makeMove(m);
        auto score = attack(new_board, depth-1);
        if(score < best){
            best = score;
            if(best < alt[depth]){
                alt[depth] = best;
            }
            if(best < alt[depth+1]){
                return best;
            }
        }
    }
    return best;
}

// void debugBoard(Board board) {
//     for(int i =0; i < 8; i++){
//         for(int j =0; j < 8; j++){
//             if(board[i][j])
//                 std::cout << board[i][j] << ' ';
//             else
//                 std::cout << "00" << ' ';
//         }
//         std::cout << '\n';
//     }
// }

int Bot::attack(Board &board, int depth){
    if(depth == 0){
        return evalPosition(board);
    }
    vector<Move> legalMoves = generator.generateMoves(board);
    int best = INT_MIN;
    for(auto m : legalMoves){
        auto new_board = board;
        new_board.makeMove(m);
        auto score = defense(new_board, depth-1);
        if(score > best){
            best = score;
            if(best > alt[depth]){
                alt[depth] = best;
            }
            if(best > alt[depth+1]){
                return best;
            }
        }
    }
    return best;
}

Move Bot::bestMove(Board board) {
    int depth = 10;
    for(int i=0; i<(int)alt.size(); i++){
        if(i&1){
            alt[i] = INT_MAX;
        }
        else{
            alt[i] = INT_MIN;
        }
    }
    vector<Move> legalMoves = generator.generateMoves(board);
    srand(time(0));
    random_shuffle(legalMoves.begin(), legalMoves.end());
    pair<Move, int> best = std::make_pair(Move(), INT_MIN);
    for(auto m : legalMoves){
        auto new_board = board;
        new_board.makeMove(m);
        auto score = defense(new_board, depth-1);
        //std::cout << "ruch: " << m.toString() << ": " << score << "\n";
        if(score > best.second){
            best = std::make_pair(m, score);
            if(best.second > alt[depth]){
                alt[depth] = best.second;
            }
        }
    }
    return best.first;
}

Bot::Bot() {
    generator = MoveGenerator();
}
