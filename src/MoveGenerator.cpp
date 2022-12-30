#include "MoveGenerator.h"

void MoveGenerator::generateKingMoves(pair<int, int> square) {
    int row = square.first, column = square.second;

    int dr[8]={1,1,0,-1, 1,-1,-1, 0};
    int dc[8]={1,0,1,-1,-1, 1, 0,-1};

    for(int i=0; i<8; ++i)
    {
        int new_row = row+dr[i], new_column = column+dc[i];
        if(inBounds({new_row, new_column}))
        {
            // Move (and capture if opposite color)
            if(board[new_row][new_column] == Piece::None ||
            Piece::color(board[new_row][new_column]) != friendlyColor)
            {
                Move move = Move(row, column, new_row, new_column);
                moves.push_back(move);
            }
        }
    }

    int castling_row = (friendlyColor == Piece::White)? 7 : 0;

    // Short castling
    if(!board.hasMoved[castling_row][4] && !board.hasMoved[castling_row][7] && 
    board[castling_row][5] == Piece::None && board[castling_row][6] == Piece::None &&
    !isSquareThreatened({castling_row, 4}, board) &&
    !isSquareThreatened({castling_row, 5}, board))
    {
        Move move = Move(castling_row,4,castling_row,6);
        // Move Rook
        move.secondaryMove = new Move(castling_row,7,castling_row, 5);;
        moves.push_back(move);
    }

    // Long castling
    if(!board.hasMoved[castling_row][4] && !board.hasMoved[castling_row][0] && 
    board[castling_row][1] == Piece::None && board[castling_row][2] == Piece::None &&
    board[castling_row][3] == Piece::None &&
    !isSquareThreatened({castling_row, 3}, board) &&
    !isSquareThreatened({castling_row, 4}, board))
    {
        Move move = Move(castling_row,4,castling_row,2);
        // Move Rook
        move.secondaryMove = new Move(castling_row, 0, castling_row, 3);
        moves.push_back(move);
    }
}


void MoveGenerator::generateKnightMoves(pair<int, int> square) {
    // Szymon
    
    int row = square.first, column = square.second;
    
    int X[] = {-2, -2, 2, 2, -1, 1, -1, 1};
    int Y[] = {1, -1, 1, -1, 2, 2, -2, -2};
    
    for(int i=0; i<8; i++){
        int row_after = row + X[i], column_after = column + Y[i];

        if(!inBounds({row_after, column_after})) continue;
        
        if(board[row_after][column_after] == Piece::None){
            Move move = Move(row, column, row_after, column_after);
            moves.push_back(move);
        }
        else if(Piece::color(board[row_after][column_after]) != friendlyColor){
            Move move = Move(row, column, row_after, column_after);
            moves.push_back(move);
        }
    }
}

void MoveGenerator::generateStraightMoves(pair<int, int> square) {
    // Rooks and Queen
    // Kalina
    int row, column, ROW = square.first, COLUMN = square.second;
    int RowChange[4] = {1, 0, -1, 0};
    int ColumnChange[4] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++) {
        int rowChange = RowChange[i];
        int columnChange = ColumnChange[i];
        row = ROW;
        column = COLUMN;
        while (1) {
            if (inBounds({ row + rowChange, column + columnChange })) {
                if (board[row + rowChange][column + columnChange] == Piece::None) {
                    Move move = Move(ROW, COLUMN, row + rowChange, column + columnChange);
                    moves.push_back(move);
                }
                else {
                    if (Piece::color(board[row + rowChange][column + columnChange]) != friendlyColor) {
                        Move move = Move(ROW, COLUMN, row + rowChange, column + columnChange);
                        moves.push_back(move);
                        break;
                    }
                    else
                        break;
                }
            }
            else
                break;

            row += rowChange;
            column += columnChange;
        }

    }
}

void MoveGenerator::generateDiagonalMoves(pair<int, int> square) {
    // Bishops and Queen
    // Kalina
    int row, column, ROW = square.first, COLUMN = square.second;
    int RowChange[4] = { 1, 1, -1, -1 };
    int ColumnChange[4] = { 1, -1, -1, 1 };

    for (int i = 0; i < 4; i++) {
        int rowChange = RowChange[i];
        int columnChange = ColumnChange[i];
        row = ROW;
        column = COLUMN;
        while (1) {
            if (inBounds({ row + rowChange, column + columnChange })) {
                if (board[row + rowChange][column + columnChange] == Piece::None) {
                    Move move = Move(ROW, COLUMN, row + rowChange, column + columnChange);
                    moves.push_back(move);
                }
                else {
                    if (Piece::color(board[row + rowChange][column + columnChange]) != friendlyColor) {
                        Move move = Move(ROW, COLUMN, row + rowChange, column + columnChange);
                        moves.push_back(move);
                        break;
                    }
                    else
                        break;
                }
            }
            else
                break;

            row += rowChange;
            column += columnChange;
        }

    }
}

