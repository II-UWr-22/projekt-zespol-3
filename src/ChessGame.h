#include <string>
#include "Bot.h"

class ChessGame{
    private:
        Board _board;
        Bot _bot;
        const string STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    public:
        ChessGame();
        ~ChessGame();

        // API
        void makeMove(std::string move);
        std::string getMove();

        void debugBoard();
};