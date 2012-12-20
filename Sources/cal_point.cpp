#ifdef _WIN32
#include "..\Headers\components.h"
#endif

#ifdef __linux
#include "../Headers/components.h"
#endif

#ifdef MACRO
#include "../Headers/components.h"
#endif

void erase_row(int row)
{
    list<Point>::iterator p;
    for (int i = 0;i < block_list.size();i++)
    {
        p = block_list[i].points.begin();
        block_list[i].clear();
        while (p != block_list[i].points.end())
        {
            if ((*p).row == row)
            {
                p = block_list[i].points.erase(p);
                row_fill[row]--;
            }
            else if ((*p).row > row)
            {
                (*p).row--;
            }
            p++;
        }
        block_list[i].occupy();
    }
}

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
    p = (this->points).begin();
    return;
}

void Block::drop()
{
    clock_t previous,current;
    previous = clock();
    this->down();
    while (!(this->isBottom()))
    {
        if (current - previous >= dropspeed)
        {
            this->down();
            previous = clock();
        }
        current = clock();
    }
    return;
}

void Block::occupy()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        block_map[(*p).row][(*p).column] = 1;
        if (++row_fill[(*p).row] >= COLUMN)
            erase_row((*p).row);
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
    bool flag = false;
    while (p != (this->points).end())
        if (block_map[(*p).row - 1][(*p).column] == 1)
        {
            this->isStop = true;
            return true;
        }
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
    int tmpr,tmpc;
    while (p != (this->points).end())
    {
        tmpr = (*base).row - ((*p).column - (*base).column);
        tmpc = (*base).column + ((*p).row - (*base).row);
        (*p).row = tmpr;
        (*p).column = tmpc;
        p++;
    }
    while (this->isLeft())
        this->right();
    while (this->isRight())
        this->left();
    while (this->isTop())
        this->down();
}