void MoveGenerator::generatePawnMoves(pair<int, int> square) {
    int row = square.first, column = square.second;

    // Instead of checking color in loops we add change to row so -1 for white pawn and 1 for black pawns
    int change = friendlyColor == Piece::White ? -1 : 1;

    int finalRow = friendlyColor == Piece::White ? 0 : 7;
    // Move forward if there is nothing in front and promote if final row
    if(inBounds({row+change, column}) && board[row+change][column] == Piece::None) {
        if(row + change == finalRow){
            for(int piece = Piece::Knight; piece <= Piece::Queen; piece++){
                Move move = Move(row, column, row + change, column);
                move.promotion = piece | friendlyColor;
                moves.push_back(move);
            }
        }
        else
        {
            Move move = Move(row, column, row + change, column);
            moves.push_back(move);
        }
    }

    // Capture 1
    if(inBounds({row+change, column+1}) && board[row+change][column+1] != Piece::None &&
    Piece::color(board[row+change][column+1]) != friendlyColor) {
        if(row + change == finalRow){
            for(int piece = Piece::Knight; piece <= Piece::Queen; piece++){
                Move move = Move(row, column, row + change, column+1);
                move.promotion = piece | friendlyColor;
                moves.push_back(move);
            }
        }
        else{
            Move move = Move(row, column, row + change, column+1);
            moves.push_back(move);
        }
    }

    // Capture 2
    if(inBounds({row+change, column-1}) && board[row+change][column-1] != Piece::None &&
       Piece::color(board[row+change][column-1]) != friendlyColor) {
        if(row + change == finalRow){
            for(int piece = Piece::Knight; piece <= Piece::Queen; piece++){
                Move move = Move(row, column, row + change, column-1);
                move.promotion = piece | friendlyColor;
                moves.push_back(move);
            }
        }
        else{
            Move move = Move(row, column, row + change, column-1);
            moves.push_back(move);
        }

    }

    // Move two steps forward
    if(inBounds({row+2*change, column}) && board[row+2*change][column] == Piece::None &&
       board[row+1*change][column] == Piece::None && !board.hasMoved[row][column]) {
        Move move = Move(row, column, row + 2*change, column);
        moves.push_back(move);
    }

    // En Passant 1 
    if(board.lastMove.startingSquare==std::make_pair(row+2*change, column+1) &&
       board.lastMove.targetSquare==std::make_pair(row, column+1) &&
       Piece::pieceType(board[row][column+1])==Piece::Pawn && 
       Piece::color(board[row][column+1])!=friendlyColor){
        Move move = Move(row, column, row + change, column+1);
        // Opponent's Pawn disappears
        move.secondaryMove = new Move(row, column+1, row, column+1);
        moves.push_back(move);
    }

    // En Passant 2 
    if(board.lastMove.startingSquare==std::make_pair(row+2*change, column-1) &&
       board.lastMove.targetSquare==std::make_pair(row, column-1) &&
       Piece::pieceType(board[row][column-1])==Piece::Pawn && 
       Piece::color(board[row][column-1])!=friendlyColor){
        Move move = Move(row, column, row + change, column-1);
        // Opponent's Pawn disappears
        move.secondaryMove = new Move(row, column-1, row, column-1);
        moves.push_back(move);
    }
}

void MoveGenerator::generatePseudoLegalMoves() {
    init();
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            if(!Piece::isColor(board[row][col], friendlyColor))
                continue;
            switch(Piece::pieceType(board[row][col])){
                case Piece::King:
                    generateKingMoves({row,col});
                    break;
                case Piece::Pawn:
                    generatePawnMoves({row, col});
                    break;
                case Piece::Bishop:
                    generateDiagonalMoves({row, col});
                    break;
                case Piece::Knight:
                    generateKnightMoves({row, col});
                    break;
                case Piece::Rook:
                    generateStraightMoves({row, col});
                    break;
                case Piece::Queen:
                    generateDiagonalMoves({row, col});
                    generateStraightMoves({row, col});
                    break;
                default:
                    continue;
            }
        }
    }
}


void MoveGenerator::init() {
    moves = vector<Move>();
    friendlyColor = board.colorToMove;
}

