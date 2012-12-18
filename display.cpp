#ifdef _WIN32
#include "Headers\cal_point.h"
#define GLUT_DISABLE_ATEXIT_HACK
#define DELAY 12
#endif

#ifdef __linux
#include "Headers/cal_point.h"
#define DELAY 1
#endif

#ifdef MACRO
#include "Headers/cal_point.h"
#define DELAY 12
#endif

//Test
S_Block testS;
Z_Block testZ;
L_Block testL;
J_Block testJ;
I_Block testI;
O_Block testO;
T_Block testT;

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
    glColor3f(1.0f,1.0f,1.0f);

    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,UP_BORDER,0.0f);
        glVertex3f(LEFT_BORDER,DOWN_BORDER,0.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(RIGHT_BORDER,UP_BORDER,0.0f);
        glVertex3f(RIGHT_BORDER,DOWN_BORDER,0.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,DOWN_BORDER,0.0f);
        glVertex3f(RIGHT_BORDER,DOWN_BORDER,0.0f);
    glEnd();
}

void drawTetris()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    drawContainer();
	drawBlock(testT);

    glFlush();
    glutSwapBuffers();
}

void refreshTetris(int c)
{
    if (last_time >= 50)
    {
        testT.down();
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
            testT.left();
            break;
        case GLUT_KEY_RIGHT:
            testT.right();
            break;
        case GLUT_KEY_DOWN:
            testT.drop();
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
