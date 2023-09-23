#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <time.h>
#include <unistd.h>

#include <iostream>

#include "chessboard.h"
#include "player.h"
#include "utils.h"

class Game {
 public:
  Chessboard chessboard;
  Player* white;
  Player* black;
  int nbtour;

  Game();
  void startgame();
  void move(coord ini, coord dest, Player* qui);
  friend ostream& operator<<(ostream&, Game&);
  friend istream& operator>>(istream&, Game&);
  void resumeGame();
  void saveGame();
};

#endif  // GAME_H_INCLUDED
