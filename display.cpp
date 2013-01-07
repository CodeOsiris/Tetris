#ifdef _WIN32
#include "Headers\components.h"
#define GLUT_DISABLE_ATEXIT_HACK
#define DELAY 12
#define RATE 1
#endif

#ifdef __linux
#include "Headers/components.h"
#define DELAY 1
#define RATE 100
#endif

#ifdef MACRO
#include "Headers/components.h"
#define DELAY 12
#define RATE 1
#endif

//Components
Block current_block,next_block; // 表示当前正在下落的方块以及预告下一个方块
Point block_map[ROW + 2][COLUMN + 2][DEPTH + 2]; // 记录整个游戏区域各点的状态以便于绘图
int level_fill[ROW + 2]; // 记录每一层的小方块个数，以便在铺满一层时进行消除

//View Parameters
clock_t previous,current; // 用于在经过一段时间后就让方块下落一层
long total_erase = 0; // 记录总共消除了多少层
long score = 0; // 记录当前的游戏分数
long level = 1; // 设置游戏等级，等级越高方块下落速度越快
int clock_switch = 1; // 配合下面两个速度来调整下落速度
int speed = 5000 * RATE; // 普通下落速度
int dropspeed = 1 * RATE; // 急速下落速度
bool hasGravity = false; // 用于切换不同的游戏模式
double fix_angle = 0.71; // 用于修复切换视角之后的屏幕抖动
bool isStart = true; // 用于控制游戏暂停与继续
bool isNext = false; // 用于判断下一个方块是否可以出现并下落
bool isLose = false; // 用于判断游戏是否结束
int scr_w = 1000; // 游戏窗口的宽度
int scr_h = 600; // 游戏窗口的高度
int status = 0; // 用于控制目前是从哪个方向观察游戏区域的，共四个方向
double anglex = 0.0; // 用于左右旋转视角
double angley = 0.0; // 用于上下旋转视角
// glutLookAt函数所需的参数
float eyex = 2.0 * sin(anglex) + CENTER_X, eyey = 0.6, eyez = 2.0 * cos(anglex) + CENTER_Z, centerx = CENTER_X, centery = CENTER_Y, centerz = CENTER_Z, upx = 0.0, upy = 1.0, upz = 0.0;
const double pi = acos(-1); // 圆周率常量，用于旋转视角
const long level_score[11] = {0,20,50,90,140,200,270,350,460,560,670}; // 每个等级游戏下消除一层方块所获得的分数

// 随机产生一个数来决定下一个方块的形状
void getNextBlock()
{
    int block_type = rand() % 7;
    switch (block_type)
    {
        case 0:
            next_block = S_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
        case 1:
            next_block = L_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
        case 2:
            next_block = I_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
        case 3:
            next_block = O_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
        case 4:
            next_block = T_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
        case 5:
            next_block = Y_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
        case 6:
            next_block = N_Block(START_ROW,START_COLUMN,START_DEPTH);
            break;
    }
}

// 初始化游戏参数
void init()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    isStart = true;
    isNext = false;
    isLose = false;
    status = 0;
    anglex = 0.0;
    eyex = 2.0 * sin(anglex) + CENTER_X;
    eyey = 0.6;
    eyez = 2.0 * cos(anglex) + CENTER_Z;
    speed = 5000 * RATE;
    hasGravity = false;
    total_erase = 0;
    score = 0;
    level = 1;
    for (int i = 0;i <= ROW + 1;i++)
    {
        for (int j = 0;j <= COLUMN + 1;j++)
        {
            for (int k = 0;k <= DEPTH + 1;k++)
            {
                if (i == 0 || i == ROW + 1 || j == 0 || j == COLUMN + 1 || k == 0 || k == DEPTH + 1)
                    block_map[i][j][k] = Point(0,i,j,k,true);
                else block_map[i][j][k] = Point(0,i,j,k,false);
            }
        }
        level_fill[i] = 0;
    }
    previous = clock();
    srand(time(0));
    getNextBlock();
    current_block = next_block;
    getNextBlock();
}

