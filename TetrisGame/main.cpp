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
	board b1;

	drawBorder();
	
	point p(6, 1);
	//shape s;
	char key = 0;
	int dir;
	bool currentshape = true;

	do {
		shape s;
		currentshape = true;
		while (currentshape)
		{
			if (_kbhit())
				key = _getch();
			if (key == '9')
			{
				gotoxy(0, 20);
				gameOver();
			}
			else
			{
				
					if ((dir = s.getDirection(key)) != -1)
					{
						s.setDirection(dir);
						currentshape = s.moveShape(b1);
					}

					s.drawShape('#');
					Sleep(500);
					s.drawShape(' ');
					currentshape = s.moveShape(b1);
					key = 0;
					fflush(stdin);
				}
			
		}

		b1.update(s.getBody());
		s.drawShape('#');

		if (b1.deleteLineAndUpdate()) //kind of working :/
			b1.syncBoardToDisplay();
		
		if (b1.isGameOver())
			gameOver();


		/*cout << endl;
		cout << endl;
		cout << endl;
		cout << endl; cout << endl;
		b1.print();
		cout << endl;
		cout << endl;
		cout << "x: " << s.getBody()[0].getX() << "y: " << s.getBody()[0].getY() << endl;
		Sleep(10000);
		cout << endl;
		cout << endl;*/

	} while (key != '9');
}