#include "chessboard.h"

#include <cstdio>

#include "player.h"
#include "utils.h"

void Chessboard::forceMove(coord& c1, coord& c2) {
  if (this->Tab[c2.x][c2.y] != NULL) delete this->Tab[c2.x][c2.y];
  this->Tab[c2.x][c2.y] = this->Tab[c1.x][c1.y];
  this->Tab[c1.x][c1.y] = NULL;
}

void Chessboard::initializeChessboard() {
  int i, j;
  for (i = 1; i < 7; i++) {
    if ((i == 6) || (i == 1))
      for (j = 0; j < 8; j++) {
        this->Tab[i][j] = new Pawn((i % 2) + 1);
      }
    else
      for (j = 0; j < 8; j++) this->Tab[i][j] = NULL;
  }
  this->Tab[0][0] = new Rook(2);
  this->Tab[7][0] = new Rook(1);
  this->Tab[0][7] = new Rook(2);
  this->Tab[7][7] = new Rook(1);
  this->Tab[0][1] = new Knight(2);
  this->Tab[7][1] = new Knight(1);
  this->Tab[0][6] = new Knight(2);
  this->Tab[7][6] = new Knight(1);
  this->Tab[0][5] = new Bishop(2);
  this->Tab[7][5] = new Bishop(1);
  this->Tab[0][2] = new Bishop(2);
  this->Tab[7][2] = new Bishop(1);
  this->Tab[0][3] = new Queen(2);
  this->Tab[7][3] = new Queen(1);
  this->Tab[0][4] = new King(2);
  this->Tab[7][4] = new King(1);
  this->Tab[0][3] = new Queen(2);
  this->Tab[7][3] = new Queen(1);
  this->Tab[0][4] = new King(2);
  this->Tab[7][4] = new King(1);
}

Chessboard::Chessboard() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) this->Tab[i][j] = NULL;
}

void Chessboard::naiveMove(int n) {
  coord loc;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      loc.x = i;
      loc.y = j;
      if (this->pieceCheck(loc))
        if ((2 - (n) % 2) == this->getPiece(loc)->player)
          this->getPiece(loc)->naiveMove(loc, *this);
    }
}

Chessboard::~Chessboard() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) delete this->Tab[i][j];
}

Chessboard::Chessboard(const Chessboard& tab) {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (tab.Tab[i][j] == NULL)
        this->Tab[i][j] = NULL;
      else
        switch (tab.Tab[i][j]->value) {
          case 999:
            this->Tab[i][j] = new King(tab.Tab[i][j]->player);
            break;
          case 1:
            this->Tab[i][j] = new Pawn(tab.Tab[i][j]->player);
            break;
          case 4:
            this->Tab[i][j] = new Knight(tab.Tab[i][j]->player);
            break;
          case 3:
            this->Tab[i][j] = new Bishop(tab.Tab[i][j]->player);
            break;
          case 5:
            this->Tab[i][j] = new Rook(tab.Tab[i][j]->player);
            break;
          case 10:
            this->Tab[i][j] = new Queen(tab.Tab[i][j]->player);
            break;
        }
    }
}

void Chessboard::move(coord loc, coord dest, Player* qui) {
  this->forceMove(loc, dest);
  if ((this->getPiece(dest)->value == 1) && ((dest.x == 0) || (dest.x == 7))) {
    delete this->getPiece(dest);
    this->Tab[dest.x][dest.y] = qui->choosePiece();
  }
}

Piece* Chessboard::getPiece(coord loc) {
  if (loc.verifcoord()) return this->Tab[loc.x][loc.y];
}

void Chessboard::setPiece(Piece* input, coord loc) {
  this->Tab[loc.x][loc.y] = input;
}

bool Chessboard::pieceCheck(coord loc) {
  if (loc.verifcoord()) {
    if (Tab[loc.x][loc.y] == NULL)
      return false;
    else
      return true;
  }
}

