#include <iostream>
#include <vector>
#include "point.h"
#include "board.h"
#include "shape.h"
#include "utilities.h"
#include "optionalMove.h"

board::board(int pNum) //bottom line filled with 1's to represent the floor.
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

bool board::existInMat(point val) const //checking if that space is free
{
	if (usedCoords[val.getY() ][val.getX() - offset] != 0) // changed x/y
		return true;
	else
		return false;
}

void board::print(int pNum) const
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

void board::update(shape& s) //updates matrix once a shape reached down.
{	
	point* p = s.getBody();

	if (s.getSymbol() == '@') //is a bomb
	{
		bombExplotion(p, *this);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			usedCoords[p[i].getY()][p[i].getX() - offset] = 1; //changed x/y
		}
	}

}

bool board::isGameOver() const //game over if shapes reached top line
{
	for (int i = 0; i < 12; i++)
	{
		if (usedCoords[1][i] == 1)
			return true;
	}

	return false;
}

bool board::deleteLineAndUpdate() //once a full line is found, that line is deleted, then "bubbled" up to the top of the board. 
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

void board::syncBoardToDisplay() //printing the current board state
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

point* board::bestMove(shape& s)
{
	vector<point*> possibleMoves = findPossibleMoves(s);
	vector<point*> movesThatdeleted = movesThatDeleteLines(possibleMoves);

	if (movesThatdeleted.empty())
		return lowestMove(possibleMoves);
	else
		return lowestMove(possibleMoves);
}

vector <point*> board::findPossibleMoves(shape& s)
{
	vector <point*> bodyPosPossibleArr;
	point* p;
	shape shapeCopy = s;
	shapeCopy.stickShapeToLeftBorder(*this);
	bool needToinsert;
	bool canMoveRight = true;
	int heightDiff;
	for (int i = 0; i < 4; i++)
	{
		canMoveRight = true;
		while (canMoveRight)
		{
			shape upperLineShape(shapeCopy);

			shapeCopy.setDirection(0); //drop
			shapeCopy.moveShape(*this);        

			heightDiff = upperLineShape.getBody()[0].getY() - shapeCopy.getBody()[0].getY();

			needToinsert = isFitted(*this, shapeCopy);
			if (needToinsert)
			{
				point* insert = new point[4];
				insert[0] = shapeCopy.getBody()[0];
				insert[1] = shapeCopy.getBody()[1];
				insert[2] = shapeCopy.getBody()[2];
				insert[3] = shapeCopy.getBody()[3];
				bodyPosPossibleArr.push_back(insert);
			}

			shapeCopy.moveShapeUpBy(heightDiff);
			shapeCopy.setDirection(2); //right
			canMoveRight = shapeCopy.moveShape(*this);
		}

		shapeCopy.stickShapeToLeftBorder(*this);
		shapeCopy.rotateShape();
	}

	return bodyPosPossibleArr;
}

vector <point*> board::movesThatDeleteLines(vector <point*> points) //not checked
{
	bool isDeleted = false;
	shape dummyShape(1);
	vector <point*> resArr;

	for (const auto& p : points)
	{
		dummyShape.updateBody(p);
		update(dummyShape);
		
		for (int i = 0; i < 19; i++)
			if (checkIfLineFull(usedCoords[i]))
				isDeleted = true;

		deleteShapeFromBoard(dummyShape);
		if (isDeleted)
			resArr.push_back(dummyShape.getBody());

		isDeleted = false;
	}

	return resArr;
}

void board::deleteShapeFromBoard(shape& s)
{
	for (int i = 0; i < 4; i++)
	{
		usedCoords[s.getBody()[i].getY()][s.getBody()[i].getX() - offset] = 0;
	}
}

void board::typeInput(int pNum)
{
	cout << "Enter Player " << pNum << " type " << endl << "c For Computer / h For Human" << endl;
	cin >> pType;
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
void bombExplotion(point* p, board& b)
{
	int midX = p[0].getX() - b.offset;
	int midY = p[0].getY();
	int currX = midX, currY = midY;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			currY = midY - 1 + i;
			currX = midX - 1 + j;
			if (currY < 19 && (currX > 0 && currX < 12))
			{
				b.usedCoords[currY][currX] = 0;
				gotoxy(currX + b.offset, currY);
				cout << " ";
			}
		}
	}
}
bool board::isFitted(const board& b, shape& s) const
{
	bool pos1, pos2, pos3, pos4;
	pos1 = b.existInMat(s.getBody()[0]);
	pos2 = b.existInMat(s.getBody()[1]);
	pos3 = b.existInMat(s.getBody()[2]);
	pos4 = b.existInMat(s.getBody()[3]);

	if (pos1 == false && pos2 == false && pos3 == false && pos4 == false)
		return true;
	else
		return false;
}



