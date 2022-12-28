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
        moves.push_back(move);
        // Move Rook
        Move s_move = Move(castling_row,7,castling_row, 5);
        move.secondaryMove = &s_move;
    }

    // Long castling
    if(!board.hasMoved[castling_row][4] && !board.hasMoved[castling_row][0] && 
    board[castling_row][1] == Piece::None && board[castling_row][2] == Piece::None &&
    board[castling_row][3] == Piece::None &&
    !isSquareThreatened({castling_row, 3}, board) &&
    !isSquareThreatened({castling_row, 4}, board))
    {
        Move move = Move(castling_row,4,castling_row,2);
        moves.push_back(move);
        // Move Rook
        Move s_move = Move(castling_row, 0, castling_row, 3);
        move.secondaryMove = &s_move;
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

    // Move forward if there is nothing in front
    if(inBounds({row+change, column}) && board[row+change][column] == Piece::None) {
        Move move = Move(row, column, row + change, column);
        moves.push_back(move);
    }

    // Capture 1
    if(inBounds({row+change, column+1}) && board[row+change][column+1] != Piece::None &&
    Piece::color(board[row+change][column+1]) != friendlyColor) {
        Move move = Move(row, column, row + change, column+1);
        moves.push_back(move);
    }

    // Capture 2
    if(inBounds({row+change, column-1}) && board[row+change][column-1] != Piece::None &&
       Piece::color(board[row+change][column-1]) != friendlyColor) {
        Move move = Move(row, column, row + change, column-1);
        moves.push_back(move);
    }

    // Move two steps forward
    if(inBounds({row+2*change, column}) && board[row+2*change][column] == Piece::None &&
       board[row+1*change][column] == Piece::None) {
        Move move = Move(row, column, row + 2*change, column);
        moves.push_back(move);
    }

    // En Passant 1 
    if(board.lastMove.startingSquare==std::make_pair(row+2*change, column+1) &&
       board.lastMove.targetSquare==std::make_pair(row, column+1) &&
       Piece::pieceType(board[row][column+1])==Piece::Pawn && 
       Piece::color(board[row][column+1])!=friendlyColor){
        Move move = Move(row, column, row + change, column+1);
        moves.push_back(move);
        // Opponent's Pawn disappears
        Move s_move = Move(row, column+1, row, column+1);
        move.secondaryMove = &s_move;
    }

    // En Passant 2 
    if(board.lastMove.startingSquare==std::make_pair(row+2*change, column-1) &&
       board.lastMove.targetSquare==std::make_pair(row, column-1) &&
       Piece::pieceType(board[row][column-1])==Piece::Pawn && 
       Piece::color(board[row][column-1])!=friendlyColor){
        Move move = Move(row, column, row + change, column-1);
        moves.push_back(move);
        // Opponent's Pawn disappears
        Move s_move = Move(row, column-1, row, column-1);
        move.secondaryMove = &s_move;
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
    for(Move &move : moves){
        // No need to check if castling was correct
        Board copy_board = board;
        copy_board.makeMove(move);
        // find king in copy_board and check if it is not checked
    }

    return moves;
}

bool MoveGenerator::isSquareThreatened(pair<int, int> square, Board& board) {
    int row = square.first, column = square.second;
    int piece = board[row][column];
    int color = Piece::color(piece);
    // Piotrek


    return false;
}

bool MoveGenerator::inBounds(pair<int, int> square) {
    int row = square.first, column = square.second;
    return (row >= 0 && row <= 7 && column >= 0 && column <= 7);
}