void Chessboard::legalMoveOne(int i, int j, int nbtour) {
  cCell<coord>*temp, *pred = NULL;
  coord pos, pos2, loc;
  pos.x = i;
  pos.y = j;
  temp = this->getPiece(pos)->possibilites.head;
  while (this->getPiece(pos)->possibilites.head != NULL) {
    Chessboard rate(*this);
    rate.forceMove(pos, this->getPiece(pos)->possibilites.head->elt);
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        loc.x = i;
        loc.y = j;
        if (rate.pieceCheck(loc))
          if ((2 - (nbtour) % 2) == rate.getPiece(loc)->player)
            rate.getPiece(loc)->naiveMove(loc, rate);
      }

    pos2 = rate.findKing(nbtour + 1);
    if (rate.check(nbtour + 1, pos2)) {
      this->getPiece(pos)->possibilites.head = temp->succ;
      delete temp;
      temp = this->getPiece(pos)->possibilites.head;
    } else {
      break;
    }
  }
  while (temp != NULL) {
    Chessboard rate(*this);
    rate.forceMove(pos, temp->elt);
    coord loc;
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++) {
        loc.x = i;
        loc.y = j;
        if (rate.pieceCheck(loc))
          if ((2 - (nbtour) % 2) == rate.getPiece(loc)->player)
            rate.getPiece(loc)->naiveMove(loc, rate);
      }
    pos2 = rate.findKing(nbtour + 1);
    if (temp != NULL && !rate.check(nbtour + 1, pos2)) {
      pred = temp;
      temp = temp->succ;
    } else if (temp == NULL)
      break;
    else {
      pred->succ = temp->succ;
      delete temp;
      temp = pred->succ;
    }
  }
}

void Chessboard::legalMove(int nbtour) {
  int i, j;
  coord loc;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      loc.x = i;
      loc.y = j;
      if ((this->pieceCheck(loc)) &&
          (this->getPiece(loc)->player == (2 - (nbtour + 1) % 2)))
        this->legalMoveOne(i, j, nbtour);
    }
  }
}

void Chessboard::printChess() {
  int i, j;
  system("cls");
  printf("                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
         218, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196,
         194, 196, 191);
  for (i = 0; i < 8; i++) {
    printf("                               %d", 8 - i);
    for (j = 0; j < 8; j++) {
      int ch, q;
      printf("%c", 179);
      if (this->Tab[i][j] == NULL) {
        ch = 32;
        q = 0;
      } else {
        ch = this->Tab[i][j]->symbol;
        q = this->Tab[i][j]->player;
      }
    }
    if (i < 7) {
      printf("                                ");
    } else {
      printf("                                ");
    }
  }
  printf(
      "                                 A B C D E F G H \n                  ");
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      if (this->Tab[i][j] != NULL) {
        cout << "coord" << i << "  " << j << "  type  ";
        printf("%c", this->Tab[i][j]->symbol);
        cout << endl;
        this->Tab[i][j]->possibilites.printList();
        cout << endl;
      }
}

int Chessboard::check(int ntour, coord coking) {
  coord loc;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      loc.x = i;
      loc.y = j;
      if (this->pieceCheck(loc))
        if ((this->Tab[i][j]->player == ntour % 2 + 1))
          if ((this->Tab[i][j]->possibilites.findLinkedList(coking))) return 1;
    }
  return 0;
}

coord Chessboard::findKing(int ntour) {
  int i, j;
  coord co;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++) {
      co.x = i;
      co.y = j;
      if ((this->pieceCheck(co)) && (this->Tab[i][j]->value == 999) &&
          (this->Tab[i][j]->player == 2 - (ntour % 2)))
        return co;
    }
  return co;
}

int Chessboard::endGame(int ntour) {
  int i, j;
  coord loc;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      loc.x = i;
      loc.y = j;
      if (this->pieceCheck(loc))
        if ((2 - ntour % 2) == (this->Tab[i][j]->player)) {
          if (!(this->Tab[i][j]->possibilites.emptylist())) return (0);
        }
    }
  }
  return (1);
}