#include <QApplication>
#include "glwidget.h"
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w0;
    w0.show();
    MainWindow w1;
    w1.show();
    GLWidget w2;
    w2.show();

    return a.exec();
}
