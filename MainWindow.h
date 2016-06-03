#pragma once

#include <QtCore>
#include <QtWidgets>
#include "FPSCounter.h"
#include "GL_QGraphicsView.h"

class MainWindow
  : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QGraphicsScene* m_central_gs;
    QGraphicsTextItem* m_central_fps_item;
    GL_QGraphicsView* m_central_gv;
    QGraphicsScene* m_right_gs;
    QGraphicsTextItem* m_right_fps_item;
    GL_QGraphicsView* m_right_gv;
    QDockWidget* m_right_dock_widget;
    QGraphicsScene* m_bottom_gs;
    QGraphicsTextItem* m_bottom_fps_item;
    GL_QGraphicsView* m_bottom_gv;
    QDockWidget* m_bottom_dock_widget;
    QTimer* m_refresh_timer;
    FPSCounter m_fps_counter;

protected slots:
    void on_refresh_timer_timeout();
};
