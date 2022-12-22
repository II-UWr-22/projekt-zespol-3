#include <iostream>

char R[100];

int main () {
    R['1'] = '8';
    R['2'] = '7';
    R['3'] = '6';
    R['4'] = '5';
    R['5'] = '4';
    R['6'] = '3';
    R['7'] = '2';
    R['8'] = '1';

    R['a'] = 'h';
    R['b'] = 'g';
    R['c'] = 'f';
    R['d'] = 'e';
    R['e'] = 'd';
    R['f'] = 'c';
    R['g'] = 'b';
    R['h'] = 'a';

    std::ios::sync_with_stdio(false);
    // flush po kazdym wywolaniu cout
    std::cout.setf(std::ios::unitbuf);

    std::string comm;
    while(true) { // game loop
        // std::cout << "# inside game loop\n";
        getline(std::cin, comm);
        // std::cout << "# comm is: " << comm << "\n";

        if(comm == "xboard") {
            std::cout << "feature reuse=0\n";
            std::cout << "feature sigint=0\n";
            std::cout << "feature name=Zespol3\n";
            std::cout << "feature variants=\"crazyhouse\"\n";
            std::cout << "feature debug=1\n";
            std::cout << "feature done=1\n";
        }
        else if(comm == "quit") {
            // std::cout << "# quit\n";
            return 0;
        }
        else if(comm.size() == 4) {
            // std::cout << "move g8a5\n";
            std::string move = "";
            for (int i = 0; i < 4; i++) {
                if (i % 2 == 0)
                    move += comm[i];
                else
                    move += R[comm[i]];
            }
            std::cout << "move " << move << "\n";
        }
    }

    return 0;
}