// 将分数值转化为字符串以便于输出到屏幕上
string valToStr(long val)
{
    string str;
    do
    {
        str += (val % 10) + '0';
        val /= 10;
    }
    while (val);
    string rstr;
    for (int i = str.length() - 1;i >= 0;i--)
        rstr += str[i];
    return rstr;
}

// 在屏幕上画出一个方块
void drawBlock(Block block){
    list<Point>::iterator p;
    for (p = block.points.begin();p != block.points.end();p++)
    {
        double x = p->column * BLOCK_SIZE, y = p->row * BLOCK_SIZE, z = p->depth * BLOCK_SIZE;
        glPushMatrix();
            glTranslatef(x,y,z);
            glColor4f(0.0f,0.0f,1.0f,0.6f);
            glutSolidCube(BLOCK_SIZE);
        glPopMatrix();
    }
    return;
}

// 在屏幕左边显示提示信息
void drawHint()
{
    float base_x,base_y,base_z,hint_x,hint_y,hint_z,fix_x,fix_y,fix_z,stat_x,stat_y,stat_z,fixs_x,fixs_y,fixs_z;
    glPushMatrix();
        switch (status)
        {
            case 0:
                base_x = 3 * BLOCK_SIZE;
                base_y = -1.0f;
                base_z = -7 * BLOCK_SIZE;
                hint_x = -14 * BLOCK_SIZE;
                hint_y = 0.9f;
                hint_z = 0.0f;
                fix_x = -0.04f;
                fix_y = -0.15f;
                fix_z = 0.0f;
                stat_x = 1.0f;
                stat_y = 0.0f;
                stat_z = 0.0f;
                fixs_x = 0.02f;
                fixs_y = -0.15f;
                fixs_z = 0.0f;
                break;
            case 1:
                base_x = -7 * BLOCK_SIZE;
                base_y = -1.0f;
                base_z = 3 * BLOCK_SIZE;
                hint_x = 0.0f;
                hint_y = 0.9f;
                hint_z = -14 * BLOCK_SIZE;
                fix_x = 0.0f;
                fix_y = -0.15f;
                fix_z = -0.04f;
                stat_x = 0.0f;
                stat_y = 0.0f;
                stat_z = 1.0f;
                fixs_x = 0.0f;
                fixs_y = -0.15f;
                fixs_z = 0.02f;
                break;
            case 2:
                base_x = -17 * BLOCK_SIZE;
                base_y = -1.0f;
                base_z = -7 * BLOCK_SIZE;
                hint_x = 14 * BLOCK_SIZE;
                hint_y = 0.9f;
                hint_z = 0.0f;
                fix_x = 0.04f;
                fix_y = -0.15f;
                fix_z = 0.0f;
                stat_x = -1.0f;
                stat_y = 0.0f;
                stat_z = 0.0f;
                fixs_x = -0.02f;
                fixs_y = -0.15f;
                fixs_z = 0.0f;
                break;
            case 3:
                base_x = -7 * BLOCK_SIZE;
                base_y = -1.0f;
                base_z = -17 * BLOCK_SIZE;
                hint_x = 0.0f;
                hint_y = 0.9f;
                hint_z = 14 * BLOCK_SIZE;
                fix_x = 0.0f;
                fix_y = -0.15f;
                fix_z = 0.04f;
                stat_x = 0.0f;
                stat_y = 0.0f;
                stat_z = -1.0f;
                fixs_x = 0.0f;
                fixs_y = -0.15f;
                fixs_z = -0.02f;
                break;
        }
        glTranslatef(base_x,base_y,base_z);
        drawBlock(next_block);
    glPopMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    string total_str = "Erase: " + valToStr(total_erase);
    string score_str = "Score: " + valToStr(score);
    string level_str = "Level: " + valToStr(level);
    glRasterPos3f(centerx + stat_x,centery + stat_y,centerz + stat_z);
    for (int i = 0;i < level_str.length();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,level_str[i]);
    glRasterPos3f(centerx + stat_x + fixs_x,centery + stat_y + fixs_y,centerz + stat_z + fixs_z);
    for (int i = 0;i < score_str.length();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,score_str[i]);
    glRasterPos3f(centerx + stat_x + fixs_x * 2,centery + stat_y + fixs_y * 2,centerz + stat_z + fixs_z * 2);
    for (int i = 0;i < total_str.length();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,total_str[i]);
    string help[15] = {
        "F1: Toggle gravity",
        "Enter: Restart",
        "Arrow Keys: Move blocks",
        "Q: Rotate blocks on axis-x",
        "W: Rotate blocks on axis-y",
        "E: Rotate blocks on axis-z",
        "S: Speed blocks",
        "Space: Drop blocks",
        "A: Rotate horizontally(clockwise)",
        "D: Rotate horizontally(counterclockwise)",
        "F: Rotate vertically(clockwise)",
        "R: Rotate vertically(counterclockwise)",
        "P: Pause",
        "-: Level down",
        "+: Level up"
    };
    for (int i = 0;i < 15;i++)
    {
        glRasterPos3f(centerx + hint_x + fix_x * i,centery + hint_y + fix_y * i,centerz + hint_z + fix_z * i);
        for (int j = 0;j < help[i].length();j++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,help[i][j]);
    }
    if (!isStart)
    {
        glColor3f(1.0f,0.0f,0.0f);
        string pause = "Paused";
        glRasterPos3f(centerx,centery,centerz);
        for (int i = 0;i < pause.length();i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,pause[i]);
    }
    glColor3f(1.0f,1.0f,1.0f);
    string mode;
    if (hasGravity)
        mode = "Gravity";
    else mode = "Classic";
    glRasterPos3f(centerx,centery + 0.9f,centerz);
    for (int i = 0;i < mode.length();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,mode[i]);
}

