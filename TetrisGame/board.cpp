#include <iostream>

#include "point.h"
#include "board.h"
#include "shape.h"
#include "utilities.h"

board::board(int pNum)
{
	for (int i = 0; i < 12; i++)
	{
		usedCoords[19][i] = 1;
	}
	if (pNum == 1)
		offset = gameConfig::P1OFFSET;
	else
		offset = gameConfig::P2OFFSET;
}

bool board::existInMat(point val)
{
	if (usedCoords[val.getY() ][val.getX() - offset] != 0) // changed x/y
		return true;
	else
		return false;
}

void board::print(int pNum)
{
	int offset = 0;
	if (pNum == 2)
		offset = 18;
	
	
	for (int i = 0; i < 19; i++)
	{
		cout << endl;
		for (int j = 0; j < 12; j++)
		{
			gotoxy(40 + offset + j, 0 + i);
			cout << usedCoords[i][j] << " ";
		}
	}
}

void board::update(point* p)
{
	for (int i = 0; i < 4; i++)
	{
		usedCoords[p[i].getY()][p[i].getX() - offset] = 1; //changed x/y
	}
}

bool board::isGameOver()
{
	for (int i = 0; i < 12; i++)
	{
		if (usedCoords[1][i] == 1)
			return true;
	}

	return false;
}

bool board::deleteLineAndUpdate()
{
	bool isDeleted = false;
	int height;
	for (int i = 0; i < 19; i++)
	{
		if (checkIfLineFull(usedCoords[i]))
		{
			isDeleted = true;
			deleteLine(usedCoords[i]);
			height = i;
			while (height > 0)
			{
				switchLines(usedCoords[height], usedCoords[height - 1]);
				height--;
			}	
		}
	}

	return isDeleted;
}

void board::syncBoardToDisplay()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			gotoxy(j + 1 + offset, i);
			if (usedCoords[i][j] == 0)
				cout << " ";
			else if (usedCoords[i][j] == 1)
				cout << "#";
		}
	}
}

bool checkIfLineFull(int* arr)
{
	for (int i = 0; i < 12; i++)
	{
		if (arr[i] == 0)
			return false;
	}

	return true;
}

void deleteLine(int* arr)
{
	for (int i = 0; i < 12; i++)
	{
		arr[i] = 0;
	}
}

void switchLines(int* under, int* upper)
{
	int temp;
	for (int i = 0; i < 12; i++)
	{
		temp = upper[i];
		upper[i] = under[i];
		under[i] = temp;
	}
}



