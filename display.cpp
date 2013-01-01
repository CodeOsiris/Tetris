#ifdef _WIN32
#include "Headers\components.h"
#define GLUT_DISABLE_ATEXIT_HACK
#define DELAY 12
#endif

#ifdef __linux
#include "Headers/components.h"
#define DELAY 1
#endif

#ifdef MACRO
#include "Headers/components.h"
#define DELAY 12
#endif

//Components
Block current_block,next_block;
Point block_map[ROW + 2][COLUMN + 2][DEPTH + 2];
int level_fill[ROW + 2];

//View Parameters
clock_t previous,current;
int clock_switch = 1;
int speed = 90000;
int dropspeed = 100;
int scr_w = 600;
int scr_h = 600;

void getNextBlock()
{
    int block_type = rand() % 7;
    switch (block_type)
    {
        case 0:
            next_block = S_Block(START_ROW,START_COLUMN);
            break;
        case 1:
            next_block = Z_Block(START_ROW,START_COLUMN);
            break;
        case 2:
            next_block = L_Block(START_ROW,START_COLUMN);
            break;
        case 3:
            next_block = J_Block(START_ROW,START_COLUMN);
            break;
        case 4:
            next_block = I_Block(START_ROW,START_COLUMN);
            break;
        case 5:
            next_block = O_Block(START_ROW,START_COLUMN);
            break;
        case 6:
            next_block = T_Block(START_ROW,START_COLUMN);
            break;
    }
}

void init()
{
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
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

void drawBlock(Block block){
    list<Point>::iterator p;
    for (p = block.points.begin();p != block.points.end();p++)
    {
        double x = p->column * BLOCK_SIZE, y = p->row * BLOCK_SIZE, z = p->depth * BLOCK_SIZE;
        glColor3f(block.color[0],block.color[1],block.color[2]);
        glPushMatrix();
            glTranslatef(x,y,z);
            glutWireCube(BLOCK_SIZE);
        glPopMatrix();
    }
	return;
}

void drawPoint()
{
    for (int i = 1;i <= ROW;i++)
    {
        for (int j = 1;j <= COLUMN;j++)
        {
            for (int k = 1;k < DEPTH;k++)
            {
                double x = j * BLOCK_SIZE, y = i * BLOCK_SIZE, z = k * BLOCK_SIZE;
                if (block_map[i][j][k].isOccupy)
                {
                    glColor3f(block_map[i][j][k].color[0],block_map[i][j][k].color[1],block_map[i][j][k].color[2]);
                    glPushMatrix();
                        glTranslatef(x,y,z);
                        glutWireCube(BLOCK_SIZE);
                    glPopMatrix();
                }
            }
        }
    }
}

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

/*    glColor3f(0.1f,0.1f,0.1f);
    for (int i = 1;i <= ROW;i++)
    {
        glBegin(GL_LINES);
            glVertex3f(LEFT_BORDER,BOTTOM_BORDER + i * BLOCK_SIZE,0.0f);
            glVertex3f(RIGHT_BORDER,BOTTOM_BORDER + i * BLOCK_SIZE,0.0f);
        glEnd();
    }
    for (int i = 1;i <= COLUMN;i++)
    {
        glBegin(GL_LINES);
            glVertex3f(LEFT_BORDER + i * BLOCK_SIZE,TOP_BORDER,0.0f);
            glVertex3f(LEFT_BORDER + i * BLOCK_SIZE,BOTTOM_BORDER,0.0f);
        glEnd();
    }
    */
}

void drawTetris()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)scr_w / (GLfloat)scr_h,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-0.3f,1.0f,3.0f,-0.3f,0.0f,0.0f,0.0f,1.0f,0.0f);

    /*for (int i = ROW;i >= 1;i--)
    {
        for (int j = 1;j <= COLUMN;j++)
        {
            printf("%2d ",block_map[i][j].parent);
        }
        printf("\n");
    }*/
    drawContainer();
    glPushMatrix();
        glTranslatef(BLOCK_SIZE - 1.0f,BLOCK_SIZE - 1.0f,-1.0f);
        drawPoint();
        if (!current_block.isBottom())
            drawBlock(current_block);
        else
        {
            current_block.occupy();
            current_block.isStop = true;
            current_block = next_block;
            getNextBlock();
            while (judge_row());
        }
    glPopMatrix();

    glPushMatrix();
        glTranslatef(BLOCK_SIZE + 0.0f,BLOCK_SIZE - 1.05f,0.0f);
        drawBlock(next_block);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w,int h)
{
    scr_w = w;
    scr_h = h;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
}

void refreshTetris(int c)
{
    current = clock();
    if (current - previous >= (speed * (clock_switch % 10) + dropspeed * (clock_switch / 10) / 1000))
    {
        if (!current_block.isBottom())
            current_block.down();
        previous = clock();
        clock_switch = 1;
    }

    glutPostRedisplay();
    glutTimerFunc(DELAY,refreshTetris,0);
}

void keyboardSpecial(int key,int x,int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            if (!current_block.isLeft())
                current_block.left();
            break;
        case GLUT_KEY_RIGHT:
            if (!current_block.isRight())
                current_block.right();
            break;
        case GLUT_KEY_UP:
            if (!current_block.isBack())
                current_block.back();
            //if (!current_block.isBottom())
            //    current_block.rotate();
            break;
        case GLUT_KEY_DOWN:
            if (!current_block.isFront())
                current_block.forth();
            //clock_switch = 10;
            break;
    }
}

void keyboardControl(unsigned char key,int x,int y)
{
    switch (key)
    {
		case 27:
			exit(0);
        case 32:
            if (!current_block.isBottom())
                current_block.drop();
            break;
        default:
            break;
    }
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(scr_w,scr_h);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Tetris");
    init();
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardControl);
    glutDisplayFunc(drawTetris);
    refreshTetris(0);
    glutMainLoop();
    return 0;
}
