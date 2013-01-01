#ifdef _WIN32
#include <windows.h>
#include <GL\glut.h>
#endif

#ifdef __linux
#include <GL/glut.h>
#include <Qt/qgl.h>
#endif

#ifdef MACRO
#include <GL/glut.h>
#endif

class QTWidget : public QGLWidget
{
    Q_OBJECT
public:
    QTWidget(QWidget* parent = 0,const char* name = 0,bool fs = false);
    ~QTWidget();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width,int height);
    void keyPressEvent(QKeyEvent *e);
    bool fullscreen;
};

void getNextBlock();
void drawBlock();
void drawPoint();
void drawContainer();
