#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch

#include "gameConfig.h"
#include "utilities.h"
#include "point.h"
#include "shape.h"
#include "board.h"

using namespace std;

int main()
{
	int startingKey;
	startingKey = printMenuAndSelect();
	clrscr();
	//startingKey = _getch();
	board b1(1);
	board b2(2);

	drawBorder(gameConfig::P1OFFSET);
	drawBorder(gameConfig::P2OFFSET);
	
	char key = 0, check = 0;
	int dir;
	bool currentshape1 = true;
	bool currentshape2 = true;

	if (startingKey == 1)
	{

	do {
		shape s1(1);
		shape s2(2);

		
		currentshape1 = true;
		currentshape2 = true;
		while (currentshape1 || currentshape2 )

		{
			fflush(stdin);
			if (_kbhit())
				key = _getch();
			if (key == '9')
			{
				gotoxy(0, 20);
				gameOver();
			}
			else if (key == '8')
			{
				gotoxy(50, 10);
				cout << "Game Paused";
				fflush(stdin);
				while (true)
				{
					if (_kbhit())
						check = _getch();
					if (check == '2')
					{
						gotoxy(50, 10);
						cout << "             ";
						break;
					}
				}

				check = 0;
				key = 0;
			}
			else
			{
				if ((dir = s1.getDirection(key)) != -1)
				{
					s1.setDirection(dir);
					currentshape1 = s1.moveShape(b1);
				}
				
				if ((dir = s2.getDirection(key)) != -1)
				{
					s2.setDirection(dir);
					currentshape2 = s2.moveShape(b2);
				}

				s1.drawShape('#');
				s2.drawShape('#');
				Sleep(200);
				s1.drawShape(' ');
				s2.drawShape(' ');
				currentshape1 = s1.moveShape(b1);
				currentshape2 = s2.moveShape(b2);

				key = 0;
				fflush(stdin);

				}
			
		}

		b1.update(s1.getBody());
		b2.update(s2.getBody());
		s1.drawShape('#');
		s2.drawShape('#');

		if (b1.deleteLineAndUpdate()) 
			b1.syncBoardToDisplay();

		if (b2.deleteLineAndUpdate())
			b2.syncBoardToDisplay();
		
		if (b1.isGameOver())
			gameOver(); 

		if (b2.isGameOver())
			gameOver();

	} while (key != '9');
	}
}