#pragma once

#include "gameConfig.h"

class point
{
    int x, y;

public:
    point();
    point(int _x, int _y);


    void draw(char ch);
    void move(int direction);
    void setXY(int x, int y);
    void setX(int _x) { x = _x; }
    void setY(int _y) { y = _y; }
    int getX();
    int getY();

};
