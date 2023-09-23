#ifndef CHESSBOARD_H_INCLUDED
#define CHESSBOARD_H_INCLUDED

#include "utils.h"

#include <cstdio>

class Player;
class Piece;

class Chessboard {
private:
    Piece* Tab[8][8];

public:
    void printChess();
    int check(int ntour, coord coking);
    coord findKing(int ntour);
    int endGame(int ntour);
    void legalMove(Chessboard E, int ntour);
    void forceMove(coord& c1, coord& c2);
    void initializeChessboard();
    Chessboard();
    void naiveMove(int n);
    ~Chessboard();
    Chessboard(const Chessboard& tab);
    void move(coord loc, coord dest, Player* qui);
    Piece* getPiece(coord loc);
    void setPiece(Piece* input, coord loc);
    bool pieceCheck(coord loc);
    void legalMoveOne(int i, int j, int nbtour);
    void legalMove(int nbtour);
};

#endif // CHESSBOARD_H_INCLUDED