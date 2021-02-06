#include "LDrawSpectrum.h"
#include <QApplication>
#include <QObject>
//#include <GL/glut.h>
////#include <GL/freeglut.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LDrawSpectrum w;
    w.show();

    return a.exec();
}
