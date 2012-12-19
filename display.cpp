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
L_Block current_block;

//View Parameters
int last_time;

void init()
{
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void drawBlock(Block block){
    list<Point>::iterator p;
    for (p = block.points.begin();p != block.points.end();p++)
    {
        double x = (*p).x * BLOCK_SIZE, y = (*p).y * BLOCK_SIZE, z = (*p).z * BLOCK_SIZE;
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
        glTranslatef(START_X * BLOCK_SIZE,START_Y * BLOCK_SIZE,0.0f);
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
            while (current_block.isLeft())
                current_block.right();
            while (current_block.isRight())
                current_block.left();
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
