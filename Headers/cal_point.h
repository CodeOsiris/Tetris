#ifndef CAL_POINT_H_INCLUDED
#define CAL_POINT_H_INCLUDED
#include "settings.h"
using namespace std;

struct Point
{
    int x;
    int y;
    int z;

    Point(int xx = 0,int yy = 0,int zz = 0) : x(xx + START_X),y(yy + START_Y),z(zz){}
};

class Block
{
public:
    Block()
    {
        points = vector<Point>(BLOCK_NUM);
    }
    vector<Point> points;
    void down();
    void left();
    void right();
    void drop();
    virtual void rotate() = 0;
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
        points[0] = Point();
        points[1] = Point(-1);
        points[2] = Point(0,1);
        points[3] = Point(1,1);
    }
    void rotate();
};

class Z_Block: public Block
{
public:
    Z_Block()
    {
        points[0] = Point();
        points[1] = Point(1);
        points[2] = Point(0,1);
        points[3] = Point(-1,1);
    }
    void rotate();
};

class L_Block: public Block
{
public:
    L_Block()
    {
        points[0] = Point();
        points[1] = Point(1);
        points[2] = Point(0,1);
        points[3] = Point(0,2);
    }
    void rotate();
};

class J_Block: public Block
{
public:
    J_Block()
    {
        points[0] = Point();
        points[1] = Point(-1);
        points[2] = Point(0,1);
        points[3] = Point(0,2);
    }
    void rotate();
};

class I_Block: public Block
{
public:
    I_Block()
    {
        points[0] = Point();
        points[1] = Point(0,1);
        points[2] = Point(0,2);
        points[3] = Point(0,3);
    }
    void rotate();
};

class O_Block: public Block
{
public:
    O_Block()
    {
        points[0] = Point();
        points[1] = Point(0,1);
        points[2] = Point(1,0);
        points[3] = Point(1,1);
    }
    void rotate();
};

class T_Block: public Block
{
public:
    T_Block()
    {
        points[0] = Point();
        points[1] = Point(-1);
        points[2] = Point(1);
        points[3] = Point(0,1);
    }
    void rotate();
};

#endif
