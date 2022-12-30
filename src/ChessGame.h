#ifndef GAME_H
#define GAME_H

#include <string>
#include "Bot.h"

class ChessGame{
    private:
        Board _board;
        Bot _bot;
        MoveGenerator _generator;
        const string STARTING_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w";
    public:
        ChessGame();
        ~ChessGame();

        // API
        void makeMove(std::string& move);
        std::string getMove();

        void debugBoard();
};

#endif