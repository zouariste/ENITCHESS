#include "src/utils.h"

#include "src/chessboard.h"

#include "src/piece.h"

#include "src/player.h"

#include "src/game.h"

#include "time.h"

using namespace std;

int main() {

    Game x;
    // To simulate a AI vs AI game, please uncomment and choose the respective difficulty.
    // x.white = new Ai(3); x.black = new Ai(1); x.white->color = 1; x.black->color = 2;
    x.startgame();

}