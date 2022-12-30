#include "ChessGame.h"

int main()
{
    std::ios::sync_with_stdio(false);
    // flush po kazdym wywolaniu cout
    std::cout.setf(std::ios::unitbuf);

    ChessGame game = ChessGame();

    std::string comm;
    while(true) { // game loop
        // std::cout << "# inside game loop\n";
        getline(std::cin, comm);
        // std::cout << "# comm is: " << comm << "\n";

        if(comm == "xboard") {
            std::cout << "feature reuse=0\n";
            std::cout << "feature sigint=0\n";
            std::cout << "feature name=Zespol3\n";
            std::cout << "feature variants=\"normal\"\n";
            std::cout << "feature debug=1\n";
            std::cout << "feature done=1\n";
        }
        else if(comm == "quit") {
            return 0;
        }
        else if(comm == "draw"){
            std::cout << "offer draw";
        }
        else if(comm.substr(0,5) == "level"){
            continue;
        }
        else if(comm == "post"){
            continue;
        }
        else if (comm == "hard") {
            continue;
        }
        else if (comm == "white") {
            continue;
        }
        else if (comm == "black") {
            continue;
        }
        else if (comm == "force") {
            continue;
        }
        else if(comm.size() == 4 or comm.size() == 5) {
            game.makeMove(comm);
            std::string response = game.getMove();
            std::cout << "move " << response << std::endl;
            game.makeMove(response);
        }
    }
}
