#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "utils.h"

#include "chessboard.h"

#include "piece.h"


class Player {
    public: int color;
    string nom;
    virtual int demandersauvegarde() = 0;
    virtual bool decideMove(Chessboard & E, coord & ini, coord & sol) = 0;
    virtual Piece * choosePiece() = 0;
};

class Human: public Player {
    public: Piece * choosePiece();
    int demandersauvegarde() {
        return 0;
    }
    bool decideMove(Chessboard & E, coord & ini, coord & dest);
};

class Ai: public Player {
    public: int difficulty;
    int demandersauvegarde() {
        return this -> difficulty;
    }
    Ai(int diff) {
        this -> difficulty = diff;
    }
    Piece * choosePiece() {
        Piece * res = new Queen(this -> color);
        return res;
    }
    void miniMax(int depth, Chessboard & E, coord & ini, coord & sol);
    int findMin(int, Chessboard & );
    int findMax(int, Chessboard & );
    void ABminimax(int depth, Chessboard & E, coord & ini, coord & sol);
    int ABfindMin(int, Chessboard & , int, int);
    int ABfindMax(int, Chessboard & , int, int);
    int scoreChessboard(Chessboard & E) {
        int i, j;
        coord loc;
        int v = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                loc.x = i;
                loc.y = j;
                if ((E.pieceCheck(loc) && (E.getPiece(loc) -> player == this -> color))) {
                    v = v + E.getPiece(loc) -> value;
                }
                if ((E.pieceCheck(loc) && (E.getPiece(loc) -> player != this -> color))) {
                    v = v - E.getPiece(loc) -> value;
                }

            }
        }
        return (v);
    }
    bool decideMove(Chessboard & E, coord & ini, coord & sol) {
        if (this -> difficulty < 4) this -> miniMax(this -> difficulty, E, ini, sol);
        else this -> ABminimax(this -> difficulty, E, ini, sol);
        return true;
    }
};

#endif // PLAYER_H_INCLUDED