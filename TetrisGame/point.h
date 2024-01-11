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

};

