#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED
#include "settings.h"
using namespace std;

//游戏组件声明

bool judge_row(); //用于判断是否要进行消除

//方块类
struct Point
{
    int row; //方块所在行
    int column; //方块所在列
    int depth; //方块所在层

    int x; //方块x坐标
    int y; //方块y坐标
    int z; //方块z坐标

    int parent; //方块所属积木标号，未被占有的方块标号为0
    bool isOccupy; //标记当前方块是否被占据
    float color[3]; //方块RGB颜色

    Point(int p = 0,int r = 0,int c = 0,int d = 0,bool o = false) : parent(p),row(r),column(c),depth(d),x(c),y(r),z(d),isOccupy(o){}
};

//积木类
class Block
{
public:
    Block(int br = 0,int bc = 0,int bd = 0) : base_row(br),base_column(bc),base_depth(bd)
    {
        points = list<Point>(BLOCK_NUM);
        isStop = false;
        index++;
    }

    list<Point> points; //积木包含的方块列表
    int base_row; //积木旋转基点的初始行
    int base_column; //积木旋转基点的初始列
    int base_depth; //积木旋转基点的初始层
    static int index; //积木标号
    bool isStop; //标记积木是否已停止运动
    float color[3]; //积木整体RGB颜色
    char type; //积木类型

    void down(); //积木下落
    void left(); //积木左移
    void right(); //积木右移
    void forth(); //积木前移
    void back(); //积木后移
    void drop(); //积木加速下落
    void rotate_x(); //积木以x轴为中心旋转
    void rotate_y(); //积木以y轴为中心旋转
    void rotate_z(); //积木以z轴为中心旋转
    void occupy(); //令积木占有当前所在位置
    void clear(); //令积木取消占有当前所在位置
    bool isBottom(); //判断积木是否到达最底部
    bool isTop(); //判断积木是否到达最顶部
    bool isLeft(); //判断积木是否到达最左侧
    bool isRight(); //判断积木是否到达最右侧
    bool isFront(); //判断积木是否到达最前端
    bool isBack(); //判断积木是否到达最后端
    int toBottom(); //积木到最底部的距离
};

//以下分别为7种形状的衍生方块
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
