#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "prototype.h"
#include "echequier.h"
#include "classjoueur.h"
#include <unistd.h>

using namespace sf;
using namespace std;
Vector2f offset(28, 28);
int load = 0, load2 = 0;
int difsim = 0;
int board[8][8];
class Partie
{
public:
	echequier grille;
	Joueur* blanc;
	Joueur* noir;
	int nbtour;
	Partie();
	//~partie();
	void lancerjeu();
	void mouvement(coord ini, coord dest, Joueur *qui);
	friend ostream& operator<<(ostream&, Partie&);
	friend istream& operator>>(istream&, Partie&);
	void reprendrePartie();
	void sauvegarderPartie();
}; 

std::string position = "";
Vector2i pos;

std::string toChessNote(Vector2f p)
{
	std::string s = "";
	s += char(p.x / 56 + 97);
	s += char(7 - p.y / 56 + 49);
	return s;
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 7 - int(b) + 49;
	return Vector2f(x * 56, y * 56);
}

void affiche2(echequier &E, int board[8][8])
{
	int signe=0, p;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			coord loc; loc.x = i; loc.y = j;
			if (E.getpiece(loc) != NULL)
			{
				if (E.getpiece(loc)->joueur == 2)
					signe = -1;
				else
					signe = 1;
				switch (E.getpiece(loc)->valeur)
				{
				case 999:
					p = 5; break;
				case 1:
					p = 6; break;
				case 4:
					p = 2; break;
				case 3:
					p = 3; break;
				case 5:
					p = 1; break;
				case 10:
					p = 4; break;
				}
			}
			else
				p = 0;
			board[i][j] = p * signe;
		}


}

void move(std::string str,Sprite f[])
{
	Vector2f oldPos = toCoord(str[0], str[1]);
	Vector2f newPos = toCoord(str[2], str[3]);

	for (int i = 0; i<32; i++)
		if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

	for (int i = 0; i<32; i++)
		if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);

}

void loadPosition(int board[8][8],Sprite f[])
{
	int k = 0;
	for (int k=0;k<32;k++) f[k].setPosition(-1000,-1000);
	for (int i = 0; i<8; i++)
		for (int j = 0; j<8; j++)
		{
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n>0 ? 1 : 0;
			f[k].setTextureRect(IntRect(56 * x, 56 * y, 56, 56));
			f[k].setPosition(56 * j, 56 * i);
			k++;
		}

	for (int i = 0; i<position.length(); i += 5)
		move(position.substr(i, 4));
}

void menuchoix(int &mode)
{
	RenderWindow window(VideoMode(504, 604), "ENITCHESS");
	Texture t1, t2, t3, t4, t5, t6; Sprite f[5];
	t1.loadFromFile("images/Menu.png");
	t2.loadFromFile("images/1VS1.png");
	t3.loadFromFile("images/1VScpu1.png");
	t4.loadFromFile("images/1VScpu2.png");
	t5.loadFromFile("images/1VScpu3.png");
	t6.loadFromFile("images/1VScpu4.png");


	f[0].setTexture(t2);
	f[1].setTexture(t3);
	f[2].setTexture(t4);
	f[3].setTexture(t5);
	f[4].setTexture(t6);

	Sprite sBoard(t1);
	f[0].setPosition(56 * 2, 56 * 3);
	f[1].setPosition(56 * 2, 56 * 4);
	f[2].setPosition(56 * 2, 56 * 5);
	f[3].setPosition(56 * 2, 56 * 6);
	f[4].setPosition(56 * 2, 56 * 7);


	window.draw(sBoard);
	for (int i = 0; i < 5; i++) f[i].move(offset);
	for (int i = 0; i < 5; i++) {
		window.draw(f[i]);
	}
	for (int i = 0; i < 5; i++) f[i].move(-offset);
	window.display();
	while (window.isOpen())
	{
		pos = Mouse::getPosition(window) - Vector2i(offset);
		Event e;
		while (window.pollEvent(e))
		{
			if (f[0].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						mode = 1;
					}
			if (f[1].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						mode = 2;
					}
			if (f[2].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						mode = 3;
					}
			if (f[3].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						mode = 4;
					}
			if (f[4].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						mode = 5;
					}
		}
	}
}

