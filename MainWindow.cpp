#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    m_central_gs(new QGraphicsScene()),
    m_central_fps_item(m_central_gs->addText("")),
    m_central_gv(new GL_QGraphicsView(m_central_gs)),
    m_right_gs(new QGraphicsScene()),
    m_right_fps_item(m_right_gs->addText("")),
    m_right_gv(new GL_QGraphicsView(m_right_gs)),
    m_right_dock_widget(new QDockWidget("right graphicsview")),
    m_bottom_gs(new QGraphicsScene()),
    m_bottom_fps_item(m_bottom_gs->addText("")),
    m_bottom_gv(new GL_QGraphicsView(m_bottom_gs)),
    m_bottom_dock_widget(new QDockWidget("bottom graphicsview")),
    m_refresh_timer(new QTimer())
{
    setCentralWidget(m_central_gv);
    m_right_dock_widget->setWidget(m_right_gv);
    m_right_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::RightDockWidgetArea, m_right_dock_widget);
    m_bottom_dock_widget->setWidget(m_bottom_gv);
    m_bottom_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::BottomDockWidgetArea, m_bottom_dock_widget);
    QToolBar* t = addToolBar("dock widget visibility");
    t->addAction(m_right_dock_widget->toggleViewAction());
    t->addAction(m_bottom_dock_widget->toggleViewAction());

    QFont font("Monospace");
    font.setPixelSize(20);

    m_central_gs->setBackgroundBrush(QBrush(Qt::black));
    m_central_fps_item->setFont(font);
    m_central_fps_item->setDefaultTextColor(QColor(255,255,0,255));
    m_right_fps_item->setFont(font);
    m_right_fps_item->setDefaultTextColor(QColor(255,0,255,255));
    m_bottom_fps_item->setFont(font);
    m_bottom_fps_item->setDefaultTextColor(QColor(0,255,255,255));

    m_refresh_timer->setSingleShot(false);
    connect(m_refresh_timer, &QTimer::timeout, this, &MainWindow::on_refresh_timer_timeout);
    m_refresh_timer->start(0);

    resize(1024, 768);
}

MainWindow::~MainWindow()
{
    delete m_central_gv;
    delete m_central_gs;
    delete m_right_gv;
    delete m_right_gs;
    delete m_right_dock_widget;
    delete m_bottom_gv;
    delete m_bottom_gs;
    delete m_bottom_dock_widget;
    delete m_refresh_timer;
}

void MainWindow::on_refresh_timer_timeout()
{
    QString s{m_fps_counter.qstring_query_update()};
    m_central_fps_item->setPlainText(s);
    m_right_fps_item->setPlainText(s);
    m_bottom_fps_item->setPlainText(s);
}
