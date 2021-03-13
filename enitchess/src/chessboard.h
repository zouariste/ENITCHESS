#ifndef ECHEQUIER_H_INCLUDED
#define ECHEQUIER_H_INCLUDED

#include "utils.h"
#include <stdio.h>

// class Piece;
// class Player;

class ChessBoard
{
private:
	Piece * Tab[8][8];
public:
	void printchess();
	int check(int ntour, Coord coroi);
	Coord chercheroi(int ntour);
	int finpartie(int ntour);
	void deplacementlegal(ChessBoard E, int ntour);
	void forcedeplacer(Coord &c1, Coord &c2)
	{
		if (this->Tab[c2.x][c2.y] != NULL) delete this->Tab[c2.x][c2.y];
		this->Tab[c2.x][c2.y] = this->Tab[c1.x][c1.y];
		this->Tab[c1.x][c1.y] = NULL;
	}
	void initChessBoard()
	{
		int i, j;
		for (i = 1; i<7; i++)
		{
			if ((i == 6) || (i == 1))
				for (j = 0; j<8; j++)
				{
					this->Tab[i][j] = new Pawn((i % 2) + 1);
				}
			else
				for (j = 0; j<8; j++)
					this->Tab[i][j] = NULL;
		}
		this->Tab[0][0] = new Rook(2);               this->Tab[7][0] = new Rook(1);
		this->Tab[0][7] = new Rook(2);               this->Tab[7][7] = new Rook(1);
		this->Tab[0][1] = new Knight(2);             this->Tab[7][1] = new Knight(1);
		this->Tab[0][6] = new Knight(2);             this->Tab[7][6] = new Knight(1);
		this->Tab[0][5] = new Bishop(2);                this->Tab[7][5] = new Bishop(1);
		this->Tab[0][2] = new Bishop(2);                this->Tab[7][2] = new Bishop(1);
		this->Tab[0][3] = new Queen(2);              this->Tab[7][3] = new Queen(1);
		this->Tab[0][4] = new King(2);                this->Tab[7][4] = new King(1);
		this->Tab[0][3] = new Queen(2);              this->Tab[7][3] = new Queen(1);
		this->Tab[0][4] = new King(2);                this->Tab[7][4] = new King(1);
	}

	ChessBoard()
	{
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
				this->Tab[i][j] = NULL;

	}
	void deplacementnaif(int n)
	{
		Coord loc;
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
			{
				loc.x = i; loc.y = j;
				if (this->verifPiece(loc))
					if ((2 - (n) % 2) == this->getPiece(loc)->joueur)
						this->getPiece(loc)->deplacementnaif(loc, *this);
			}
	}
	~ChessBoard()
	{
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
				delete this->Tab[i][j];
	}
	ChessBoard(const ChessBoard& tab)
	{
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
			{
				if (tab.Tab[i][j] == NULL)
					this->Tab[i][j] = NULL;
				else
					switch (tab.Tab[i][j]->valeur)
					{
					case 999:
						this->Tab[i][j] = new King(tab.Tab[i][j]->joueur); break;
					case 1:
						this->Tab[i][j] = new Pawn(tab.Tab[i][j]->joueur); break;
					case 4:
						this->Tab[i][j] = new Knight(tab.Tab[i][j]->joueur); break;
					case 3:
						this->Tab[i][j] = new Bishop(tab.Tab[i][j]->joueur); break;
					case 5:
						this->Tab[i][j] = new Rook(tab.Tab[i][j]->joueur); break;
					case 10:
						this->Tab[i][j] = new Queen(tab.Tab[i][j]->joueur); break;



					}
			}
	}
	void mouvement(Coord loc, Coord dest, Player *qui)
	{
		this->forcedeplacer(loc, dest);
		if ((this->getPiece(dest)->valeur == 1) && ((dest.x == 0) || (dest.x == 7)))
		{
			delete this->getPiece(dest);
			this->Tab[dest.x][dest.y] = qui->choosepiece();
		}

	}
	Piece* getPiece(Coord loc) { if (loc.verifcoord()) return this->Tab[loc.x][loc.y]; }
	void setPiece(Piece *input, Coord loc) { this->Tab[loc.x][loc.y] = input; }
	bool verifPiece(Coord loc) { if (loc.verifcoord()) { if (Tab[loc.x][loc.y] == NULL) return false; else return true; } }
	void deplacementlegalun(int i, int j, int nbtour)
	{
		cCell<Coord> *temp, *pred=NULL;
		Coord pos, pos2, loc;
		pos.x = i;
		pos.y = j;
		temp = this->getPiece(pos)->possibilites.head;
		while (this->getPiece(pos)->possibilites.head != NULL)
		{
			ChessBoard Taux(*this);
			Taux.forcedeplacer(pos, this->getPiece(pos)->possibilites.head->elt);
			for (int i = 0; i<8; i++)
				for (int j = 0; j<8; j++)
				{
					loc.x = i; loc.y = j;
					if (Taux.verifPiece(loc))
						if ((2 - (nbtour) % 2) == Taux.getPiece(loc)->joueur)
							Taux.getPiece(loc)->deplacementnaif(loc, Taux);
				}

			pos2 = Taux.chercheroi(nbtour + 1);
			if (Taux.check(nbtour + 1, pos2))
			{
				this->getPiece(pos)->possibilites.head = temp->succ;
				delete temp;
				temp = this->getPiece(pos)->possibilites.head;
			}

			else { break; }
		}
		while (temp != NULL)
		{
			ChessBoard Taux(*this);
			Taux.forcedeplacer(pos, temp->elt);
			Coord loc;
			for (int i = 0; i<8; i++)
				for (int j = 0; j<8; j++)
				{
					loc.x = i; loc.y = j;
					if (Taux.verifPiece(loc))
						if ((2 - (nbtour) % 2) == Taux.getPiece(loc)->joueur)
							Taux.getPiece(loc)->deplacementnaif(loc, Taux);
				}
			pos2 = Taux.chercheroi(nbtour + 1);
			if (temp != NULL && !Taux.check(nbtour + 1, pos2))
			{
				pred = temp;
				temp = temp->succ;

			}

			else if (temp == NULL) break;

			else
			{
				pred->succ = temp->succ;
				delete temp;
				temp = pred->succ;

			}


		}

	}
	void deplacementlegal(int nbtour)
	{
		int i, j; Coord loc;
		for (i = 0; i<8; i++)
		{
			for (j = 0; j<8; j++)
			{
				loc.x = i; loc.y = j;
				if ((this->verifPiece(loc)) && (this->getPiece(loc)->joueur == (2 - (nbtour + 1) % 2)))
					this->deplacementlegalun(i, j, nbtour);

			}
		}
	}

};

