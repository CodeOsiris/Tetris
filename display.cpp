#ifdef _WIN32
#include "Headers\cal_point.h"
#define GLUT_DISABLE_ATEXIT_HACK
#define DELAY 12000
#endif

#ifdef __linux
#include "Headers/cal_point.h"
#define DELAY 1000
#endif

#ifdef MACRO
#include "Headers/cal_point.h"
#define DELAY 12000
#endif

//Test
S_Block testS;
Z_Block testZ;
L_Block testL;
J_Block testJ;
I_Block testI;
O_Block testO;
T_Block testT;

//View settings
const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 3000;
const int LEFT_BORDER = 100;
const int RIGHT_BORDER = 2400;

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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(59.5,(GLdouble)WINDOW_WIDTH / (GLdouble)WINDOW_HEIGHT,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,4,0,0,0,0,1,0);

    for (int i = 0;i < BLOCK_NUM;i++)
    {
        Point p = block.points[i];
        double x = p.x, y = p.y, z = p.z;
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
}

void drawTetris()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	drawBlock(testT);

    glFlush();
    glutSwapBuffers();
}

void refreshTetris(int c)
{
    testT.down();

    glutPostRedisplay();
    glutTimerFunc(DELAY,refreshTetris,0);
}

void keyboardControl(unsigned char key,int x,int y)
{
    switch(key)
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
    glutInitWindowSize(WINDOW_WIDTH * BLOCK_SIZE,WINDOW_HEIGHT * BLOCK_SIZE);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Tetris");
    init();
    glutDisplayFunc(drawTetris);
    glutKeyboardFunc(keyboardControl);
    refreshTetris(0);
    glutMainLoop();
    return 0;
}
