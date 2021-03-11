#ifndef CLASSJOUEUR_H_INCLUDED
#define CLASSJOUEUR_H_INCLUDED

#include "prototype.h"
#include "echequier.h"

class Humain :public Joueur
{
    public:
		piece * choisirpiece();
		int demandersauvegarde() { return 0; }
		bool decidermouvement(echequier &E,coord &ini,coord &dest);
};

class Machine :public Joueur
{
    public:
	int difficulte;
	int demandersauvegarde() { return this->difficulte; }
    Machine(int diff) {this->difficulte=diff;}
    piece * choisirpiece(){piece *res=new reine(this->couleur);return res;}
    void minimax( int profondeur , echequier &E ,coord &ini,coord &sol);
    int recherchemin (int,echequier&);
    int recherchemax (int,echequier&);
    void ABminimax( int profondeur , echequier &E ,coord &ini,coord &sol);
    int ABrecherchemin (int,echequier&,int,int);
    int ABrecherchemax (int,echequier&,int,int);
    int evaluerechequier(echequier &E)
    {
        int i,j;coord loc;int v=0;
        for (i=0;i<8;i++)
        {
            for (j=0;j<8;j++)
            {
                loc.x=i;loc.y=j;
                if ((E.verifpiece(loc)&&(E.getpiece(loc)->joueur ==this->couleur))) {v=v+E.getpiece(loc)->valeur;}
                if ((E.verifpiece(loc)&&(E.getpiece(loc)->joueur !=this->couleur))) {v=v-E.getpiece(loc)->valeur;}

            }
        }
        return(v);
    }
    bool decidermouvement(echequier &E,coord &ini,coord &sol)
    {
        if (this->difficulte<4) this->minimax(this->difficulte,E,ini,sol);
        else this->ABminimax(this->difficulte,E,ini,sol);
		return true;
    }
};

bool Humain::decidermouvement(echequier &E, coord &ini, coord &dest)
{

	if ((ini.verifcoord()) && (E.verifpiece(ini)) && (E.getpiece(ini)->joueur == this->couleur) && (!(E.getpiece(ini)->possibilites.listevide())) && (E.getpiece(ini)->possibilites.cherchechaine(dest)))
		return true;
	else
		return false;

}

void Machine::minimax( int profondeur , echequier &E ,coord &ini,coord &sol)
{
    int valeur,meilleurevaleur = -10000;
	coord loc;
	coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifpiece(loc)) && (E.getpiece(loc)->joueur == this->couleur))
            {
                for (cCell<coord> *tmp = E.getpiece(loc)->possibilites.tete; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    echequier Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) {ini.x = i;ini.y = j;sol.x = tmp->elt.x;sol.y = tmp->elt.y;return;}
                    valeur = this->recherchemin( profondeur-1 , Aux );
                    if (valeur == 999) {ini.x = i;ini.y = j;sol.x = tmp->elt.x;sol.y = tmp->elt.y;return;}
                    if(( valeur > meilleurevaleur) ||( (valeur==meilleurevaleur) &&((rand() % 6)==2)))
                    {
                        meilleurevaleur = valeur;
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp->elt.x;
                        sol.y = tmp->elt.y;

                    }

                }

            }
        }

}

int Machine::recherchemin( int profondeur , echequier &E )
{
    if(profondeur==0)
        {return this->evaluerechequier(E);}
	coord temp;
    int meilleurevaleur = 10000;
    coord loc,sol;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifpiece(loc)) && (E.getpiece(loc)->joueur != this->couleur))
            {
                for (cCell<coord> *tmp = E.getpiece(loc)->possibilites.tete; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    echequier Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur);
                    Aux.deplacementlegal(this->couleur);
                    if (Aux.finpartie(this->couleur)) return (-999);

                    int valeur = -this->recherchemax( profondeur-1 , Aux );
                    if (valeur==999) return (999);
                    if( valeur < meilleurevaleur )
                    {
                        meilleurevaleur = valeur;

                    }

                }

            }
        }

        return meilleurevaleur;
}

int Machine::recherchemax( int profondeur ,  echequier &E )
{
    if(profondeur==0)
        {return this->evaluerechequier(E);}
	coord temp;
    int meilleurevaleur = -10000;
    coord loc,sol;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifpiece(loc)) && (E.getpiece(loc)->joueur == this->couleur))
            {
                for (cCell<coord> *tmp = E.getpiece(loc)->possibilites.tete; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    echequier Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) return (999);
                    int valeur = this->recherchemin( profondeur-1 , Aux );
                    if (valeur==999) return (999);
					if ((valeur > meilleurevaleur) || ((valeur == meilleurevaleur) && ((rand() % 6) == 2)))
                    {
                        meilleurevaleur = valeur;

                    }

                }

            }
        }

        return meilleurevaleur;

}

void Machine::ABminimax( int profondeur , echequier &E ,coord &ini,coord &sol)
{
    int meilleurevaleur = -10000;
    coord loc;
	coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifpiece(loc)) && (E.getpiece(loc)->joueur == this->couleur))
            {
                for (cCell<coord> *tmp = E.getpiece(loc)->possibilites.tete; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    echequier Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) {ini.x = i;ini.y = j;sol.x = tmp->elt.x;sol.y = tmp->elt.y;return;}
                    int valeur = ABrecherchemin( profondeur-1 , Aux ,-10000,10000);
                    if (valeur == 999) {ini.x = i;ini.y = j;sol.x = tmp->elt.x;sol.y = tmp->elt.y;return;}
                    if( valeur > meilleurevaleur )
                    {
                        meilleurevaleur = valeur;
                        ini.x = i;
                        ini.y = j;
                        sol.x = tmp->elt.x;
                        sol.y = tmp->elt.y;

                    }

                }

            }
        }

}

int Machine::ABrecherchemin( int profondeur , echequier &E,int a,int b )
{
    if(profondeur==0)
        return this->evaluerechequier(E);
    int alpha=a;int beta=b;
    int meilleurevaleur = 10000;
    coord loc,sol; coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifpiece(loc)) && (E.getpiece(loc)->joueur != this->couleur))
            {
                for (cCell<coord> *tmp = E.getpiece(loc)->possibilites.tete; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    echequier Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur);
                    Aux.deplacementlegal(this->couleur);
                    if (Aux.finpartie(this->couleur)) return (-999);
                    int valeur = ABrecherchemax(profondeur-1,Aux,alpha,beta);
                    if (valeur==999) return (999);
                    if( valeur < meilleurevaleur )
                    {
                        meilleurevaleur = valeur;
                        beta=valeur;
                    }
                    if(beta>alpha) return meilleurevaleur;


                }

            }
        }

        return meilleurevaleur;
}

int Machine::ABrecherchemax( int profondeur ,  echequier &E ,int a,int b)
{

    if(profondeur==0)
        return this->evaluerechequier(E);

    int meilleurevaleur = -10000;int alpha=a;int beta=b;
    coord loc,sol; coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifpiece(loc)) && (E.getpiece(loc)->joueur == this->couleur))
            {
                for (cCell<coord> *tmp = E.getpiece(loc)->possibilites.tete; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    echequier Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) return (999);
                    int valeur = ABrecherchemin(profondeur-1,Aux,alpha,beta);
                    if (valeur==999) return (999);
                    if( valeur > meilleurevaleur )
                    {
                        meilleurevaleur = valeur;
                        alpha=valeur;
                    }
                    if(beta<alpha) return meilleurevaleur;

                }

            }
        }

        return meilleurevaleur;

}

#endif // CLASSJOUEUR_H_INCLUDED
