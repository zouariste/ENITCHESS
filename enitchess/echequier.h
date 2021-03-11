#ifndef ECHEQUIER_H_INCLUDED
#define ECHEQUIER_H_INCLUDED

#include "prototype.h"
#include <stdio.h>

class piece;
class Joueur;

class echequier
{
private:
	piece * Tab[8][8];
public:
	void printchess();
	int check(int ntour, coord coroi);
	coord chercheroi(int ntour);
	int finpartie(int ntour);
	void deplacementlegal(echequier E, int ntour);
	void forcedeplacer(coord &c1, coord &c2)
	{
		if (this->Tab[c2.x][c2.y] != NULL) delete this->Tab[c2.x][c2.y];
		this->Tab[c2.x][c2.y] = this->Tab[c1.x][c1.y];
		this->Tab[c1.x][c1.y] = NULL;
	}
	void initechequier()
	{
		int i, j;
		for (i = 1; i<7; i++)
		{
			if ((i == 6) || (i == 1))
				for (j = 0; j<8; j++)
				{
					this->Tab[i][j] = new pion((i % 2) + 1);
				}
			else
				for (j = 0; j<8; j++)
					this->Tab[i][j] = NULL;
		}
		this->Tab[0][0] = new tour(2);               this->Tab[7][0] = new tour(1);
		this->Tab[0][7] = new tour(2);               this->Tab[7][7] = new tour(1);
		this->Tab[0][1] = new cheval(2);             this->Tab[7][1] = new cheval(1);
		this->Tab[0][6] = new cheval(2);             this->Tab[7][6] = new cheval(1);
		this->Tab[0][5] = new fou(2);                this->Tab[7][5] = new fou(1);
		this->Tab[0][2] = new fou(2);                this->Tab[7][2] = new fou(1);
		this->Tab[0][3] = new reine(2);              this->Tab[7][3] = new reine(1);
		this->Tab[0][4] = new roi(2);                this->Tab[7][4] = new roi(1);
		this->Tab[0][3] = new reine(2);              this->Tab[7][3] = new reine(1);
		this->Tab[0][4] = new roi(2);                this->Tab[7][4] = new roi(1);
	}

	echequier()
	{
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
				this->Tab[i][j] = NULL;

	}
	void deplacementnaif(int n)
	{
		coord loc;
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
			{
				loc.x = i; loc.y = j;
				if (this->verifpiece(loc))
					if ((2 - (n) % 2) == this->getpiece(loc)->joueur)
						this->getpiece(loc)->deplacementnaif(loc, *this);
			}
	}
	~echequier()
	{
		for (int i = 0; i<8; i++)
			for (int j = 0; j<8; j++)
				delete this->Tab[i][j];
	}
	echequier(const echequier& tab)
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
						this->Tab[i][j] = new roi(tab.Tab[i][j]->joueur); break;
					case 1:
						this->Tab[i][j] = new pion(tab.Tab[i][j]->joueur); break;
					case 4:
						this->Tab[i][j] = new cheval(tab.Tab[i][j]->joueur); break;
					case 3:
						this->Tab[i][j] = new fou(tab.Tab[i][j]->joueur); break;
					case 5:
						this->Tab[i][j] = new tour(tab.Tab[i][j]->joueur); break;
					case 10:
						this->Tab[i][j] = new reine(tab.Tab[i][j]->joueur); break;



					}
			}
	}
	void mouvement(coord loc, coord dest, Joueur *qui)
	{
		this->forcedeplacer(loc, dest);
		if ((this->getpiece(dest)->valeur == 1) && ((dest.x == 0) || (dest.x == 7)))
		{
			delete this->getpiece(dest);
			this->Tab[dest.x][dest.y] = qui->choisirpiece();
		}

	}
	piece* getpiece(coord loc) { if (loc.verifcoord()) return this->Tab[loc.x][loc.y]; }
	void setpiece(piece *input, coord loc) { this->Tab[loc.x][loc.y] = input; }
	bool verifpiece(coord loc) { if (loc.verifcoord()) { if (Tab[loc.x][loc.y] == NULL) return false; else return true; } }
	void deplacementlegalun(int i, int j, int nbtour)
	{
		cCell<coord> *temp, *pred=NULL;
		coord pos, pos2, loc;
		pos.x = i;
		pos.y = j;
		temp = this->getpiece(pos)->possibilites.tete;
		while (this->getpiece(pos)->possibilites.tete != NULL)
		{
			echequier Taux(*this);
			Taux.forcedeplacer(pos, this->getpiece(pos)->possibilites.tete->elt);
			for (int i = 0; i<8; i++)
				for (int j = 0; j<8; j++)
				{
					loc.x = i; loc.y = j;
					if (Taux.verifpiece(loc))
						if ((2 - (nbtour) % 2) == Taux.getpiece(loc)->joueur)
							Taux.getpiece(loc)->deplacementnaif(loc, Taux);
				}

			pos2 = Taux.chercheroi(nbtour + 1);
			if (Taux.check(nbtour + 1, pos2))
			{
				this->getpiece(pos)->possibilites.tete = temp->succ;
				delete temp;
				temp = this->getpiece(pos)->possibilites.tete;
			}

			else { break; }
		}
		while (temp != NULL)
		{
			echequier Taux(*this);
			Taux.forcedeplacer(pos, temp->elt);
			coord loc;
			for (int i = 0; i<8; i++)
				for (int j = 0; j<8; j++)
				{
					loc.x = i; loc.y = j;
					if (Taux.verifpiece(loc))
						if ((2 - (nbtour) % 2) == Taux.getpiece(loc)->joueur)
							Taux.getpiece(loc)->deplacementnaif(loc, Taux);
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
		int i, j; coord loc;
		for (i = 0; i<8; i++)
		{
			for (j = 0; j<8; j++)
			{
				loc.x = i; loc.y = j;
				if ((this->verifpiece(loc)) && (this->getpiece(loc)->joueur == (2 - (nbtour + 1) % 2)))
					this->deplacementlegalun(i, j, nbtour);

			}
		}
	}

};

void echequier::printchess()
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
	if (this->Tab[i][j]!=NULL) {cout<<"coord"<<i<<"  "<<j<<"  type  ";printf("%c",this->Tab[i][j]->symbole);cout<<endl; this->Tab[i][j]->possibilites.affichechaine();cout<<endl;}
}

int echequier::check(int ntour, coord coroi)
{
	coord loc;
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
		{
			loc.x = i; loc.y = j;
			if (this->verifpiece(loc))
				if ((this->Tab[i][j]->joueur == ntour % 2 + 1))
					if ((this->Tab[i][j]->possibilites.cherchechaine(coroi)))
						return 1;
		}
	return 0;
}

coord echequier::chercheroi(int ntour)
{
	int i, j;
	coord co;
	for (i = 0; i<8; i++)
		for (j = 0; j<8; j++)
		{
			co.x = i; co.y = j;
			if ((this->verifpiece(co)) && (this->Tab[i][j]->valeur == 999) && (this->Tab[i][j]->joueur == 2 - (ntour % 2)))
				return co;
		}
	return co;
}

int echequier::finpartie(int ntour)
{
	int i, j; coord loc;
	for (i = 0; i<8; i++)
	{
		for (j = 0; j<8; j++)
		{
			loc.x = i; loc.y = j;
			if (this->verifpiece(loc))
				if ((2 - ntour % 2) == (this->Tab[i][j]->joueur))
				{
					if (!(this->Tab[i][j]->possibilites.listevide())) return (0);
				}
		}
	}
	return (1);
}

#endif // ECHEQUIER_H_INCLUDED
