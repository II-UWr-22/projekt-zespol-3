#include "ChessGame.h"

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.setf(std::ios::unitbuf);

    ChessGame game = ChessGame();

    std::string move;
    while(1) {
        getline(std::cin, move);
        game.makeMove(move);
        std::string response = game.getMove();
        std::cout << "move " << response << std::endl;
        game.makeMove(response);
    }
}


