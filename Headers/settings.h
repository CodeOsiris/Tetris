#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

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

//Basic Settings
const float BLOCK_SIZE = 0.05f;
const int BLOCK_NUM = 4;
const float BOTTOM_BORDER = -1.0f + BLOCK_SIZE / 2;
const float TOP_BORDER = 1.0f - BLOCK_SIZE / 2;
const float LEFT_BORDER = -1.0f + BLOCK_SIZE / 2;
const float RIGHT_BORDER = 0.5f - BLOCK_SIZE / 2;
#endif
