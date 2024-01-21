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

	char key = 0; //Setting Defult direction - Down
	int dir;
	int startingKey = handleGameStart(); //Menu presentetion and selection
	//creating 2 new boards
	board b1(1); 
	board b2(2);
	// bool flags to indicate when a shape finished its turn, and a new one needs to be created.
	bool currentshape1 = true;
	bool currentshape2 = true;

	//game starts
	if (startingKey == 1)
	{
		do {
			//two new shapes created. for each round
			shape s1(1);
			shape s2(2);
			currentshape1 = true;
			currentshape2 = true;
			while ( currentshape1 || currentshape2 )
			{
				fflush(stdin);
				if (_kbhit())
					key = _getch();
				//exit game when selecting 9
				if (key == '9') 
					gameOver();
				//pausing game when selecting 8, resuming when selecting 2	
				else if (key == '8')
				{
					handlePause();
					key = 0;
				}
				else
				{
					//setting direction according to selected key, and moving coordinates.
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

					//drawing shapes
					handleDrawing(s1, s2);
					//as long as nothing being pressed, shapes are moving down.
					currentshape1 = s1.moveShape(b1);
					currentshape2 = s2.moveShape(b2);
					key = 0;
					fflush(stdin);
					}
			}
			
			//end of round,
			// updating the board matrix
			b1.update(s1.getBody());
			b2.update(s2.getBody());
			//drawing the shapes in the place they landed
			s1.drawShape('#');
			s2.drawShape('#');
			//check for full lines and delete.
			handleFullLines(b1, b2);
			//check if game is over
			handleGameOver(b1, b2);

		} while (key != '9');
	}
}