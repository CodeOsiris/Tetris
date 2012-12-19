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
        (*p++).row--;
    return;
}

void Block::left()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).column--;
    return;
}

void Block::right()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).column++;
    return;
}

void Block::drop()
{
    while (!(this->isBottom()))
        this->down();
    return;
}

void Block::occupy()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        block_map[(*p).row][(*p).column] = 1;
        p++;
    }
}

void Block::clear()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        block_map[(*p).row][(*p).column] = 0;
        p++;
    }
}

bool Block::isBottom()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if (block_map[(*p).row - 1][(*p).column] == 1)
            return true;
        else p++;
    return false;
}

bool Block::isTop()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if (block_map[(*p).row + 1][(*p).column] == 1)
            return true;
        else p++;
    return false;
}

bool Block::isLeft()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if (block_map[(*p).row][(*p).column - 1] == 1)
            return true;
        else p++;
    return false;
}

bool Block::isRight()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        if (block_map[(*p).row][(*p).column + 1] == 1)
            return true;
        else p++;
    return false;
}

void Block::rotate()
{
    list<Point>::iterator base = (this->points).begin(),p = (this->points).begin();
    p++;
    while (p != (this->points).end())
    {
        (*p).column = (*base).column + ((*p).row - (*base).row);
        (*p).row = (*base).row - ((*p).column - (*base).column);
        p++;
    }
    while (this->isLeft())
        this->right();
    while (this->isRight())
        this->left();
    while (this->isTop())
        this->down();
}
