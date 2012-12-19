#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED
#include "settings.h"
using namespace std;

struct Point
{
    int x;
    int y;
    int z;

    Point(int xx = 0,int yy = 0,int zz = 0) : x(xx + COLUMN / 2),y(yy + ROW / 2),z(zz){}
};

class Block
{
public:
    Block()
    {
        points = list<Point>(BLOCK_NUM);
    }
    list<Point> points;
    void down();
    void left();
    void right();
    void drop();
    void rotate();
    bool isTop();
    bool isBottom();
    bool isLeft();
    bool isRight();
};

class S_Block: public Block
{
public:
    S_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(-1);
        *p++ = Point(0,1);
        *p++ = Point(1,1);
    }
};

class Z_Block: public Block
{
public:
    Z_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(1);
        *p++ = Point(0,1);
        *p++ = Point(-1,1);
    }
};

class L_Block: public Block
{
public:
    L_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(1);
        *p++ = Point(0,1);
        *p++ = Point(0,2);
    }
};

class J_Block: public Block
{
public:
    J_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(-1);
        *p++ = Point(0,1);
        *p++ = Point(0,2);
    }
};

class I_Block: public Block
{
public:
    I_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(0,1);
        *p++ = Point(0,2);
        *p++ = Point(0,3);
    }
};

class O_Block: public Block
{
public:
    O_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(0,1);
        *p++ = Point(1,0);
        *p++ = Point(1,1);
    }
};

class T_Block: public Block
{
public:
    T_Block()
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point();
        *p++ = Point(-1);
        *p++ = Point(1);
        *p++ = Point(0,1);
    }
};

#endif
