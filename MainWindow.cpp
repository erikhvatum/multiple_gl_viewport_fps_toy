#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    m_central_gs(new QGraphicsScene()),
    m_central_fps_item(m_central_gs->addText("")),
    m_central_gv(new GL_QGraphicsView(0, m_central_gs)),
    m_central_swap_interval("central swapInterval == 0"),
    m_left_widget(new QWidget()),
    m_left_dock_widget(new QDockWidget("left widget")),
    m_right_gs(new QGraphicsScene()),
    m_right_fps_item(m_right_gs->addText("")),
    m_right_gv(new GL_QGraphicsView(0, m_right_gs)),
    m_right_dock_widget(new QDockWidget("right graphicsview")),
    m_right_swap_interval("right swapInterval == 0"),
    m_bottom_gs(new QGraphicsScene()),
    m_bottom_fps_item(m_bottom_gs->addText("")),
    m_bottom_gv(new GL_QGraphicsView(0, m_bottom_gs)),
    m_bottom_dock_widget(new QDockWidget("bottom graphicsview")),
    m_bottom_swap_interval("bottom swapInterval == 0"),
    m_refresh_timer(new QTimer())
{
    setCentralWidget(m_central_gv);
    m_central_swap_interval.setToolTip(
        "When set, central.format().swapInterval() == 0\n"
        "When unset, central.format().swapInterval() == 1");
    m_central_swap_interval.setCheckable(true);
    m_central_swap_interval.setChecked(true);
    connect(&m_central_swap_interval, &QAction::toggled, this, &MainWindow::on_central_swap_interval_toggled);

    m_left_fps_label = new QLabel();
    m_left_widget->setLayout(new QVBoxLayout());
    m_left_widget->layout()->addWidget(m_left_fps_label);
    m_left_dock_widget->setWidget(m_left_widget);
    m_left_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::LeftDockWidgetArea, m_left_dock_widget);

    m_right_dock_widget->setWidget(m_right_gv);
    m_right_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::RightDockWidgetArea, m_right_dock_widget);
    m_right_swap_interval.setToolTip(
        "When set, right.format().swapInterval() == 0\n"
        "When unset, right.format().swapInterval() == 1");
    m_right_swap_interval.setCheckable(true);
    m_right_swap_interval.setChecked(true);
    connect(&m_right_swap_interval, &QAction::toggled, this, &MainWindow::on_right_swap_interval_toggled);

    m_bottom_dock_widget->setWidget(m_bottom_gv);
    m_bottom_dock_widget->setAllowedAreas(Qt::AllDockWidgetAreas);
    addDockWidget(Qt::BottomDockWidgetArea, m_bottom_dock_widget);
    m_bottom_swap_interval.setToolTip(
        "When set, bottom.format().swapInterval() == 0\n"
        "When unset, bottom.format().swapInterval() == 1");
    m_bottom_swap_interval.setCheckable(true);
    m_bottom_swap_interval.setChecked(true);
    connect(&m_bottom_swap_interval, &QAction::toggled, this, &MainWindow::on_bottom_swap_interval_toggled);

    m_toolbar = new QToolBar();
    addToolBar(Qt::LeftToolBarArea, m_toolbar);
    m_toolbar->addAction(&m_central_swap_interval);
    m_toolbar->addAction(m_right_dock_widget->toggleViewAction());
    m_toolbar->addAction(m_left_dock_widget->toggleViewAction());
    m_toolbar->addAction(&m_right_swap_interval);
    m_toolbar->addAction(m_bottom_dock_widget->toggleViewAction());
    m_toolbar->addAction(&m_bottom_swap_interval);

    QFont font("Monospace");
    font.setPixelSize(20);

    m_central_gs->setBackgroundBrush(QBrush(Qt::black));
    m_central_fps_item->setFont(font);
    m_central_fps_item->setDefaultTextColor(QColor(255,255,0,255));
    m_right_gs->setBackgroundBrush(QBrush(Qt::white));
    m_right_fps_item->setFont(font);
    m_right_fps_item->setDefaultTextColor(QColor(255,0,255,255));
    m_bottom_gs->setBackgroundBrush(QBrush(Qt::white));
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
    delete m_left_widget;
    delete m_left_dock_widget;
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
    m_left_fps_label->setText(s);
    m_right_fps_item->setPlainText(s);
    m_bottom_fps_item->setPlainText(s);
}

void MainWindow::on_central_swap_interval_toggled(bool checked)
{
    m_central_gv->deleteLater();
    m_central_gv = new GL_QGraphicsView(checked ? 0 : 1, m_central_gs);
    setCentralWidget(m_central_gv);
}

void MainWindow::on_right_swap_interval_toggled(bool checked)
{
    m_right_gv->deleteLater();
    m_right_gv = new GL_QGraphicsView(checked ? 0 : 1, m_right_gs);
    m_right_dock_widget->setWidget(m_right_gv);
}

void MainWindow::on_bottom_swap_interval_toggled(bool checked)
{
    m_bottom_gv->deleteLater();
    m_bottom_gv = new GL_QGraphicsView(checked ? 0 : 1, m_bottom_gs);
    m_bottom_dock_widget->setWidget(m_bottom_gv);
}
