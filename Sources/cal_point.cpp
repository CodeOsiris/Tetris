#ifdef _WIN32
#include "..\Headers\cal_point.h"
#endif

#ifdef __linux
#include "../Headers/cal_point.h"
#endif

#ifdef MACRO
#include "../Headers/cal_point.h"
#endif

void Block::down()
{
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).y--;
    return;
}

void Block::left()
{
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).x--;
    return;
}

void Block::right()
{
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).x++;
    return;
}

void Block::drop()
{
    double y = (this->points[0]).y - (int)((BOTTOM_BORDER + BLOCK_SIZE / 2) / BLOCK_SIZE);
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).y -= y;
    return;
}

bool Block::isTop()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).y >= (int)(TOP_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

bool Block::isBottom()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).y <= (int)(BOTTOM_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

bool Block::isLeft()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).x <= (int)(LEFT_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

bool Block::isRight()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).x >= (int)(RIGHT_BORDER / BLOCK_SIZE))
            return true;
    return false;
}

void S_Block::rotate()
{
}

void Z_Block::rotate()
{
}

void L_Block::rotate()
{
}

void J_Block::rotate()
{
}

void I_Block::rotate()
{
}

void O_Block::rotate()
{
}

void T_Block::rotate()
{
}
