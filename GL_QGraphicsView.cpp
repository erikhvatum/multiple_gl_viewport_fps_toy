#include "GL_QGraphicsView.h"

GL_QGraphicsView::GL_QGraphicsView(int swap_interval, QGraphicsScene* scene)
  : m_glw(new QOpenGLWidget)
{
    QSurfaceFormat fmt = m_glw->format();
    fmt.setSwapInterval(swap_interval);
    m_glw->setFormat(fmt);
    setViewport(m_glw);
    setScene(scene);
}

GL_QGraphicsView::~GL_QGraphicsView()
{
    delete m_glw;
}
