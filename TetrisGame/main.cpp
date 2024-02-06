/*#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch

#include "gameConfig.h"

#include "point.h"
#include "shape.h"
#include "board.h"
*/
#include "utilities.h"
#include <iostream>
#include "Starter.h"
using namespace std;

int main()
{
	Starter *s = new Starter;
	int newGame;
	newGame = s->lunch();
	while (newGame == 1)
	{
		clrscr();
		s = new Starter;
		newGame = s->lunch();
	}

	delete s;
	exit(1);
	return 0;
}