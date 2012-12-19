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
L_Block current_block(START_ROW,START_COLUMN);
int block_map[ROW][COLUMN];

//View Parameters
int last_time;

void init()
{
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    for (int i = 0;i < ROW;i++)
        for (int j = 0;j < COLUMN;j++)
        {
            if (i == 0 || i == ROW || j == 0 || j == COLUMN)
                block_map[i][j] = 1;
            else block_map[i][j] = 0;
        }
}

void drawBlock(Block block){
    list<Point>::iterator p;
    for (p = block.points.begin();p != block.points.end();p++)
    {
        double x = (*p).column * BLOCK_SIZE, y = (*p).row * BLOCK_SIZE, z = (*p).depth * BLOCK_SIZE;
        glColor3f(1.0f,1.0f,1.0f);

        glBegin(GL_QUADS);
            glVertex3f(x + BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z + 0.0f);
            glVertex3f(x - BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z + 0.0f);
            glVertex3f(x - BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z + 0.0f);
            glVertex3f(x + BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z + 0.0f);
        glEnd();
    }
	return;
}

void drawContainer()
{
    glColor3f(1.0f,1.0f,1.0f);

    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,TOP_BORDER,0.0f);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,0.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(RIGHT_BORDER,TOP_BORDER,0.0f);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,0.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,0.0f);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,0.0f);
    glEnd();
}

void drawTetris()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    drawContainer();
    glPushMatrix();
        glTranslatef(BLOCK_SIZE - 1.0f,BLOCK_SIZE - 1.0f,0.0f);
        drawBlock(current_block);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void refreshTetris(int c)
{
    if (last_time >= 50)
    {
        if (!current_block.isBottom())
            current_block.down();
        last_time = 0;
    }
    else last_time++;

    glutPostRedisplay();
    glutTimerFunc(DELAY,refreshTetris,0);
}

void keyboardSpecial(int key,int x,int y)
{
    glutSetKeyRepeat(0);
    switch (key)
    {
        case GLUT_KEY_LEFT:
            if (!current_block.isLeft() && !current_block.isBottom())
                current_block.left();
            break;
        case GLUT_KEY_RIGHT:
            if (!current_block.isRight() && !current_block.isBottom())
                current_block.right();
            break;
        case GLUT_KEY_UP:
            if (!current_block.isBottom())
                current_block.rotate();
            break;
        case GLUT_KEY_DOWN:
            if (!current_block.isBottom())
                current_block.drop();
            break;
    }
}

void keyboardControl(unsigned char key,int x,int y)
{
    switch (key)
    {
		case 27:
			exit(0);
        default:
            break;
    }
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Tetris");
    init();
    glutDisplayFunc(drawTetris);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardControl);
    refreshTetris(0);
    glutMainLoop();
    return 0;
}
