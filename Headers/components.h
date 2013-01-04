#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED
#include "settings.h"
using namespace std;

bool judge_row();

struct Point
{
    int row;
    int column;
    int depth;

    int x;
    int y;
    int z;

    int parent;
    bool isOccupy;
    float color[3];

    Point(int p = 0,int r = 0,int c = 0,int d = 0,bool o = false) : parent(p),row(r),column(c),depth(d),x(c),y(r),z(d),isOccupy(o){}
};

class Block
{
public:
    Block(int br = 0,int bc = 0,int bd = 0) : base_row(br),base_column(bc),base_depth(bd)
    {
        points = list<Point>(BLOCK_NUM);
        isStop = false;
        index++;
    }

    list<Point> points;
    int base_row;
    int base_column;
    int base_depth;
    static int index;
    bool isStop;
    float color[3];
    char type;
    float fix_row;
    float fix_column;
    float fix_depth;

    void down();
    void left();
    void right();
    void forth();
    void back();
    void drop();
    void rotate_x();
    void rotate_y();
    void rotate_z();
    void occupy();
    void clear();
    bool isBottom();
    bool isTop();
    bool isLeft();
    bool isRight();
    bool isFront();
    bool isBack();
    float center_row();
    float center_column();
    float center_depth();
    int toBottom();
};

class S_Block: public Block
{
public:
    S_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column + 1,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column - 1,base_depth);
        color[0] = 0.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
        type = 'S';
    }
};

class L_Block: public Block
{
public:
    L_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column - 1,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth);
        *p++ = Point(this->index,base_row - 2,base_column,base_depth);
        color[0] = 1.0f;
        color[1] = 0.5f;
        color[2] = 0.0f;
        type = 'L';
    }
};

class I_Block: public Block
{
public:
    I_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column + 1,base_depth);
        *p++ = Point(this->index,base_row,base_column + 2,base_depth);
        *p++ = Point(this->index,base_row,base_column - 1,base_depth);
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 0.0f;
        type = 'I';
    }
};

class O_Block: public Block
{
public:
    O_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column - 1,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column - 1,base_depth);
        color[0] = 0.0f;
        color[1] = 1.0f;
        color[2] = 1.0f;
        type = 'O';
    }
};

class T_Block: public Block
{
public:
    T_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column - 1,base_depth);
        *p++ = Point(this->index,base_row,base_column + 1,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth);
        color[0] = 0.0f;
        color[1] = 1.0f;
        color[2] = 0.0f;
        type = 'T';
    }
};

class Y_Block: public Block
{
public:
    Y_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column - 1,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column,base_depth + 1);
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
        type = 'Y';
    }
};

class N_Block: public Block
{
public:
    N_Block(int br = 0,int bc = 0,int bd = 0) : Block(br,bc,bd)
    {
        list<Point>::iterator p = (this->points).begin();
        *p++ = Point(this->index,base_row,base_column,base_depth);
        *p++ = Point(this->index,base_row,base_column + 1,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth);
        *p++ = Point(this->index,base_row - 1,base_column,base_depth + 1);
        color[0] = 1.0f;
        color[1] = 0.0f;
        color[2] = 1.0f;
        type = 'N';
    }
};

extern vector<Block> block_list;
extern Point block_map[ROW + 2][COLUMN + 2][DEPTH + 2];
#endif
