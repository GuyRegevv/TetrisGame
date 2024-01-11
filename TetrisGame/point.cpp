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
    gotoxy(x, y);
    cout << ch << endl;
}

void point::move(int dir)
{
    switch (dir) {
    case 0: // DOWN
        ++y;
        if (y > 18) {
            y = 1;
        }
        break;
    case 1: // LEFT
        --x;
        if (x < 1) {
            x = 1;
        }
        break;
    case 2: // RIGHT
        ++x;
        if (x > 12) {
            x = 12;
        }
        break;
    }
}


