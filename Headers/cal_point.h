#ifndef CAL_POINT_H_INCLUDED
#define CAL_POINT_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <GL\glut.h>
#endif

#ifdef __linux
#include <GL/glut.h>
#endif

#ifdef MACRO
#include <GL/glut.h>
#endif

using namespace std;

//Basic Settings
const float BLOCK_SIZE = 0.05f;
const int BLOCK_NUM = 4;
const float LEFT_BORDER = -1.0f + BLOCK_SIZE / 2;
const float RIGHT_BORDER = 0.5f - BLOCK_SIZE / 2;
const float UP_BORDER = 1.0f - BLOCK_SIZE / 2;
const float DOWN_BORDER = -1.0f + BLOCK_SIZE / 2;

struct Point
{
    double x;
    double y;
    double z;

    Point(double xx = 0, double yy = 0, double zz = 0) : x(xx), y(yy), z(zz){}
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
    //virtual void rotate() = 0;
};

class S_Block: public Block
{
public:
    S_Block()
    {
        points[0] = Point();
        points[1] = Point(-BLOCK_SIZE);
        points[2] = Point(0,BLOCK_SIZE);
        points[3] = Point(BLOCK_SIZE,BLOCK_SIZE);
    }
};

class Z_Block: public Block
{
public:
    Z_Block()
    {
        points[0] = Point();
        points[1] = Point(BLOCK_SIZE);
        points[2] = Point(0,BLOCK_SIZE);
        points[3] = Point(-BLOCK_SIZE,BLOCK_SIZE);
    }
};

class L_Block: public Block
{
public:
    L_Block()
    {
        points[0] = Point();
        points[1] = Point(BLOCK_SIZE);
        points[2] = Point(0,BLOCK_SIZE);
        points[3] = Point(0,BLOCK_SIZE * 2);
    }
};

class J_Block: public Block
{
public:
    J_Block()
    {
        points[0] = Point();
        points[1] = Point(-BLOCK_SIZE);
        points[2] = Point(0,BLOCK_SIZE);
        points[3] = Point(0,BLOCK_SIZE * 2);
    }
};

class I_Block: public Block
{
public:
    I_Block()
    {
        points[0] = Point();
        points[1] = Point(0,BLOCK_SIZE);
        points[2] = Point(0,BLOCK_SIZE * 2);
        points[3] = Point(0,BLOCK_SIZE * 3);
    }
};

class O_Block: public Block
{
public:
    O_Block()
    {
        points[0] = Point();
        points[1] = Point(0,BLOCK_SIZE);
        points[2] = Point(BLOCK_SIZE,0);
        points[3] = Point(BLOCK_SIZE,BLOCK_SIZE);
    }
};

class T_Block: public Block
{
public:
    T_Block()
    {
        points[0] = Point();
        points[1] = Point(-BLOCK_SIZE);
        points[2] = Point(BLOCK_SIZE);
        points[3] = Point(0,BLOCK_SIZE);
    }
};

#endif
