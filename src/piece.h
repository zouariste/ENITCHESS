#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "utils.h"
#include "chessboard.h"

class Piece {
public:
    int player;
    int value;
    int symbole;
    liste<coord> possibilites;

    Piece(int j) {
        liste<coord> ini;
        player = j;
        possibilites = ini;
    }

    ~Piece() {}

    int verifami(coord dest, Chessboard E);
    int verifennemi(coord dest, Chessboard E);
    virtual void naiveMove(coord source, Chessboard tab) = 0;
};

class Queen : public Piece {
public:
    Queen(int j) : Piece(j) {
        value = 10;
        symbole = 81;
    }

    void naiveMove(coord source, Chessboard tab);
};

class Bishop : public Piece {
public:
    Bishop(int j) : Piece(j) {
        value = 3;
        symbole = 66;
    }

    void naiveMove(coord source, Chessboard tab);
};

class Rook : public Piece {
public:
    Rook(int j) : Piece(j) {
        value = 5;
        symbole = 82;
    }

    void naiveMove(coord source, Chessboard tab);
};

class Pawn : public Piece {
public:
    Pawn(int j) : Piece(j) {
        value = 1;
        symbole = 80;
    }

    void naiveMove(coord source, Chessboard tab);
};

class Knight : public Piece {
public:
    Knight(int j) : Piece(j) {
        value = 4;
        symbole = 75;
    }

    void naiveMove(coord source, Chessboard tab);
};

class King : public Piece {
public:
    King(int j) : Piece(j) {
        value = 999;
        symbole = 244;
    }

    void naiveMove(coord source, Chessboard tab);
};

#endif // PIECE_H_INCLUDED
