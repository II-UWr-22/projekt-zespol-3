#ifndef TEST_H
#define TEST_H

#include <cstdio>
#include "ChessGame.h"

unsigned long long countPosition(int depth, MoveGenerator& g, const Board& board, int curr);
void test(unsigned long long result, int number, int depth);
void testMoveGeneration();
void printBoard();
#endif



