#ifdef _WIN32
#include "..\Headers\cal_point.h"
#endif

#ifdef __linux
#include "../Headers/cal_point.h"
#endif

#ifdef MACRO
#include "../Headers/cal_point.h"
#endif

void Block::down(){
    for (int i = 0;i < BLOCK_NUM;i++)
        (this->points[i]).y -= BLOCK_SIZE;
    return;
}
