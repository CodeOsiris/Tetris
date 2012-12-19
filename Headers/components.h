#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED
#include "settings.h"
using namespace std;

struct Point
{
    int row;
    int column;
    int depth;

    int x;
    int y;
    int z;

    Point(int r = 0,int c = 0,int d = 0) : row(r),column(c),depth(d),x(c),y(r),z(d){}
};

class Block
{
public:
    Block(int br = 0,int bc = 0,int bd = 0) : base_row(br),base_column(bc),base_depth(bd)
    {
        points = list<Point>(BLOCK_NUM);
    }

    list<Point> points;
    int base_row;
    int base_column;
    int base_depth;

    void down();
    void left();
    void right();
    void drop();
    void rotate();
    void occupy();
    void clear();
    bool isBottom();
    bool isTop();
    bool isLeft();
    bool isRight();
};

class S_Block: public Block
{
public:
    S_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row,base_column + 1);
        *p++ = Point(base_row - 1,base_column);
        *p++ = Point(base_row - 1,base_column - 1);
    }
};

class Z_Block: public Block
{
public:
    Z_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row,base_column - 1);
        *p++ = Point(base_row - 1,base_column);
        *p++ = Point(base_row - 1,base_column + 1);
    }
};

class L_Block: public Block
{
public:
    L_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row,base_column - 1);
        *p++ = Point(base_row - 1,base_column);
        *p++ = Point(base_row - 2,base_column);
    }
};

class J_Block: public Block
{
public:
    J_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row,base_column + 1);
        *p++ = Point(base_row - 1,base_column);
        *p++ = Point(base_row - 2,base_column);
    }
};

class I_Block: public Block
{
public:
    I_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row,base_column + 1);
        *p++ = Point(base_row,base_column + 2);
        *p++ = Point(base_row,base_column - 1);
    }
};

class O_Block: public Block
{
public:
    O_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row - 1,base_column);
        *p++ = Point(base_row,base_column - 1);
        *p++ = Point(base_row - 1,base_column - 1);
    }
};

class T_Block: public Block
{
public:
    T_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(base_row,base_column);
        *p++ = Point(base_row,base_column - 1);
        *p++ = Point(base_row,base_column + 1);
        *p++ = Point(base_row - 1,base_column);
    }
};

#endif
