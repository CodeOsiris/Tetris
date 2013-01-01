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
Point block_map[ROW + 2][COLUMN + 2];
int row_fill[ROW + 2];

//View Parameters
clock_t previous,current;
int clock_switch = 1;
int speed = 90000;
int dropspeed = 100;

QTWidget::QTWidget(QWidget* parent,const char* name,bool fs) : QGLWidget(parent,name)
{
    fullscreen = fs;
    setGeometry(0,0,600,600);
    setCaption("Tetris by CodeFarmer");
    if (fullscreen)
        showFullScreen();
}

QTWidget::~QTWidget(){}

void QTWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    for (int i = 0;i <= ROW + 1;i++)
    {
        for (int j = 0;j <= COLUMN + 1;j++)
        {
            if (i == 0 || i == ROW + 1 || j == 0 || j == COLUMN + 1)
                block_map[i][j] = Point(0,i,j,0,true);
            else block_map[i][j] = Point(0,i,j,0,false);
        }
        row_fill[i] = 0;
    }
    previous = clock();
    srand(time(0));
    getNextBlock();
    current_block = next_block;
    getNextBlock();
}

void QTWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

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
        glTranslatef(BLOCK_SIZE - 1.0f,BLOCK_SIZE - 1.0f,0.0f);
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
        glTranslatef(BLOCK_SIZE + 0.1f,BLOCK_SIZE - 1.05f,0.0f);
        drawBlock(next_block);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void QTWidget::resizeGL(int width,int height)
{
    if (height == 0)
        height = 1;
    glViewport(0,0,(GLint)width,(GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(GLfloat)width / (GLfloat)height,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QTWidget::keyPressEvent(QKeyEvent* e)
{
    switch (e->key())
    {
        case Qt::Key_Left:
            if (!current_block.isLeft())
                current_block.left();
            break;
        case Qt::Key_Right:
            if (!current_block.isRight())
                current_block.right();
            break;
        case Qt::Key_Up:
            if (!current_block.isBottom())
                current_block.rotate();
            break;
        case Qt::Key_Down:
            clock_switch = 10;
            break;
        case Qt::Key_Space:
            if (!current_block.isBottom())
                current_block.drop();
            break;
        case Qt::Key_F2:
            fullscreen = !fullscreen;
            if (fullscreen)
                showFullScreen();
            else
            {
                showNormal();
                setGeometry(0,0,600,600);
            }
        case Qt::Key_Escape:
            close();
    }
}

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

void drawBlock(Block block){
    list<Point>::iterator p;
    for (p = block.points.begin();p != block.points.end();p++)
    {
        double x = p->column * BLOCK_SIZE, y = p->row * BLOCK_SIZE, z = p->depth * BLOCK_SIZE;
        glColor3f(block.color[0],block.color[1],block.color[2]);
        glBegin(GL_QUADS);
            glVertex3f(x + BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z + 0.0f);
            glVertex3f(x - BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z + 0.0f);
            glVertex3f(x - BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z + 0.0f);
            glVertex3f(x + BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z + 0.0f);
        glEnd();

        glColor3f(0.4f,0.4f,0.4f);
        glBegin(GL_LINE_LOOP);
            glVertex3f(x + BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z - 0.2f);
            glVertex3f(x - BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z - 0.2f);
            glVertex3f(x - BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z - 0.2f);
            glVertex3f(x + BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z - 0.2f);
        glEnd();
    }
	return;
}

void drawPoint()
{
    for (int i = 1;i <= ROW;i++)
    {
        for (int j = 1;j <= COLUMN;j++)
        {
            double x = j * BLOCK_SIZE, y = i * BLOCK_SIZE, z = 0 * BLOCK_SIZE;
            if (block_map[i][j].isOccupy)
            {
                glColor3f(block_map[i][j].color[0],block_map[i][j].color[1],block_map[i][j].color[2]);
                glBegin(GL_QUADS);
                    glVertex3f(x + BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z + 0.0f);
                    glVertex3f(x - BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z + 0.0f);
                    glVertex3f(x - BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z + 0.0f);
                    glVertex3f(x + BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z + 0.0f);
                glEnd();

                glColor3f(0.4f,0.4f,0.4f);
                glBegin(GL_LINE_LOOP);
                    glVertex3f(x + BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z - 0.2f);
                    glVertex3f(x - BLOCK_SIZE / 2, y + BLOCK_SIZE / 2, z - 0.2f);
                    glVertex3f(x - BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z - 0.2f);
                    glVertex3f(x + BLOCK_SIZE / 2, y - BLOCK_SIZE / 2, z - 0.2f);
                glEnd();
            }
        }
    }
}

void drawContainer()
{
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,TOP_BORDER,-1.0f);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,-1.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(RIGHT_BORDER,TOP_BORDER,-1.0f);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,-1.0f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(LEFT_BORDER,BOTTOM_BORDER,-1.0f);
        glVertex3f(RIGHT_BORDER,BOTTOM_BORDER,-1.0f);
    glEnd();

    glColor3f(0.1f,0.1f,0.1f);
    for (int i = 1;i <= ROW;i++)
    {
        glBegin(GL_LINES);
            glVertex3f(LEFT_BORDER,BOTTOM_BORDER + i * BLOCK_SIZE,0.1f);
            glVertex3f(RIGHT_BORDER,BOTTOM_BORDER + i * BLOCK_SIZE,0.1f);
        glEnd();
    }
    for (int i = 1;i <= COLUMN;i++)
    {
        glBegin(GL_LINES);
            glVertex3f(LEFT_BORDER + i * BLOCK_SIZE,TOP_BORDER,0.1f);
            glVertex3f(LEFT_BORDER + i * BLOCK_SIZE,BOTTOM_BORDER,0.1f);
        glEnd();
    }
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

void keyboardControl(unsigned char key,int x,int y)
{
    switch (key)
    {
		case 27:
			exit(0);
        case 32:
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
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardControl);
    glutDisplayFunc(drawTetris);
    refreshTetris(0);
    glutMainLoop();
    return 0;
}
