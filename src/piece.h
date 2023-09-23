#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "chessboard.h"
#include "utils.h"

class Piece {
 public:
  int player;
  int value;
  int symbol;
  liste<coord> possibilites;

  Piece(int j) {
    liste<coord> ini;
    player = j;
    possibilites = ini;
  }

  ~Piece() {}

  int verifyAlly(coord dest, Chessboard E);
  int verifyEnemy(coord dest, Chessboard E);
  virtual void naiveMove(coord source, Chessboard tab) = 0;
};

class Queen : public Piece {
 public:
  Queen(int j) : Piece(j) {
    value = 10;
    symbol = 81;
  }

  void naiveMove(coord source, Chessboard tab);
};

class Bishop : public Piece {
 public:
  Bishop(int j) : Piece(j) {
    value = 3;
    symbol = 66;
  }

  void naiveMove(coord source, Chessboard tab);
};

class Rook : public Piece {
 public:
  Rook(int j) : Piece(j) {
    value = 5;
    symbol = 82;
  }

  void naiveMove(coord source, Chessboard tab);
};

class Pawn : public Piece {
 public:
  Pawn(int j) : Piece(j) {
    value = 1;
    symbol = 80;
  }

  void naiveMove(coord source, Chessboard tab);
};

class Knight : public Piece {
 public:
  Knight(int j) : Piece(j) {
    value = 4;
    symbol = 75;
  }

  void naiveMove(coord source, Chessboard tab);
};

class King : public Piece {
 public:
  King(int j) : Piece(j) {
    value = 999;
    symbol = 244;
  }

  void naiveMove(coord source, Chessboard tab);
};

#endif  // PIECE_H_INCLUDED