// 在屏幕相应位置画出小正方体
void drawPoint()
{
    float color[4][4] = {0.7f,0.0f,0.0f,0.7f,
                         1.0f,0.5f,0.0f,0.7f,
                         1.0f,1.0f,0.0f,0.7f,
                         0.0f,1.0f,0.0f,0.7f};
    for (int i = 1;i <= ROW;i++)
    {
        for (int j = 1;j <= COLUMN;j++)
        {
            for (int k = 1;k <= DEPTH;k++)
            {
                double x = j * BLOCK_SIZE, y = i * BLOCK_SIZE, z = k * BLOCK_SIZE;
                if (block_map[i][j][k].isOccupy)
                {
                    glPushMatrix();
                        glTranslatef(x,y,z);
                        glColor4f(color[i % 4][0],color[i % 4][1],color[i % 4][2],color[i % 4][3]);
                        glutSolidCube(BLOCK_SIZE);
                    glPopMatrix();
                }
            }
        }
    }
    for (list<Point>::iterator p = (current_block.points).begin();p != (current_block.points).end();p++)
    {
        int distance = current_block.toBottom();
        double x = p->column * BLOCK_SIZE, y = (p->row - distance)* BLOCK_SIZE, z = p->depth * BLOCK_SIZE;
        glPushMatrix();
            glTranslatef(x,y,z);
            glColor4f(0.0f,0.0f,1.0f,0.2f);
            glutSolidCube(BLOCK_SIZE);
        glPopMatrix();
    }
}

