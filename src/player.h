#ifndef CLASSJOUEUR_H_INCLUDED
#define CLASSJOUEUR_H_INCLUDED

#include "utils.h"

#include "chessboard.h"

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
                if ((E.Piececheck(loc) && (E.getPiece(loc) -> player == this -> color))) {
                    v = v + E.getPiece(loc) -> value;
                }
                if ((E.Piececheck(loc) && (E.getPiece(loc) -> player != this -> color))) {
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

bool Human::decideMove(Chessboard & E, coord & ini, coord & dest) {

    if ((ini.verifcoord()) && (E.Piececheck(ini)) && (E.getPiece(ini) -> player == this -> color) && (!(E.getPiece(ini) -> possibilites.emptylist())) && (E.getPiece(ini) -> possibilites.cherchechaine(dest)))
        return true;
    else
        return false;

}

void Ai::miniMax(int depth, Chessboard & E, coord & ini, coord & sol) {
    int value, bestscore = -10000;
    coord loc;
    coord temp;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            loc.x = i;
            loc.y = j;
            if ((E.Piececheck(loc)) && (E.getPiece(loc) -> player == this -> color)) {
                for (cCell < coord > * tmp = E.getPiece(loc) -> possibilites.head; tmp != NULL; tmp = tmp -> succ) {
                    temp.x = i, temp.y = j;
                    Chessboard Aux = E;
                    Aux.move(temp, tmp -> elt, this);
                    Aux.naiveMove(this -> color + 1);
                    Aux.legalMove(this -> color + 1);
                    if (Aux.endGame(this -> color + 1)) {
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp -> elt.x;
                        sol.y = tmp -> elt.y;
                        return;
                    }
                    value = this -> findMin(depth - 1, Aux);
                    if (value == 999) {
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp -> elt.x;
                        sol.y = tmp -> elt.y;
                        return;
                    }
                    if ((value > bestscore) || ((value == bestscore) && ((rand() % 6) == 2))) {
                        bestscore = value;
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp -> elt.x;
                        sol.y = tmp -> elt.y;

                    }

                }

            }
        }

}

int Ai::findMin(int depth, Chessboard & E) {
    if (depth == 0) {
        return this -> scoreChessboard(E);
    }
    coord temp;
    int bestscore = 10000;
    coord loc, sol;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            loc.x = i;
            loc.y = j;
            if ((E.Piececheck(loc)) && (E.getPiece(loc) -> player != this -> color)) {
                for (cCell < coord > * tmp = E.getPiece(loc) -> possibilites.head; tmp != NULL; tmp = tmp -> succ) {
                    temp.x = i, temp.y = j;
                    Chessboard Aux = E;
                    Aux.move(temp, tmp -> elt, this);
                    Aux.naiveMove(this -> color);
                    Aux.legalMove(this -> color);
                    if (Aux.endGame(this -> color)) return (-999);

                    int value = -this -> findMax(depth - 1, Aux);
                    if (value == 999) return (999);
                    if (value < bestscore) {
                        bestscore = value;

                    }

                }

            }
        }

    return bestscore;
}

int Ai::findMax(int depth, Chessboard & E) {
    if (depth == 0) {
        return this -> scoreChessboard(E);
    }
    coord temp;
    int bestscore = -10000;
    coord loc, sol;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            loc.x = i;
            loc.y = j;
            if ((E.Piececheck(loc)) && (E.getPiece(loc) -> player == this -> color)) {
                for (cCell < coord > * tmp = E.getPiece(loc) -> possibilites.head; tmp != NULL; tmp = tmp -> succ) {
                    temp.x = i, temp.y = j;
                    Chessboard Aux = E;
                    Aux.move(temp, tmp -> elt, this);
                    Aux.naiveMove(this -> color + 1);
                    Aux.legalMove(this -> color + 1);
                    if (Aux.endGame(this -> color + 1)) return (999);
                    int value = this -> findMin(depth - 1, Aux);
                    if (value == 999) return (999);
                    if ((value > bestscore) || ((value == bestscore) && ((rand() % 6) == 2))) {
                        bestscore = value;

                    }

                }

            }
        }

    return bestscore;

}

void Ai::ABminimax(int depth, Chessboard & E, coord & ini, coord & sol) {
    int bestscore = -10000;
    coord loc;
    coord temp;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            loc.x = i;
            loc.y = j;
            if ((E.Piececheck(loc)) && (E.getPiece(loc) -> player == this -> color)) {
                for (cCell < coord > * tmp = E.getPiece(loc) -> possibilites.head; tmp != NULL; tmp = tmp -> succ) {
                    temp.x = i, temp.y = j;
                    Chessboard Aux = E;
                    Aux.move(temp, tmp -> elt, this);
                    Aux.naiveMove(this -> color + 1);
                    Aux.legalMove(this -> color + 1);
                    if (Aux.endGame(this -> color + 1)) {
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp -> elt.x;
                        sol.y = tmp -> elt.y;
                        return;
                    }
                    int value = ABfindMin(depth - 1, Aux, -10000, 10000);
                    if (value == 999) {
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp -> elt.x;
                        sol.y = tmp -> elt.y;
                        return;
                    }
                    if (value > bestscore) {
                        bestscore = value;
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp -> elt.x;
                        sol.y = tmp -> elt.y;

                    }

                }

            }
        }

}

int Ai::ABfindMin(int depth, Chessboard & E, int a, int b) {
    if (depth == 0)
        return this -> scoreChessboard(E);
    int alpha = a;
    int beta = b;
    int bestscore = 10000;
    coord loc, sol;
    coord temp;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            loc.x = i;
            loc.y = j;
            if ((E.Piececheck(loc)) && (E.getPiece(loc) -> player != this -> color)) {
                for (cCell < coord > * tmp = E.getPiece(loc) -> possibilites.head; tmp != NULL; tmp = tmp -> succ) {
                    temp.x = i, temp.y = j;
                    Chessboard Aux = E;
                    Aux.move(temp, tmp -> elt, this);
                    Aux.naiveMove(this -> color);
                    Aux.legalMove(this -> color);
                    if (Aux.endGame(this -> color)) return (-999);
                    int value = ABfindMax(depth - 1, Aux, alpha, beta);
                    if (value == 999) return (999);
                    if (value < bestscore) {
                        bestscore = value;
                        beta = value;
                    }
                    if (beta > alpha) return bestscore;

                }

            }
        }

    return bestscore;
}

int Ai::ABfindMax(int depth, Chessboard & E, int a, int b) {

    if (depth == 0)
        return this -> scoreChessboard(E);

    int bestscore = -10000;
    int alpha = a;
    int beta = b;
    coord loc, sol;
    coord temp;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            loc.x = i;
            loc.y = j;
            if ((E.Piececheck(loc)) && (E.getPiece(loc) -> player == this -> color)) {
                for (cCell < coord > * tmp = E.getPiece(loc) -> possibilites.head; tmp != NULL; tmp = tmp -> succ) {
                    temp.x = i, temp.y = j;
                    Chessboard Aux = E;
                    Aux.move(temp, tmp -> elt, this);
                    Aux.naiveMove(this -> color + 1);
                    Aux.legalMove(this -> color + 1);
                    if (Aux.endGame(this -> color + 1)) return (999);
                    int value = ABfindMin(depth - 1, Aux, alpha, beta);
                    if (value == 999) return (999);
                    if (value > bestscore) {
                        bestscore = value;
                        alpha = value;
                    }
                    if (beta < alpha) return bestscore;

                }

            }
        }

    return bestscore;

}

#endif // CLASSJOUEUR_H_INCLUDED