void aide()
{
	RenderWindow window(VideoMode(504, 604), "ENITCHESS");
	Texture t1;
	t1.loadFromFile("images/aidee.png");



	Sprite sBoard(t1);


	window.draw(sBoard);
	window.display();
	while (window.isOpen())
	{
		pos = Mouse::getPosition(window) - Vector2i(offset);
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::MouseButtonPressed)
			{
				window.close();
			}


		}

	}

}

void menudeb(echequier &E, int &nbtour, int &mode,Partie *p)
{
	
	RenderWindow window(VideoMode(504, 604), "ENITCHESS");
	Texture t1, t2, t3, t4, t5; Sprite f[4];
	t1.loadFromFile("images/Menu.png");
	t2.loadFromFile("images/Commencer.png");
	t3.loadFromFile("images/Charger.png");
	t4.loadFromFile("images/Aide.png");
	t5.loadFromFile("images/Quitter.png");

	f[0].setTexture(t2);
	f[1].setTexture(t3);
	f[2].setTexture(t4);
	f[3].setTexture(t5);
	Sprite sBoard(t1);
	f[0].setPosition(56 * 2, 56 * 3);
	f[1].setPosition(56 * 2, 56 * 4);
	f[2].setPosition(56 * 2, 56 * 5);
	f[3].setPosition(56 * 2, 56 * 6);

	window.draw(sBoard);
	for (int i = 0; i < 4; i++) f[i].move(offset);
	for (int i = 0; i < 4; i++) {
		window.draw(f[i]);
	}
	for (int i = 0; i < 4; i++) f[i].move(-offset);
	window.display();
	while (window.isOpen())
	{
		pos = Mouse::getPosition(window) - Vector2i(offset);
		Event e;
		while (window.pollEvent(e))
		{
			if (f[0].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close(); 
						menuchoix(mode);
						nbtour = 1; break; break;
					}
			if (f[1].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						p->reprendrePartie();
						load = 1;
						
					}
			if (f[2].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						aide();
					}
			if (f[3].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						exit(0); 
					}

			

		}
		
	}

}

piece* Humain::choisirpiece()
{
	RenderWindow window(VideoMode(504, 380), "menuchoixpiece");
	Texture t1, t2; 
	Sprite g[32];
	echequier q; /*q.initechequier();
	affiche2(q, board);*/ int size = 56; int s = 0;
	t1.loadFromFile("images/figures.png");
	t2.loadFromFile("images/Menuchoixpiece.png");
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
						piece *p = new tour(2); 
						return p;
					}
			if (g[1].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new cheval(2);
						return p;
					}
			if (g[2].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new fou(2);
						return p;
					}
			if (g[3].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new reine(2);
						return p;
					}
			if (g[24].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new tour(1);
						return p;
					}
			if (g[25].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new cheval(1);
						return p;
					}
			if (g[26].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new fou(1);
						return p;
					}
			if (g[27].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close();
						piece *p = new reine(1);
						return p;
					}


		}

	}
	//E.printchess(); system("pause");
	
}

