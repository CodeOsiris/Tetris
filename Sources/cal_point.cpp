#ifdef _WIN32
#include "..\Headers\components.h"
#endif

#ifdef __linux
#include "../Headers/components.h"
#endif

#ifdef MACRO
#include "../Headers/components.h"
#endif

int Block::index = 0;

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

void Block::forth()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).depth++;
    p = (this->points).begin();
    return;
}

void Block::back()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
        (*p++).depth--;
    p = (this->points).begin();
    return;
}

void Block::drop()
{
    while (!this->isBottom())
    {
        this->down();
    }
}

void erase_row(int row)
{
    list<Point>::iterator p;
    for (int i = 1;i < ROW;i++)
    {
        for (int j = 1;j <= COLUMN;j++)
            for (int k = 1;k <= DEPTH;k++)
                block_map[i][j][k] = block_map[i + 1][j][k];
        level_fill[i] = level_fill[i + 1];
    }
    for (int j = 1;j <= COLUMN;j++)
        for (int k = 1;k <= DEPTH;k++)
            block_map[ROW][j][k] = Point(0,ROW,j,k,false);
    level_fill[ROW] = 0;
}

bool judge_row(){
    for (int i = 1; i <= ROW; i++)
        if (level_fill[i] >= COLUMN * DEPTH)
        {
            erase_row(i);
            return true;
        }
    return false;
}

void Block::occupy()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        block_map[p->row][p->column][p->depth].parent = this->index;
        block_map[p->row][p->column][p->depth].isOccupy = true;
        level_fill[p->row]++;
        for (int i = 0;i < 3;i++)
            block_map[p->row][p->column][p->depth].color[i] = this->color[i];
        p++;
    }
}

void Block::clear()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        block_map[p->row][p->column][p->depth].parent = 0;
        block_map[p->row][p->column][p->depth].isOccupy = false;
        for (int i = 0;i < 3;i++)
            block_map[p->row][p->column][p->depth].color[i] = 0.0f;
        p++;
    }
}

bool Block::isBottom()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if (block_map[p->row - 1][p->column][p->depth].parent == this->index)
        {
            p++;
            continue;
        }
        else if (block_map[p->row - 1][p->column][p->depth].isOccupy == true)
            return true;
        else p++;
    }
    return false;
}

bool Block::isTop()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if (block_map[p->row + 1][p->column][p->depth].parent == this->index)
        {
            p++;
            continue;
        }
        else if (block_map[p->row + 1][p->column][p->depth].isOccupy == true)
            return true;
        else p++;
    }
    return false;
}

bool Block::isLeft()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if (block_map[p->row][p->column - 1][p->depth].parent == this->index)
        {
            p++;
            continue;
        }
        else if (block_map[p->row][p->column - 1][p->depth].isOccupy == true)
            return true;
        else p++;
    }
    return false;
}

bool Block::isRight()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if (block_map[p->row][p->column + 1][p->depth].parent == this->index)
        {
            p++;
            continue;
        }
        else if (block_map[p->row][p->column + 1][p->depth].isOccupy == true)
            return true;
        else p++;
    }
    return false;
}

bool Block::isFront()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if (block_map[p->row][p->column][p->depth + 1].parent == this->index)
        {
            p++;
            continue;
        }
        else if (block_map[p->row][p->column][p->depth + 1].isOccupy == true)
            return true;
        else p++;
    }
    return false;
}

bool Block::isBack()
{
    list<Point>::iterator p = (this->points).begin();
    while (p != (this->points).end())
    {
        if (block_map[p->row][p->column][p->depth - 1].parent == this->index)
        {
            p++;
            continue;
        }
        else if (block_map[p->row][p->column][p->depth - 1].isOccupy == true)
            return true;
        else p++;
    }
    return false;
}

void Block::rotate_z()
{
    list<Point>::iterator p = (this->points).begin();
    Point base(this->index,this->center_row(),this->center_column(),this->center_depth());
    int tmpr,tmpc;
    while (p != (this->points).end())
    {
        tmpr = base.row - (p->column - base.column);
        tmpc = base.column + (p->row - base.row);
        p->row = tmpr;
        p->column = tmpc;
        p++;
    }
    if (this->fix_row * this->fix_column > 0)
        this->fix_column = -this->fix_column;
    else this->fix_row = -this->fix_row;
    while (this->isLeft())
        this->right();
    while (this->isRight())
        this->left();
    while (this->isTop())
        this->down();
}

float Block::center_row()
{
    return ((this->points).begin())->row + fix_row;
}

float Block::center_column()
{
    return ((this->points).begin())->column + fix_column;
}

float Block::center_depth()
{
    return ((this->points).begin())->depth + fix_depth;
}