// 画出游戏区域
void drawContainer()
{
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,TOP_BORDER,FRONT_BORDER);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,FRONT_BORDER);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,TOP_BORDER,BACK_BORDER);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,BACK_BORDER);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(RIGHT_BORDER,TOP_BORDER,FRONT_BORDER);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,FRONT_BORDER);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(RIGHT_BORDER,TOP_BORDER,BACK_BORDER);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,BACK_BORDER);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,FRONT_BORDER);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,FRONT_BORDER);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,BACK_BORDER);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,BACK_BORDER);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(LEFT_BORDER,TOP_BORDER,FRONT_BORDER);
        glVertex3f(RIGHT_BORDER,TOP_BORDER,FRONT_BORDER);
        glVertex3f(RIGHT_BORDER,TOP_BORDER,BACK_BORDER);
        glVertex3f(LEFT_BORDER,TOP_BORDER,BACK_BORDER);
    glEnd();

    glColor3f(0.4f,0.4f,0.4f);
    for (int i = 1;i < COLUMN;i++)
    {
        for (int j = 1;j < DEPTH;j++)
        {
            glBegin(GL_LINES);
                glVertex3f(LEFT_BORDER + i * BLOCK_SIZE,BOTTOM_BORDER,FRONT_BORDER);
                glVertex3f(LEFT_BORDER + i * BLOCK_SIZE,BOTTOM_BORDER,BACK_BORDER);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(LEFT_BORDER,BOTTOM_BORDER,FRONT_BORDER - j * BLOCK_SIZE);
                glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,FRONT_BORDER - j * BLOCK_SIZE);
            glEnd();
        }
    }
}

// 游戏结束时的提示内容
void handle_lose(){
    string str = "You Lose! Press Enter to restart";
    glRasterPos3f(centerx,centery / cos(angley) - 1.5f,centerz);
    for (int i = 0;i < str.length();i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}

// 绘制游戏窗口里的内容，包括提示、游戏区域和方块等等
void drawTetris()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)scr_w / (GLfloat)scr_h,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

    glColor3f(1.0f,1.0f,1.0f);
    if (isLose)
        handle_lose();
    drawHint();

    glPushMatrix();
        switch (status)
        {
            case 0:
                glTranslatef(0.0f,-sin(angley / 180 * pi) * fix_angle,0.0f);
                glRotatef((GLfloat)angley,1.0f,0.0f,0.0f);
                break;
            case 1:
                glRotatef((GLfloat)angley,0.0f,0.0f,1.0f);
                break;
            case 2:
                glRotatef((GLfloat)angley,-1.0f,0.0f,0.0f);
                break;
            case 3:
                glTranslatef(0.0f,-sin(angley / 180 * pi) * fix_angle,0.0f);
                glRotatef((GLfloat)angley,0.0f,0.0f,-1.0f);
                break;
        }
        drawContainer();
        glPushMatrix();
            glTranslatef(-7 * BLOCK_SIZE,-7 * BLOCK_SIZE,-7 * BLOCK_SIZE);
            if (current_block.isBottom())
            {
                if (block_map[START_ROW][START_COLUMN][START_DEPTH].isOccupy)
                {
                    isLose = true;
                }
                else isNext = true;
            }
            int base = 1;
            int tmp = 1;
            while (judge_row())
            {
                total_erase++;
                score += tmp;
                tmp *= ++base;
            }
            if (score >= level_score[level] && level < 10)
                level++;
            drawBlock(current_block);
            drawPoint();
        glPopMatrix();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

// 处理改变窗口大小的事件
void reshape(int w,int h)
{
    scr_w = w;
    scr_h = h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
}

