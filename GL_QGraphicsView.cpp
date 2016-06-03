#include "GL_QGraphicsView.h"

GL_QGraphicsView::GL_QGraphicsView(QGraphicsScene* scene)
  : m_glw(new QOpenGLWidget)
{
    setViewport(m_glw);
    setScene(scene);
}

GL_QGraphicsView::~GL_QGraphicsView()
{
    delete m_glw;
}
