#ifdef _WIN32
#include "..\Headers\components.h"
#endif

#ifdef __linux
#include "../Headers/components.h"
#endif

#ifdef MACRO
#include "../Headers/components.h"
#endif

void Block::down()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).y--;
    return;
}

void Block::left()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).x--;
    return;
}

void Block::right()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).x++;
    return;
}

void Block::drop()
{
    double low = 1.0;
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if ((*p).y < low)
            low = (*p).y;
        p++;
    }
    double d = low - (int)((BOTTOM_BORDER + BLOCK_SIZE / 2) / BLOCK_SIZE);
    p = (this->points).begin();
    while (p != (this->points).end())
        (*p).y -= d;
    return;
}

bool Block::isTop()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if ((*p++).y >= (int)(TOP_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

bool Block::isBottom()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if ((*p++).y <= (int)(BOTTOM_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

bool Block::isLeft()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if ((*p++).x <= (int)(LEFT_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

bool Block::isRight()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if ((*p++).x >= (int)(RIGHT_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

void Block::rotate()
{
    list<Point>::iterator base = (this->points).begin(),p = (this->points).begin();
    p++;
    while (p != (this->points).end())
    {
        if ((*p).x - (*base).x == 0)
        {
            (*p).x = (*base).x + ((*p).y - (*base).y);
            (*p).y = (*base).y;
        }
        else
        {
            (*p).y = (*base).y - ((*p).x - (*base).x);
            (*p).x = (*base).x;
        }
        p++;
    }
}