void menufin(echequier &E,int nbtour, int mode)
{

	RenderWindow window(VideoMode(504, 604), "ENITCHESS");
	Texture t1, t2, t3, t4, t5, t6, t7, t8; Sprite f[2];
	t1.loadFromFile("images/Menu fin.png");
	t2.loadFromFile("images/Joueur 1.png");
	t3.loadFromFile("images/Joueur 2.png");
	t4.loadFromFile("images/CPU1.png");
	t5.loadFromFile("images/CPU2.png");
	t6.loadFromFile("images/CPU3.png");
	t7.loadFromFile("images/CPU4.png");
	t8.loadFromFile("images/Recommencer.png");


	if (nbtour % 2) f[1].setTexture(t2);
	else
		switch (mode)
		{
		case 1:
			f[1].setTexture(t3); break;
		case 2:
			f[1].setTexture(t4); break;
		case 3:
			f[1].setTexture(t5); break;
		case 4:
			f[1].setTexture(t6); break;
		case 5:
			f[1].setTexture(t7); break;
		}
	f[0].setTexture(t8);
	Sprite sBoard(t1);
	f[1].setPosition(56 * 2, 56 * 2);
	f[0].setPosition(56 * 4 - 10, 56 * 8);

	window.draw(sBoard);
	for (int i = 0; i < 2; i++) f[i].move(offset);
	for (int i = 0; i < 2; i++) {
		window.draw(f[i]);
	}
	for (int i = 0; i < 2; i++) f[i].move(-offset);
	window.display();
	while (window.isOpen())
	{
		pos = Mouse::getPosition(window) - Vector2i(offset);
		Event e;
		while (window.pollEvent(e))
		{
			if (f[0].getGlobalBounds().contains(pos.x, pos.y))
				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
					{
						window.close(); usleep(200);
						Partie x; x.lancerjeu();
					}
		}
	}
}

Partie::Partie() //a remplacer pour save load et a ajouter deplacement legal NB elle utilise nbtour+1
{
	int nb,mode;
	menudeb(this->grille, nb, mode, this);
	this->nbtour=nb;
    this->blanc = new Humain;
	if (mode == 1)
		this->noir = new Humain;
	else
		this->noir = new Machine(mode);
    noir->couleur=2;
	blanc->couleur = 1; 
}

void essaye(Sprite &f,int x,int y)
{
	f.setPosition(56 * x, 56 * y);
}

