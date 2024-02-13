//second commit
//up to date
#include "utilities.h"
#include <iostream>
#include "Starter.h"
using namespace std;

int main()
{
	Starter* s = new Starter;
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