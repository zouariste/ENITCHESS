#ifndef CLASSJOUEUR_H_INCLUDED
#define CLASSJOUEUR_H_INCLUDED

#include "utils.h"
#include "chessboard.h"

// class Player
// {   public:
//     int couleur;
//     string nom;
//     //virtual void demandernom()=0;
// 	virtual int demandersauvegarde() = 0;
//     virtual bool decidermouvement(ChessBoard &E,Coord &ini,Coord &sol)=0;
//     virtual Piece* choosepiece()=0;
// };


class Human :public Player
{
    public:
		Piece * choosepiece();
		int demandersauvegarde() { return 0; }
		bool decidermouvement(ChessBoard &E,Coord &ini,Coord &dest);
};

class Machine :public Player
{
    public:
	int difficulte;
	int demandersauvegarde() { return this->difficulte; }
    Machine(int diff) {this->difficulte=diff;}
    Piece * choosepiece(){Piece *res=new Queen(this->couleur);return res;}
    void minimax( int depth , ChessBoard &E ,Coord &ini,Coord &sol);
    int findmin (int,ChessBoard&);
    int findmax (int,ChessBoard&);
    void ABminimax( int depth , ChessBoard &E ,Coord &ini,Coord &sol);
    int ABrecherchemin (int,ChessBoard&,int,int);
    int ABrecherchemax (int,ChessBoard&,int,int);
    int evaluerChessBoard(ChessBoard &E)
    {
        int i,j;Coord loc;int v=0;
        for (i=0;i<8;i++)
        {
            for (j=0;j<8;j++)
            {
                loc.x=i;loc.y=j;
                if ((E.verifPiece(loc)&&(E.getPiece(loc)->joueur ==this->couleur))) {v=v+E.getPiece(loc)->valeur;}
                if ((E.verifPiece(loc)&&(E.getPiece(loc)->joueur !=this->couleur))) {v=v-E.getPiece(loc)->valeur;}

            }
        }
        return(v);
    }
    bool decidermouvement(ChessBoard &E,Coord &ini,Coord &sol)
    {
        if (this->difficulte<4) this->minimax(this->difficulte,E,ini,sol);
        else this->ABminimax(this->difficulte,E,ini,sol);
		return true;
    }
};

#endif // CLASSJOUEUR_H_INCLUDED
