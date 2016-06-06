#pragma once

#include <QtCore>
#include <QtWidgets>

class GL_QGraphicsView
  : public QGraphicsView
{
    Q_OBJECT
public:
    GL_QGraphicsView(int swap_interval, QGraphicsScene* scene);
    ~GL_QGraphicsView();

protected:
    QOpenGLWidget* m_glw;
};
