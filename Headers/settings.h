#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <list>
#include <vector>
#include <iterator>
#include <string>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#include <glut.h>
#endif

#ifdef __linux
#include <GL/glut.h>
#endif

#ifdef MACRO
#include <GL/glut.h>
#endif
using namespace std;

//基本设定
#define BLOCK_SIZE 0.12f //方块大小
#define BLOCK_NUM 4 //每个积木包含的方块数
#define BOTTOM_BORDER -13 * BLOCK_SIZE / 2//容器底部边界
#define TOP_BORDER 13 * BLOCK_SIZE / 2//容器顶部边界
#define LEFT_BORDER -13 * BLOCK_SIZE / 2//容器左侧边界
#define RIGHT_BORDER 1 * BLOCK_SIZE / 2//容器右侧边界
#define FRONT_BORDER 1 * BLOCK_SIZE / 2//容器前侧边界
#define BACK_BORDER -13 * BLOCK_SIZE / 2//容器后侧边界

#define START_ROW (int)((TOP_BORDER - BOTTOM_BORDER) / BLOCK_SIZE)//积木生成的起始行
#define START_COLUMN  (int)((RIGHT_BORDER - LEFT_BORDER) / BLOCK_SIZE / 2 + 1)//积木生成的起始列
#define START_DEPTH (int)((FRONT_BORDER - BACK_BORDER) / BLOCK_SIZE / 2 + 1)//积木生成的起始层

#define ROW (int)((TOP_BORDER - BOTTOM_BORDER) / BLOCK_SIZE)//总行数（沿y轴）
#define COLUMN (int)((RIGHT_BORDER - LEFT_BORDER) / BLOCK_SIZE)//总列数（沿x轴）
#define DEPTH (int)((FRONT_BORDER - BACK_BORDER) / BLOCK_SIZE) //总层数（沿z轴）

#define CENTER_X (LEFT_BORDER + RIGHT_BORDER) / 2//容器底部中心x坐标
#define CENTER_Y (BOTTOM_BORDER + TOP_BORDER) / 2//容器底部中心y坐标
#define CENTER_Z (FRONT_BORDER + BACK_BORDER) / 2 //容器底部中心z坐标

extern int level_fill[ROW + 2]; //记录每行被填满的数量
extern int speed; //积木下落速度
extern int dropspeed; //积木加速下落速度
extern bool hasGravity; //是否进入重力模式
#endif
