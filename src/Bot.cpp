#include "Bot.h"

double Bot::evalPosition(Board board) {
    return 0;
}

Move Bot::search(Board board, int depth) {
    vector<Move> legalMoves = generator.generateMoves(board);
    for(Move move : legalMoves){
        // printing purely for debugging function that generate all moves, can be removed
        std::cout << move.toString() << ' ';
    }
    std::cout << '\n';
    double eval = evalPosition(board);
    return Move();
}

Move Bot::bestMove(Board board) {
    Move b = search(board, 6);
    return Move();
}

Bot::Bot() {
    generator = MoveGenerator();
}
