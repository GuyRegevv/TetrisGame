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
	srand(time(0));

	char key = 0;
	int dir;
	int startingKey = handleGameStart();

	board b1(1);
	board b2(2);
	
	bool currentshape1 = true;
	bool currentshape2 = true;

	if (startingKey == 1)
	{
		do {
			shape s1(1);
			shape s2(2);
			currentshape1 = true;
			currentshape2 = true;

			while ( currentshape1 || currentshape2 )
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
					handlePause();
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

					handleDrawing(s1, s2);

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

			handleFullLines(b1, b2);
			handleGameOver(b1, b2);

		} while (key != '9');
	}
}