#ifdef _WIN32
#include "..\Headers\settings.h"
#include "..\Headers\cal_point.h"
#endif

#ifdef __linux
#include "../Headers/settings.h"
#include "../Headers/cal_point.h"
#endif

#ifdef MACRO
#include "../Headers/settings.h"
#include "../Headers/cal_point.h"
#endif

void Block::down()
{
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).y -= BLOCK_SIZE;
    return;
}

void Block::left()
{
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).x -= BLOCK_SIZE;
    return;
}

void Block::right()
{
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).x += BLOCK_SIZE;
    return;
}

void Block::drop()
{
    double y = (this->points[0]).y - (BOTTOM_BORDER + BLOCK_SIZE / 2);
    for (int i = 0;i < (this->points).size();i++)
        (this->points[i]).y -= y;
    return;
}

bool Block::isTop()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).x >= TOP_BORDER - BLOCK_SIZE / 2)
            return true;
    return false;
}

bool Block::isBottom()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).y <= BOTTOM_BORDER + BLOCK_SIZE / 2)
            return true;
    return false;
}

bool Block::isLeft()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).x <= LEFT_BORDER + BLOCK_SIZE / 2)
            return true;
    return false;
}

bool Block::isRight()
{
    for (int i = 0;i < (this->points).size();i++)
        if ((this->points[i]).x >= RIGHT_BORDER - BLOCK_SIZE / 2)
            return true;
    return false;
}
