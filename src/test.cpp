
#include "test.h"

void printBoard(Board& board) {
    for(int i =0; i < 8; i++){
        for(int j =0; j < 8; j++){
            if(board[i][j])
                std::cout << board[i][j] << ' ';
            else
                std::cout << "00" << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


unsigned long long countPosition(int depth, MoveGenerator& g, Board& board, int curr){
    if(curr == depth-1){
        return g.generateMoves(board).size();
    }
    auto mvs = g.generateMoves(board);
    unsigned long long cnt = 0;
    for(Move mv : mvs){
        Board copyBoard = board;
        copyBoard.makeMove(mv);
        cnt += countPosition(depth, g, copyBoard, curr+1);
    }
    return cnt;
}

void test(unsigned long long result, int number, int depth){
    Board board = Board();
    MoveGenerator generator = MoveGenerator();
    unsigned long long test = countPosition(depth, generator, board, 0);
    printf("TEST %d:", number);
    if(test == result)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("%llu positions found expected: %llu\n", test, result);
}

void test(unsigned long long result, int number, int depth, const string& fen){
    Board board = Board(fen);
    MoveGenerator generator = MoveGenerator();
    unsigned long long test = countPosition(depth, generator, board, 0);
    printf("TEST %d:", number);
    if(test == result)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("%llu positions found expected: %llu\n", test, result);
}


void testMoveGeneration(){
    test(400llu, 1, 2); // after 2 half moves
    test(197281llu, 2, 4); // after 4 half moves
    test(4865609llu, 3, 5); // after 5 half moves
    test(44llu, 5, 1, "2kr3r/p1ppqpb1/bn2QnN1/3P4/1p2P3/2N5/PPPBBPPP/R3K2R b");
}





