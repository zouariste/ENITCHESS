#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

class Coord{
public:
    int x;
    int y;
    int verifcoord();
    void readcoord();
    bool operator==(Coord const &b);
    friend ostream& operator<<(ostream& ,Coord );

};

template <class T>
struct cCell {
    cCell(T data) : elt(data), succ(NULL) {}
    T elt;
    cCell<T> *succ;
};

template <class T>
class LinkedList {
public:
    cCell<T> *head;
    LinkedList() : head(NULL) {};
    ~LinkedList();
    void addlist(const T data);
    void affichechaine();
    int cherchechaine(const T data) const;
    int listevide() const
    {
    if (head == NULL) return 1;
    return 0;
    }
};

class ChessBoard;

class Piece
{   public:
    int joueur;
    int valeur;
    int symbole;
    LinkedList<Coord> possibilites;
    Piece(int j) {LinkedList<Coord> ini;joueur=j;possibilites=ini;}
    ~Piece(){}
    int verifami(Coord dest,ChessBoard E);
    int verifennemi(Coord dest,ChessBoard E) ;
    virtual void deplacementnaif(Coord source,ChessBoard tab)=0;
};

class Queen :public Piece
{
    public:
    Queen(int j):Piece(j){valeur=10;symbole=81;}

    void deplacementnaif(Coord source,ChessBoard tab);
};

class Bishop :public Piece
{
    public:
    Bishop(int j):Piece(j){valeur=3;symbole=66;}
    void deplacementnaif(Coord source,ChessBoard tab);
};

class Rook :public Piece
{
    public:
    Rook(int j):Piece(j){valeur=5;symbole=82;}
    void deplacementnaif(Coord source,ChessBoard tab);
};

class Pawn :public Piece
{
    public:
    Pawn(int j):Piece(j){valeur=1;symbole=80;}
    void deplacementnaif(Coord source,ChessBoard tab);
};

class Knight :public Piece
{
    public:
    Knight(int j):Piece(j){valeur=4;symbole=75;}
    void deplacementnaif(Coord source,ChessBoard tab);
};

class King :public Piece
{
    public:
    King(int j):Piece(j){valeur=999;symbole=244;}
    void deplacementnaif(Coord source,ChessBoard tab);
};

class Player
{   public:
    int couleur;
    string nom;
    //virtual void demandernom()=0;
	virtual int demandersauvegarde() = 0;
    virtual bool decidermouvement(ChessBoard &E,Coord &ini,Coord &sol)=0;
    virtual Piece* choosepiece()=0;
};

#endif // PROTOTYPE_H_INCLUDED
