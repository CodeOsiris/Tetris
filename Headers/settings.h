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
#include <GL\glut.h>
#endif

#ifdef __linux
#include <GL/glut.h>
#endif

#ifdef MACRO
#include <GL/glut.h>
#endif
using namespace std;

//基本设定
const float BLOCK_SIZE = 0.12f; //方块大小
const int BLOCK_NUM = 4; //每个积木包含的方块数
const float BOTTOM_BORDER = -13 * BLOCK_SIZE / 2; //容器底部边界
const float TOP_BORDER = 13 * BLOCK_SIZE / 2; //容器顶部边界
const float LEFT_BORDER = -13 * BLOCK_SIZE / 2; //容器左侧边界
const float RIGHT_BORDER = 1 * BLOCK_SIZE / 2; //容器右侧边界
const float FRONT_BORDER = 1 * BLOCK_SIZE / 2; //容器前侧边界
const float BACK_BORDER = -13 * BLOCK_SIZE / 2; //容器后侧边界

const int START_ROW = (int)((TOP_BORDER - BOTTOM_BORDER) / BLOCK_SIZE); //积木生成的起始行
const int START_COLUMN = (int)((RIGHT_BORDER - LEFT_BORDER) / BLOCK_SIZE / 2 + 1); //积木生成的起始列
const int START_DEPTH = (int)((FRONT_BORDER - BACK_BORDER) / BLOCK_SIZE / 2 + 1); //积木生成的起始层

const int ROW = (int)((TOP_BORDER - BOTTOM_BORDER) / BLOCK_SIZE); //总行数（沿y轴）
const int COLUMN = (int)((RIGHT_BORDER - LEFT_BORDER) / BLOCK_SIZE); //总列数（沿x轴）
const int DEPTH = (int)((FRONT_BORDER - BACK_BORDER) / BLOCK_SIZE); //总层数（沿z轴）

const float CENTER_X = (LEFT_BORDER + RIGHT_BORDER) / 2; //容器底部中心x坐标
const float CENTER_Y = (BOTTOM_BORDER + TOP_BORDER) / 2; //容器底部中心y坐标
const float CENTER_Z = (FRONT_BORDER + BACK_BORDER) / 2; //容器底部中心z坐标

extern int level_fill[ROW + 2]; //记录每行被填满的数量
extern int speed; //积木下落速度
extern int dropspeed; //积木加速下落速度
extern bool hasGravity; //是否进入重力模式
#endif