void Partie::lancerjeu()
{
	Sprite f[35]; //figures
	RenderWindow window(VideoMode(504, 560), "ENITCHESS");
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10; 
	if (load == 0) this->grille.initechequier(); 
	this->grille.deplacementnaif(1);
	this->grille.deplacementnaif(2);
	affiche2(this->grille, board); int size = 56, s = 0;
	t1.loadFromFile("images/figures.png");
	t2.loadFromFile("images/board.png");
	t3.loadFromFile("images/Joueur 1.png");
	t4.loadFromFile("images/Joueur 2.png");
	t5.loadFromFile("images/CPU1.png");
	t6.loadFromFile("images/CPU2.png");
	t7.loadFromFile("images/CPU3.png");
	t8.loadFromFile("images/CPU4.png");
	t9.loadFromFile("images/Sauvegarder.png");



	int indice;
	coord ini, dest, loc;
	loc.x = 0; loc.y = 0; dest.x = 0; dest.y = 0; ini.x = 0; ini.y = 0;
	bool test = false;
	for (int i = 0; i < 32; i++) f[i].setTexture(t1);
	Sprite sBoard(t2);
	loadPosition(board,f);
	f[33].setTexture(t9); int mode = 1;
	f[34].setTexture(t3); 
	if (dynamic_cast<Machine*>(this->blanc))
	{
		s = 1; mode = 1;
	}
	else
		if (dynamic_cast<Machine*>(this->noir))
		{
			Machine * test = dynamic_cast<Machine*> (this->noir);
			mode = (test->difficulte);
		}
	if ((s == 0) && (load == 1)) mode = difsim+1;             load = 0;
	switch (mode)
	{
	case 1:
		f[32].setTexture(t4); break;
	case 2:
		f[32].setTexture(t5); break;
	case 3:
		f[32].setTexture(t6); break;
	case 4:
		f[32].setTexture(t7); break;
	case 5:
		f[32].setTexture(t8); break;

	}

	f[34].setPosition(56 * 0, 56 * 9);
	f[32].setPosition(56 * 0, 56 * 9);
	f[33].setPosition(56 * 5, 56 * 9);

	bool isMove = false, old = false;
	float dx = 0, dy = 0;
	Vector2f oldPos, newPos, var;
	std::string str;
	int n = 0;
	this->grille.deplacementnaif(nbtour + 1);	
	this->grille.deplacementnaif(nbtour);
	this->grille.deplacementlegal(nbtour);
	while (window.isOpen())
	{
		//if (load2) { window.close(); load2 = 0; break; }
		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
		Event e;

		while ((s == 0) && (window.pollEvent(e)) && ((mode == 1) || (nbtour % 2)))
		{
			if (e.type == Event::Closed)
				window.close();
			/////drag and drop///////

			if (f[33].getGlobalBounds().contains(pos.x, pos.y))
				if ((e.type == Event::MouseButtonPressed) && (e.key.code == Mouse::Left))
				{
					this->sauvegarderPartie(); window.close(); system("cls"); this->grille.initechequier();
					this->nbtour = 1; Partie x; x.lancerjeu();
				}

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					old = false;
					for (int i = 0; i < 32; i++)
						if (f[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true; n = i;
							dx = pos.x - f[i].getPosition().x;
							dy = pos.y - f[i].getPosition().y;
							oldPos = f[i].getPosition();
							indice = i;
							if (old == false)
							{
								var = f[i].getPosition(); old = true;
							}
						}

				}

			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left)
				{
					pos = Mouse::getPosition(window) - Vector2i(offset);
					isMove = false;
					Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
					newPos = Vector2f(size*int(p.x / size), size*int(p.y / size));
					ini.x = (int)oldPos.y / 56; ini.y = (int)oldPos.x / 56;
					dest.x = (int)newPos.y / 56; dest.y = (int)newPos.x / 56;
					//std::cout << ini.x << ' ' << ini.y << endl;
					//std::cout << dest.x << ' ' << dest.y << endl;
					if (nbtour % 2)
					{
						bool pion = false;
						test = this->blanc->decidermouvement(this->grille, ini, dest);
						if (test)
						{
							int x = this->grille.getpiece(ini)->valeur;
							this->grille.mouvement(ini, dest, blanc);
							if (x != this->grille.getpiece(dest)->valeur)
							{
								window.close(); load = 1;
								this->lancerjeu(); break; break;
								
							}


							this->grille.deplacementnaif(nbtour + 1);
							this->grille.deplacementlegal(nbtour);
						}
					}
					else
					{
						test = this->noir->decidermouvement(this->grille, ini, dest);
						if (test)
						{
							int x = this->grille.getpiece(ini)->valeur;
							this->grille.mouvement(ini, dest, noir);
							if (x != this->grille.getpiece(dest)->valeur)
							{
								window.close(); load = 1;
								this->lancerjeu(); break; break;
							}
							this->grille.deplacementnaif(nbtour + 1);
							this->grille.deplacementlegal(nbtour);
							
						}
					}
					if (test)
					{
						str = toChessNote(oldPos) + toChessNote(newPos);
						move(str,f);
						if (oldPos != newPos) position += str + " ";
						f[n].setPosition(newPos);
						//this->grille.printchess();
						if (this->grille.finpartie(nbtour + 1))
						{
							window.close();
							menufin(this->grille, nbtour, mode);
							 break; break;
						}
						this->nbtour++;
						

					}
					else
						if (old == true) {
						    old = false;
							f[indice].setPosition(var);
						}

				}

		}
		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < 32; i++) f[i].move(offset);
		for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);  window.draw(f[33]); if ((this->nbtour) % 2) window.draw(f[34]); else window.draw(f[32]);
		for (int i = 0; i < 32; i++) f[i].move(-offset);
		window.display();
		if ((s == 1) || ((mode != 1)&&(nbtour%2==0)) )
		{
			this->grille.deplacementnaif(nbtour + 1);
			this->grille.deplacementlegal(nbtour);
			if (nbtour%2)
				test = this->blanc->decidermouvement(this->grille, ini, dest);
			else
				test = this->noir->decidermouvement(this->grille, ini, dest);
			
			if (test)
			{	
				oldPos.x 
					= ini.y * 56; oldPos.y = ini.x * 56;
				newPos.x = dest.y * 56; newPos.y = dest.x * 56;
				for (int i = 0; i < 32; i++)
					if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

				for (int i = 0; i < 32; i++)
					if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);

				if (nbtour % 2)
				{
					int x = this->grille.getpiece(ini)->valeur;
					this->grille.mouvement(ini, dest, blanc);
					if (x != this->grille.getpiece(dest)->valeur)
					{
						window.close(); load = 1;
						this->lancerjeu(); break; break;
					}
				}
				else
				{
					int x = this->grille.getpiece(ini)->valeur;
					this->grille.mouvement(ini, dest, noir);
					if (x != this->grille.getpiece(dest)->valeur)
					{
						window.close(); load = 1;
						this->lancerjeu(); break; break;
					}
				}
				this->grille.deplacementnaif(nbtour + 1);
				this->grille.deplacementlegal(nbtour);

				//std::cout << "mouvement"<<ini.x << ' ' << ini.y << ' ' << dest.x << ' ' << dest.y << endl;
				if (this->grille.finpartie(nbtour))
				{
					window.close(); menufin(this->grille, nbtour, mode);
				}
				usleep(500);
				this->nbtour++;


			}
		}
		if (isMove) f[n].setPosition(pos.x - dx, pos.y - dy);
		
		////// dessiner le tout  ///////
		window.clear();
		window.draw(sBoard);
		for (int i = 0; i < 32; i++) f[i].move(offset);
		for (int i = 0; i < 32; i++) window.draw(f[i]); window.draw(f[n]);  window.draw(f[33]); if ((this->nbtour) % 2) window.draw(f[34]); else window.draw(f[32]);
		for (int i = 0; i < 32; i++) f[i].move(-offset);
		window.display(); 
	}
}

