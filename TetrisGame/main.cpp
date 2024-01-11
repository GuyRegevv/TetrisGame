#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch

#include "gameConfig.h"
#include "utilities.h"
#include "point.h"
#include "shape.h"

using namespace std;

int main()
{
	drawBorder();

	point p(6, 1);
	shape s;
	char key = ' ';
	int dir;

	do {
		if (_kbhit())
		{
			key = _getch();
			if (key == '9')
			break;
			else
			{
				if ((dir = s.getDirection(key)) != -1)
					s.setDirection(dir);

				s.drawShape('#');
				Sleep(500);
				s.drawShape(' ');
				s.moveShape();
			}
		}

	} while (key != '9');
}