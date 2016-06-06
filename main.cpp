#include <QApplication>
#include "LogoGLWidget.h"
#include "MainWindow.h"

static QSharedPointer<MainWindow> w0, w1;
static QSharedPointer<LogoGLWidget> w2;
static QSharedPointer<QAction> qsurfaceformat_default_swap_interval;
static QSharedPointer<QAction> w2_default_swap_interval;

static void set_w2_qsurfaceformat(bool swap_interval_0)
{
    w2.reset(new LogoGLWidget(swap_interval_0 ? 0 : 1));
    w2->show();
}

static void set_qsurfaceformat_default(bool swap_interval_0)
{
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setRenderableType(QSurfaceFormat::OpenGL);
    fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    fmt.setSwapInterval(swap_interval_0 ? 0 : 1);
    fmt.setVersion(2, 1);
    fmt.setOptions(QSurfaceFormat::DeprecatedFunctions);
    fmt.setSamples(8);
    fmt.setRedBufferSize(8);
    fmt.setGreenBufferSize(8);
    fmt.setBlueBufferSize(8);
    fmt.setAlphaBufferSize(8);
    QSurfaceFormat::setDefaultFormat(fmt);

    w0.reset(new MainWindow());
    w0->toolbar()->insertAction(w0->toolbar()->actions()[0], qsurfaceformat_default_swap_interval.data());
    w0->toolbar()->addAction(w2_default_swap_interval.data());
    w0->show();

    w1.reset(new MainWindow());
    w1->toolbar()->insertAction(w1->toolbar()->actions()[0], qsurfaceformat_default_swap_interval.data());
    w1->toolbar()->addAction(w2_default_swap_interval.data());
    w1->show();

    set_w2_qsurfaceformat(w2_default_swap_interval->isChecked());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsurfaceformat_default_swap_interval.reset(new QAction("global swapInterval == 0"));
    qsurfaceformat_default_swap_interval->setToolTip(
        "When set, QSurfaceFormat::defaultFormat().swapInterval() == 0\n"
        "When unset, QSurfaceFormat::defaultFormat().swapInterval() == 1");
    qsurfaceformat_default_swap_interval->setCheckable(true);
    qsurfaceformat_default_swap_interval->setChecked(true);
    QObject::connect(qsurfaceformat_default_swap_interval.data(), &QAction::toggled, &set_qsurfaceformat_default);

    w2_default_swap_interval.reset(new QAction("logo window swapInterval == 0"));
    w2_default_swap_interval->setToolTip(
        "When set, logo.format().swapInterval() == 0\n"
        "When unset, logo.format().swapInterval() == 1");
    w2_default_swap_interval->setCheckable(true);
    w2_default_swap_interval->setChecked(true);
    QObject::connect(w2_default_swap_interval.data(), &QAction::toggled, &set_w2_qsurfaceformat);

    set_qsurfaceformat_default(true);

    int ret = a.exec();
    w0.clear();
    w1.clear();
    w2.clear();
    return ret;
}
