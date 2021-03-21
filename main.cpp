#include "src/utils.h"
#include "src/chessboard.h"
#include "src/piece.h"
#include "src/player.h"
#include "src/game.h"
#include "time.h"
using namespace std;

int main()
{
	
	Partie x; 
	//Pour Simuler une game veuillez Choisir la difficult� respective
	//x.blanc = new Machine(2);	x.noir = new Machine(1); x.blanc->couleur = 1; x.noir->couleur = 2;
	x.lancerjeu();
}
