#include <QApplication>
#include "glwidget.h"
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
//    fmt.setRenderableType(QSurfaceFormat::OpenGL);
//    fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
//    fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    fmt.setSwapInterval(0);
//    fmt.setVersion(2, 1);
//    fmt.setOptions(QSurfaceFormat::DeprecatedFunctions);
//    fmt.setSamples(8);
//    fmt.setRedBufferSize(8);
//    fmt.setGreenBufferSize(8);
//    fmt.setBlueBufferSize(8);
//    fmt.setAlphaBufferSize(8);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w0;
    w0.show();
    MainWindow w1;
    w1.show();
    GLWidget w2;
    w2.show();

    return a.exec();
}
