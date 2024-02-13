#include <iostream>
#include <windows.h>
#include <process.h>
#include <ostream>
#include <conio.h> //for kbh and getch

#include "point.h"
#include "utilities.h"

using namespace std;

point::point()
{
    x = 1;
    y = 1;
}

point::point(int _x, int _y) : x(_x), y(_y)
{

}

void point::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}


void point::draw(char ch)
{
    gotoxy(x , y  );
    cout << ch << endl;
}

void point::move(int dir) //moving point by changing coordinats
{
    switch (dir) {
    case 0: // DOWN
        ++y;
        break;
    case 1: // LEFT
        --x;
        break;
    case 2: // RIGHT
        ++x;
        break;
    case 3 :
        ++y;
        break;
    }
}

int point::getX()
{
    return x;
}

int point::getY()
{
    return y;
}

void point::printPoint()
{
    cout << "(" << x << "," << y << ") ";
}