vector<Move> MoveGenerator::generateMoves(const Board &p_board) {
    board = p_board;
    generatePseudoLegalMoves();

    // Piotrek
    vector<int> ROW, COLUMN;
    if(friendlyColor == Piece::White) ROW = {7,6,5,4,3,2,1,0}, COLUMN = {4,3,5,2,6,1,7,0};
    else ROW = {0,1,2,3,4,5,6,7}, COLUMN = {3,4,2,5,1,6,0,7};
    vector<bool> llegal(moves.size());
    int it = 0;
    for(Move &move : moves){
        // No need to check if castling was correct
        Board copy_board = board;
        copy_board.makeMove(move);
        // find king in copy_board and check if it is not checked
        int rowKing = -1, columnKing = -1;
        
        for(int row : ROW) {
            for(int column : COLUMN) {
                if(Piece::pieceType(copy_board[row][column]) == Piece::King &&
                Piece::color(copy_board[row][column]) == friendlyColor ) rowKing = row, columnKing = column;
                if(rowKing != -1 && columnKing != -1) break;
            }
            if(rowKing != -1 && columnKing != -1) break;
        }
        if(MoveGenerator::isSquareThreatened({rowKing, columnKing}, copy_board) == true) llegal[it] = false;
        else llegal[it] = true;
        it++;
    }

    vector<Move> moves2;
    for(int i = 0; i < moves.size(); i++){
        if(llegal[i]) moves2.push_back(moves[i]);
    }

    return moves2;
}

bool MoveGenerator::isSquareThreatened(pair<int, int> square, Board& board) {
    int row = square.first, column = square.second;
    bool answer = false;

    //checking for pawns
    int change = friendlyColor == Piece::White? -1 : 1;
    if(inBounds({row+change, column+1}) && Piece::pieceType(board[row+change][column+1]) == Piece::Pawn
    && Piece::color(board[row+change][column+1]) != friendlyColor ) answer = 1;

    if(inBounds({row+change, column-1}) && Piece::pieceType(board[row+change][column-1]) == Piece::Pawn
    && Piece::color(board[row+change][column-1]) != friendlyColor ) answer = 1;

    //checking for king
    vector<pair<int, int>> directions{{0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    for(auto current : directions) {
        int currentRow = row+current.first, currentColumn = column+current.second; 
        if(inBounds({currentRow, currentColumn}) && Piece::pieceType(board[currentRow][currentColumn]) == Piece::King 
        && Piece::color(board[currentRow][currentColumn]) != friendlyColor) answer = 1;
    }
    //checking for knights
    directions.clear();
    directions = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
    for(auto current : directions) {
        int currentRow = row+current.first, currentColumn = column+current.second; 
        if(inBounds({currentRow, currentColumn}) && Piece::pieceType(board[currentRow][currentColumn]) == Piece::Knight 
        && Piece::color(board[currentRow][currentColumn]) != friendlyColor) answer = 1;
    }
    //checking for bishops/queen
    directions.clear();
    directions = {{1,1},{1,-1},{-1,1},{-1,-1}};
    for(auto current : directions) {
        int currentRow = row+current.first, currentColumn = column+current.second;
        while(inBounds({currentRow, currentColumn}) && board[currentRow][currentColumn] == Piece::None)
            currentRow += current.first, currentColumn += current.second;
        if(inBounds({currentRow, currentColumn}) && Piece::color(board[currentRow][currentColumn]) != friendlyColor &&
        (Piece::pieceType(board[currentRow][currentColumn]) == Piece::Bishop || Piece::pieceType(board[currentRow][currentColumn]) == Piece::Queen)) answer = 1;
    }
    //checking for rooks/queen
    directions.clear();
    directions = {{1,0},{-1,0},{0,1},{0,-1}};
    for(auto current : directions) {
        int currentRow = row+current.first, currentColumn = column+current.second;
        while(inBounds({currentRow, currentColumn}) && board[currentRow][currentColumn] == Piece::None)
            currentRow += current.first, currentColumn += current.second;
        if(inBounds({currentRow, currentColumn}) && Piece::color(board[currentRow][currentColumn]) != friendlyColor &&
        (Piece::pieceType(board[currentRow][currentColumn]) == Piece::Rook || Piece::pieceType(board[currentRow][currentColumn]) == Piece::Queen)) answer = 1;
    }

    return answer;
}

bool MoveGenerator::inBounds(pair<int, int> square) {
    int row = square.first, column = square.second;
    return (row >= 0 && row <= 7 && column >= 0 && column <= 7);
}
