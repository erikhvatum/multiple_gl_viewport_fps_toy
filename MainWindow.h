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

    inline QToolBar* toolbar() {
        return m_toolbar;
    }

protected:
    QGraphicsScene* m_central_gs;
    QGraphicsTextItem* m_central_fps_item;
    GL_QGraphicsView* m_central_gv;
    QAction m_central_swap_interval;
    QGraphicsScene* m_right_gs;
    QGraphicsTextItem* m_right_fps_item;
    GL_QGraphicsView* m_right_gv;
    QDockWidget* m_right_dock_widget;
    QAction m_right_swap_interval;
    QGraphicsScene* m_bottom_gs;
    QGraphicsTextItem* m_bottom_fps_item;
    GL_QGraphicsView* m_bottom_gv;
    QDockWidget* m_bottom_dock_widget;
    QAction m_bottom_swap_interval;
    QTimer* m_refresh_timer;
    FPSCounter m_fps_counter;
    QToolBar* m_toolbar;

protected slots:
    void on_refresh_timer_timeout();
    void on_central_swap_interval_toggled(bool checked);
    void on_right_swap_interval_toggled(bool checked);
    void on_bottom_swap_interval_toggled(bool checked);
};
