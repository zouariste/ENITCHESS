#include "player.h"

bool Human::decidermouvement(ChessBoard &E, Coord &ini, Coord &dest)
{
	if ((ini.verifcoord()) && (E.verifPiece(ini)) && (E.getPiece(ini)->joueur == this->couleur) && (!(E.getPiece(ini)->possibilites.listevide())) && (E.getPiece(ini)->possibilites.cherchechaine(dest)))
		return true;
	else
		return false;
}

Piece* Human::choosepiece()
{
	RenderWindow window(VideoMode(504, 380), "Choose-Piece-Menu");
	Texture t1, t2; 
	Sprite g[32];
	ChessBoard q; /*q.initChessBoard();
	affiche2(q, board);*/ int size = 56; int s = 0;
	t1.loadFromFile("images/Pieces.png");
	t2.loadFromFile("images/Choose-Piece-Menu.png");
	for (int i = 0; i < 32; i++) g[i].setTexture(t1);
	Sprite sBoard(t2);
	int k = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n>0 ? 1 : 0;
			g[k].setTextureRect(IntRect(56 * x, 56 * y, 56, 56));
			g[k].setPosition(-100,-100);
			k++;
		}
	if (this->couleur % 2 == 0)
	{
		g[0].setPosition(56 * 1, 56 * 4);
		g[1].setPosition(149.3, 56 * 4);
		g[2].setPosition(242.6, 56 * 4);
		g[3].setPosition(56 * 6, 56 * 4);
	}
	else
	{
		g[24].setPosition(56 * 1, 56 * 4);
		g[25].setPosition(149.3, 56 * 4);
		g[26].setPosition(242.6, 56 * 4);
		g[27].setPosition(56 * 6, 56 * 4);
	}


	window.draw(sBoard);
	for (int i = 0; i < 32; i++) g[i].move(offset);
	for (int i = 0; i < 32; i++) {
		window.draw(g[i]);
	}
	for (int i = 0; i < 32; i++) g[i].move(-offset);
	window.display();
	while (window.isOpen())
	{
		pos = Mouse::getPosition(window) - Vector2i(offset);
		Event e;
		while (window.pollEvent(e))
		{
			if (g[0].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Rook(2); 
						return p;
					}
			if (g[1].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Knight(2);
						return p;
					}
			if (g[2].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Bishop(2);
						return p;
					}
			if (g[3].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Queen(2);
						return p;
					}
			if (g[24].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Rook(1);
						return p;
					}
			if (g[25].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Knight(1);
						return p;
					}
			if (g[26].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Bishop(1);
						return p;
					}
			if (g[27].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						Piece *p = new Queen(1);
						return p;
					}


		}

	}
	//E.printchess(); system("pause");
	
}

void Machine::minimax( int depth , ChessBoard &E ,Coord &ini,Coord &sol)
{
    int valeur,meilleurevaleur = -10000;
	Coord loc;
	Coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifPiece(loc)) && (E.getPiece(loc)->joueur == this->couleur))
            {
                for (cCell<Coord> *tmp = E.getPiece(loc)->possibilites.head; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    ChessBoard Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) {ini.x = i;ini.y = j;sol.x = tmp->elt.x;sol.y = tmp->elt.y;return;}
                    valeur = this->findmin( depth-1 , Aux );
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

int Machine::findmin( int depth , ChessBoard &E )
{
    if(depth==0)
        return this->evaluerChessBoard(E);
	Coord temp;
    int meilleurevaleur = 10000;
    Coord loc,sol;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifPiece(loc)) && (E.getPiece(loc)->joueur != this->couleur))
            {
                for (cCell<Coord> *tmp = E.getPiece(loc)->possibilites.head; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    ChessBoard Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur);
                    Aux.deplacementlegal(this->couleur);
                    if (Aux.finpartie(this->couleur)) return (-999);

                    int valeur = -this->findmax( depth-1 , Aux );
                    if (valeur==999) return (999);
                    if ( valeur < meilleurevaleur )
                    {
                        meilleurevaleur = valeur;
                    }
                }
            }
        }
        return meilleurevaleur;
}

int Machine::findmax( int depth ,  ChessBoard &E )
{
    if(depth==0)
        {return this->evaluerChessBoard(E);}
	Coord temp;
    int meilleurevaleur = -10000;
    Coord loc,sol;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifPiece(loc)) && (E.getPiece(loc)->joueur == this->couleur))
            {
                for (cCell<Coord> *tmp = E.getPiece(loc)->possibilites.head; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    ChessBoard Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) return (999);
                    int valeur = this->findmin( depth-1 , Aux );
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

void Machine::ABminimax( int depth , ChessBoard &E ,Coord &ini,Coord &sol)
{
    int meilleurevaleur = -10000;
    Coord loc;
	Coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifPiece(loc)) && (E.getPiece(loc)->joueur == this->couleur))
            {
                for (cCell<Coord> *tmp = E.getPiece(loc)->possibilites.head; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    ChessBoard Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) {ini.x = i;ini.y = j;sol.x = tmp->elt.x;sol.y = tmp->elt.y;return;}
                    int valeur = ABrecherchemin( depth-1 , Aux ,-10000,10000);
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

int Machine::ABrecherchemin( int depth , ChessBoard &E,int a,int b )
{
    if(depth==0)
        return this->evaluerChessBoard(E);
    int alpha=a;int beta=b;
    int meilleurevaleur = 10000;
    Coord loc,sol; Coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifPiece(loc)) && (E.getPiece(loc)->joueur != this->couleur))
            {
                for (cCell<Coord> *tmp = E.getPiece(loc)->possibilites.head; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    ChessBoard Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur);
                    Aux.deplacementlegal(this->couleur);
                    if (Aux.finpartie(this->couleur)) return (-999);
                    int valeur = ABrecherchemax(depth-1,Aux,alpha,beta);
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

int Machine::ABrecherchemax( int depth ,  ChessBoard &E ,int a,int b)
{

    if(depth==0)
        return this->evaluerChessBoard(E);

    int meilleurevaleur = -10000;int alpha=a;int beta=b;
    Coord loc,sol; Coord temp;
    for(int i = 0; i < 8; i++ )
        for(int j = 0; j < 8; j++ )
        {
            loc.x=i;loc.y=j;
            if((E.verifPiece(loc)) && (E.getPiece(loc)->joueur == this->couleur))
            {
                for (cCell<Coord> *tmp = E.getPiece(loc)->possibilites.head; tmp != NULL; tmp = tmp->succ)
                {
                    temp.x=i,temp.y=j;
                    ChessBoard Aux=E;
                    Aux.mouvement(temp,tmp->elt,this);
                    Aux.deplacementnaif(this->couleur+1);
                    Aux.deplacementlegal(this->couleur+1);
                    if (Aux.finpartie(this->couleur+1)) return (999);
                    int valeur = ABrecherchemin(depth-1,Aux,alpha,beta);
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
