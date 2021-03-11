#include "prototype.h"
#include "echequier.h"
#include "classpiece.h"
#include "classjoueur.h"
#include "partie.h"
#include "time.h"
using namespace std;

int main()
{
	
	Partie x; 
	//Pour Simuler une partie veuillez Choisir la difficult� respective
	//x.blanc = new Machine(2);	x.noir = new Machine(1); x.blanc->couleur = 1; x.noir->couleur = 2;
	x.lancerjeu();
}
