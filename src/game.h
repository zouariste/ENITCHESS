#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <time.h>
#include <iostream>
#include "utils.h"
#include "chessboard.h"
#include "player.h"
#include <unistd.h>

class Game {
public:
    Chessboard grille;
    Player* white;
    Player* black;
    int nbtour;

    Game();
    void startgame();
    void move(coord ini, coord dest, Player* qui);
    friend ostream& operator<<(ostream&, Game&);
    friend istream& operator>>(istream&, Game&);
    void reprendreGame();
    void saveGame();
};

#endif // GAME_H_INCLUDED
