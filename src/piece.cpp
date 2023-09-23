#include "piece.h"

#include <cstdio>

#include "utils.h"

int Piece::verifyAlly(coord dest, Chessboard E) {
  if (E.pieceCheck(dest)) {
    if (this->player == (E.getPiece(dest))->player)
      return (1);
    else
      return (0);
  } else
    return (0);
}

int Piece::verifyEnemy(coord dest, Chessboard E) {
  if (E.pieceCheck(dest)) {
    if (this->player != E.getPiece(dest)->player)
      return (1);
    else
      return (0);
  } else
    return (0);
}

void Queen::naiveMove(coord source, Chessboard Tab) {
  int i = source.x, j = source.y;
  int x, y;
  coord pos;
  x = 1, y = 1;
  this->possibilites.~liste();
  while (1) {
    pos.x = i + x;
    pos.y = j + y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1, y = 1;
  while (1) {
    pos.x = i - x;
    pos.y = j - y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1, y = 1;
  while (1) {
    pos.x = i + x;
    pos.y = j - y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1, y = 1;
  while (1) {
    pos.x = i - x;
    pos.y = j + y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1;
  while (1) {
    pos.x = i + x;
    pos.y = j;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1;
  while (1) {
    pos.x = i - x;
    pos.y = j;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  y = 1;
  while (1) {
    pos.x = i;
    pos.y = j + y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  y = 1;
  while (1) {
    pos.x = i;
    pos.y = j - y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
}

void Bishop::naiveMove(coord source, Chessboard Tab) {
  int i = source.x, j = source.y;
  int x, y;
  coord pos;
  x = 1, y = 1;
  this->possibilites.~liste();
  while (1) {
    pos.x = i + x;
    pos.y = j + y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1, y = 1;
  while (1) {
    pos.x = i - x;
    pos.y = j - y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1, y = 1;
  while (1) {
    pos.x = i + x;
    pos.y = j - y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1, y = 1;
  while (1) {
    pos.x = i - x;
    pos.y = j + y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
}

void Rook::naiveMove(coord source, Chessboard Tab) {
  int i = source.x, j = source.y;
  int x, y;
  coord pos;
  x = 1, y = 1;
  this->possibilites.~liste();
  while (1) {
    pos.x = i + x;
    pos.y = j;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  x = 1;
  while (1) {
    pos.x = i - x;
    pos.y = j;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  y = 1;
  while (1) {
    pos.x = i;
    pos.y = j + y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
  y = 1;
  while (1) {
    pos.x = i;
    pos.y = j - y;
    if (pos.verifcoord()) {
      if (this->verifyAlly(pos, Tab)) break;

      if (this->verifyEnemy(pos, Tab)) {
        this->possibilites.addToList(pos);
        break;
      }
      this->possibilites.addToList(pos);
      x += 1;
      y += 1;
    } else
      break;
  }
}

void Pawn::naiveMove(coord source, Chessboard Tab) {
  int i = source.x, j = source.y;
  coord pos;
  this->possibilites.~liste();
  if (this->player == 1) {
    pos.x = i - 1;
    pos.y = j;
    if ((!this->verifyAlly(pos, Tab)) && (!this->verifyEnemy(pos, Tab)) &&
        pos.verifcoord()) {
      this->possibilites.addToList(pos);
      pos.x = i - 2;
      pos.y = j;
      if ((i == 6) && (!this->verifyAlly(pos, Tab)) &&
          (!this->verifyEnemy(pos, Tab)))
        this->possibilites.addToList(pos);
    }
    pos.x = i - 1;
    pos.y = j + 1;
    if ((this->verifyEnemy(pos, Tab)) && pos.verifcoord())
      this->possibilites.addToList(pos);
    pos.x = i - 1;
    pos.y = j - 1;
    if ((this->verifyEnemy(pos, Tab)) && pos.verifcoord())
      this->possibilites.addToList(pos);
  }
  if (this->player == 2) {
    pos.x = i + 1;
    pos.y = j;
    if ((!this->verifyAlly(pos, Tab)) && (!this->verifyEnemy(pos, Tab)) &&
        pos.verifcoord()) {
      this->possibilites.addToList(pos);
      pos.x = i + 2;
      pos.y = j;
      if ((i == 1) && (!this->verifyAlly(pos, Tab)) &&
          (!this->verifyEnemy(pos, Tab)))
        this->possibilites.addToList(pos);
    }
    pos.x = i + 1;
    pos.y = j + 1;
    if ((this->verifyEnemy(pos, Tab)) && pos.verifcoord())
      this->possibilites.addToList(pos);
    pos.x = i + 1;
    pos.y = j - 1;
    if ((this->verifyEnemy(pos, Tab)) && pos.verifcoord())
      this->possibilites.addToList(pos);
  }
}

void Knight::naiveMove(coord source, Chessboard Tab) {
  int i = source.x, j = source.y;
  this->possibilites.~liste();
  coord pos;
  pos.x = i + 1;
  pos.y = j + 2;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 1;
  pos.y = j + 2;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i + 1;
  pos.y = j - 2;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 1;
  pos.y = j - 2;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i + 2;
  pos.y = j + 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i + 2;
  pos.y = j - 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 2;
  pos.y = j + 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 2;
  pos.y = j - 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
}

void King::naiveMove(coord source, Chessboard Tab) {
  int i = source.x, j = source.y;
  this->possibilites.~liste();
  coord pos;
  pos.x = i + 1;
  pos.y = j + 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i;
  pos.y = j + 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 1;
  pos.y = j + 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 1;
  pos.y = j;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i + 1;
  pos.y = j;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i - 1;
  pos.y = j - 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i;
  pos.y = j - 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
  pos.x = i + 1;
  pos.y = j - 1;
  if ((!this->verifyAlly(pos, Tab)) && pos.verifcoord())
    this->possibilites.addToList(pos);
}