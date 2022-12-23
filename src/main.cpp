#include "ChessGame.h"

int main()
{
    ChessGame game = ChessGame();
    while(1){
        game.debugBoard();

        std::string move;
        std::cin >> move;
        game.makeMove(move);
        std::string response = game.getMove();
        // std::cout << response << std::endl;
        // game.makeMove(response);
    }
}