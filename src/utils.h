#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

class coord{
public:
    int x;
    int y;
    int verifcoord();
    void lirecoord();
    bool operator==(coord const &b);
    friend ostream& operator<<(ostream& ,coord );

};

template <class T>
struct cCell {
    cCell(T data) : elt(data), succ(NULL) {}
    T elt;
    cCell<T> *succ;
};

template <class T>
class liste {
public:
    cCell<T> *tete;
    liste() : tete(NULL) {};
    ~liste();
    void ajoutliste(const T data);
    void affichechaine();
    int cherchechaine(const T data) const;
    int listevide() const
    {
    if (tete == NULL) return 1;
    return 0;
    }
};

int coord::verifcoord()
    {
    if ((this->x>=0)&&(this->x<8)&&(this->y>=0)&&(this->y<8))
        return 1;
    else
        return 0;
    }

void coord::lirecoord()
    {
    char ch[2];
    cin>>ch;
        switch (ch[0])
        {
            case 'H':
                this->y=7;break;
            case 'G':
                this->y=6;break;
            case 'F':
                this->y=5;break;
            case 'E':
                this->y=4;break;
            case 'D':
                this->y=3;break;
            case 'C':
                this->y=2;break;
            case 'B':
                this->y=1;break;
            case 'A':
                this->y=0;break;
            default:
                cout<<"erreur"<<endl;
        }
        switch (ch[1])
        {
            case '1':
                this->x=7;break;
            case '2':
                this->x=6;break;
            case '3':
                this->x=5;break;
            case '4':
                this->x=4;break;
            case '5':
                this->x=3;break;
            case '6':
                this->x=2;break;
            case '7':
                this->x=1;break;
            case '8':
                this->x=0;break;
            default:
                cout<<"erreur"<<endl;
        }
    }

bool coord::operator==(coord const &b)
    {
        if ((this->x==b.x)&&(this->y==b.y))return true; else return false;
    }

ostream& operator<<(ostream& flux,coord pos)
    {
        flux <<pos.x<<"  "<<pos.y<<endl;
        return flux;
    }

template<class T>
liste<T>::~liste()
{
    while (tete != NULL)
    {
        cCell<T> *tmp = tete;
        tete = tete->succ;
        delete tmp;
    }
    delete tete;
    tete=NULL;
}

template<class T>
void liste<T>::affichechaine()
{
    for (cCell<T> *tmp = tete; tmp != NULL; tmp = tmp->succ)
        cout<<"  "<<tmp->elt;
}

template<class T>
void liste<T>::ajoutliste(const T data)
{
    if (tete == NULL)
    {
        tete = new cCell<T>(data);
    }
    else
    {
        cCell<T> *cour;cour=new cCell<T>(data);cour->succ=tete;
        tete=cour;


    }
}

template<class T>
int liste<T>::cherchechaine(const T data) const
{
    if (this->tete != NULL) if (this->tete->elt==data) return 1;
    for (cCell<T> *tmp = this->tete; tmp != NULL; tmp = tmp->succ)
        if (tmp->elt == data)
            return 1;
    return 0;
}

class chessboard;

class piece
{   public:
    int joueur;
    int valeur;
    int symbole;
    liste<coord> possibilites;
    piece(int j) {liste<coord> ini;joueur=j;possibilites=ini;}
    ~piece(){}
    int verifami(coord dest,chessboard E);
    int verifennemi(coord dest,chessboard E) ;
    virtual void deplacementnaif(coord source,chessboard tab)=0;
};

class reine :public piece
{
    public:
    reine(int j):piece(j){valeur=10;symbole=81;}

    void deplacementnaif(coord source,chessboard tab);
};

class fou :public piece
{
    public:
    fou(int j):piece(j){valeur=3;symbole=66;}
    void deplacementnaif(coord source,chessboard tab);
};

class tour :public piece
{
    public:
    tour(int j):piece(j){valeur=5;symbole=82;}
    void deplacementnaif(coord source,chessboard tab);
};

class pion :public piece
{
    public:
    pion(int j):piece(j){valeur=1;symbole=80;}
    void deplacementnaif(coord source,chessboard tab);
};

class cheval :public piece
{
    public:
    cheval(int j):piece(j){valeur=4;symbole=75;}
    void deplacementnaif(coord source,chessboard tab);
};

class roi :public piece
{
    public:
    roi(int j):piece(j){valeur=999;symbole=244;}
    void deplacementnaif(coord source,chessboard tab);
};

class Joueur
{   public:
    int couleur;
    string nom;
    //virtual void demandernom()=0;
	virtual int demandersauvegarde() = 0;
    virtual bool decidermouvement(chessboard &E,coord &ini,coord &sol)=0;
    virtual piece* choisirpiece()=0;
};

#endif // PROTOTYPE_H_INCLUDED