void Partie::reprendrePartie()
{
	int ligne, colonne, valeur, joueur; coord x; int difficulte;
	std::string chemin;
	cout << "Tapez le chemin:" << endl;
	cin >> chemin;
	ifstream fichier(chemin.c_str());
	if (fichier.is_open())
	{

		int n;
		fichier >>  this->nbtour;
		fichier >> difficulte;
		if (difficulte == 0) this->blanc = new Humain; else this->blanc = new Machine(difficulte);
		fichier >> difficulte;
		if (difficulte == 0) this->noir = new Humain; else this->noir = new Machine(difficulte);
		difsim = difficulte;
		this->noir->couleur = 2; this->blanc->couleur = 1;
		while (fichier >> ligne >> colonne >> valeur >> joueur)
		{
			x.x = ligne; x.y = colonne;
			piece *input=NULL;
			switch (valeur)
			{
			case 999:
				input = new roi(joueur); break;
			case 1:
				input = new pion(joueur); break;
			case 4:
				input = new cheval(joueur); break;
			case 3:
				input = new fou(joueur); break;
			case 5:
				input = new tour(joueur); break;
			case 10:
				input = new reine(joueur); break;
			}
			this->grille.setpiece(input, x);
		}
		fichier.close();
		this->grille.deplacementnaif(this->nbtour + 1);
		this->grille.deplacementlegal(this->nbtour); load = 1;
		this->lancerjeu();
	}
	else
		cout << "erreur:fichier introuvable" << endl;
}

void Partie::sauvegarderPartie()
{
	std::string chemin;
	cout << "Tapez le chemin:" << endl;
	cin >> chemin;
	ofstream fichier(chemin.c_str(), ios::trunc);
	coord x;
	fichier << this->nbtour << endl;
	fichier << this->blanc->demandersauvegarde() << endl;
	fichier << this->noir->demandersauvegarde() << endl;
	for (int ligne = 0; ligne < 8; ligne++)
	{
		for (int colonne = 0; colonne < 8; colonne++)
		{
			x.x = ligne; x.y = colonne;
			if (this->grille.verifpiece(x))
				fichier << ligne << " " << colonne << " " << this->grille.getpiece(x)->valeur << " " << this->grille.getpiece(x)->joueur << endl;
		}
	}
}

#endif // PARTIE_H_INCLUDED