void ChessBoard::printchess()
{

	int i, j;
	system("cls");
	printf("                                %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 218, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 194, 196, 191);
	for (i = 0; i<8; i++)
	{
		printf("                               %d", 8 - i);
		for (j = 0; j<8; j++)
		{
			int ch, q;
			printf("%c", 179);
			if (this->Tab[i][j] == NULL)
			{
				ch = 32; q = 0;
			}
			else
			{
				ch = this->Tab[i][j]->symbole;
				q = this->Tab[i][j]->joueur;
			}

		}

		 // printcol(179, 0); printf("\n");
		if (i<7)
		{
			printf("                                "); //printcol(195, 0); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 196, 197, 196, 197, 196, 197, 196, 197, 196, 197, 196, 197, 196, 197, 196, 180);
		}
		else
		{
			printf("                                "); //printcol(192, 0); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 193, 196, 217);
		}
	}
	 printf("                                 A B C D E F G H \n                  ");
	for (int i=0;i<8;i++)
	for (int j=0;j<8;j++)
	if (this->Tab[i][j]!=NULL) {cout<<"Coord"<<i<<"  "<<j<<"  type  ";printf("%c",this->Tab[i][j]->symbole);cout<<endl; this->Tab[i][j]->possibilites.affichechaine();cout<<endl;}
}

int ChessBoard::check(int ntour, Coord coroi)
{
	Coord loc;
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
		{
			loc.x = i; loc.y = j;
			if (this->verifPiece(loc))
				if ((this->Tab[i][j]->joueur == ntour % 2 + 1))
					if ((this->Tab[i][j]->possibilites.cherchechaine(coroi)))
						return 1;
		}
	return 0;
}

Coord ChessBoard::chercheroi(int ntour)
{
	int i, j;
	Coord co;
	for (i = 0; i<8; i++)
		for (j = 0; j<8; j++)
		{
			co.x = i; co.y = j;
			if ((this->verifPiece(co)) && (this->Tab[i][j]->valeur == 999) && (this->Tab[i][j]->joueur == 2 - (ntour % 2)))
				return co;
		}
	return co;
}

int ChessBoard::finpartie(int ntour)
{
	int i, j; Coord loc;
	for (i = 0; i<8; i++)
	{
		for (j = 0; j<8; j++)
		{
			loc.x = i; loc.y = j;
			if (this->verifPiece(loc))
				if ((2 - ntour % 2) == (this->Tab[i][j]->joueur))
				{
					if (!(this->Tab[i][j]->possibilites.listevide())) return (0);
				}
		}
	}
	return (1);
}

#endif // ECHEQUIER_H_INCLUDED