// 控制当前方块下落
void refreshTetris(int c)
{
    speed = (int)((5.5 - level / 2.0) * 1000) * RATE;
    if (isStart)
    {
        current = clock();
        if (current - previous >= (speed * (clock_switch & 1) + dropspeed * (clock_switch & 2) / 1000))
        {
            if (!current_block.isBottom())
            {
                isNext = false;
                current_block.down();
            }
            previous = clock();
            clock_switch = 1;
            if (isNext)
            {
                current_block.occupy();
                current_block.isStop = true;
                current_block = next_block;
                getNextBlock();
                isNext = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(DELAY,refreshTetris,0);
}

// 定义特殊按键对应的操作
void keyboardSpecial(int key,int x,int y)
{
    if (isLose)
        return;
    switch (key)
    {
        case GLUT_KEY_F1:
            hasGravity = !hasGravity;
            break;
        case GLUT_KEY_LEFT:
            switch (status){
                case 0:
                    if (!current_block.isLeft())
                        current_block.left();
                    break;
                case 2:
                    if (!current_block.isRight())
                        current_block.right();
                    break;
                case 1:
                    if (!current_block.isBack())
                        current_block.back();
                    break;
                case 3:
                    if (!current_block.isFront())
                        current_block.forth();
                    break;
            }
            break;
        case GLUT_KEY_RIGHT:
            switch (status){
                case 2:
                    if (!current_block.isLeft())
                        current_block.left();
                    break;
                case 0:
                    if (!current_block.isRight())
                        current_block.right();
                    break;
                case 3:
                    if (!current_block.isBack())
                        current_block.back();
                    break;
                case 1:
                    if (!current_block.isFront())
                        current_block.forth();
                    break;
            }
            break;
        case GLUT_KEY_UP:
            switch (status){
                case 3:
                    if (!current_block.isLeft())
                        current_block.left();
                    break;
                case 1:
                    if (!current_block.isRight())
                        current_block.right();
                    break;
                case 0:
                    if (!current_block.isBack())
                        current_block.back();
                    break;
                case 2:
                    if (!current_block.isFront())
                        current_block.forth();
                    break;
            }
            break;
        case GLUT_KEY_DOWN:
            switch (status){
                case 1:
                    if (!current_block.isLeft())
                        current_block.left();
                    break;
                case 3:
                    if (!current_block.isRight())
                        current_block.right();
                    break;
                case 2:
                    if (!current_block.isBack())
                        current_block.back();
                    break;
                case 0:
                    if (!current_block.isFront())
                        current_block.forth();
                    break;
            }
            break;
    }
}

// 定义普通按键对应的操作
void keyboardControl(unsigned char key,int x,int y)
{
    if (key == 13)
        init();
    else if (key == 27)
        exit(0);
    else if (isLose)
        return;
    switch (key)
    {
        case 61:
            if (level < 10)
                level++;
            break;
        case 45:
            if (level > 1)
                level--;
            break;
        case 32:
            if (!current_block.isBottom())
                current_block.drop();
            current_block.occupy();
            current_block.isStop = true;
            current_block = next_block;
            getNextBlock();
            isNext = false;
            break;
        case 'A':
        case 'a':
            anglex -= pi / 2;
            eyex = 2.0 * sin(anglex) + CENTER_X, eyez = 2.0 * cos(anglex) + CENTER_Z;
            status = (status + 1) % 4;
            break;
        case 'D':
        case 'd':
            anglex += pi / 2;
            eyex = 2.0 * sin(anglex) + CENTER_X, eyez = 2.0 * cos(anglex) + CENTER_Z;
            status = (status + 3) % 4;
            break;
        case 'Q':
        case 'q':
            if (!current_block.isBottom())
            {
                switch (status)
                {
                    case 0:
                    case 2:
                        current_block.rotate_x();
                        break;
                    case 1:
                    case 3:
                        current_block.rotate_z();
                        break;
                }
            }
            break;
        case 'W':
        case 'w':
            if (!current_block.isBottom())
                current_block.rotate_y();
            break;
        case 'E':
        case 'e':
            if (!current_block.isBottom())
            {
                switch (status)
                {
                    case 0:
                    case 2:
                        current_block.rotate_z();
                        break;
                    case 1:
                    case 3:
                        current_block.rotate_x();
                }
            }
            break;
        case 'S':
        case 's':
            clock_switch = 2;
            break;
        case 'R':
        case 'r':
            if (angley < 22.5)
                angley += 2;
            break;
        case 'F':
        case 'f':
            if (angley > -15)
                angley -= 2;
            break;
        case 'P':
        case 'p':
            isStart = !isStart;
            break;
        default:
            break;
    }
}

// 主函数
int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(scr_w,scr_h);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Tetris");
    init();
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardControl);
    glutDisplayFunc(drawTetris);
    refreshTetris(0);
    glutMainLoop();
    return 0;
}
