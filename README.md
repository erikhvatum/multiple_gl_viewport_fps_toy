Multiple GL Viewport FPS Toy
====================================================================

This is a small test application I wrote and used to help me understand the
impact of setting the various permutations of the following:
* Setting swapInterval to 0 versus 1 ...
* for top-level QOpenGLWidgets versus child QOpenGLWidgets ...
* for the QOpenGLWidgets themselves vs via the static method
QSurfaceFormat::setDefaultFormat.

My conclusion after developing and experimenting with this tool on the
various desktop platforms supported by Qt5 is that, in the case where you have
more only one visible QOpenGLWidget instance, QSurfaceFormat::setDefaultFormat
with swap interval 1 is fine if you wish to avoid drawing frames that will
never be displayed.  However, it is important to call
QSurfaceFormat::setDefaultFormat with swap interval of 0 before making any
QOpenGLWidgets if more than one QOpenGLWidget will ever be visible
simultaneously.  Failure to do so incurs serious performance degredation,
limiting FPS to (# of visible QOpenGLWidgets) / (screen refresh rate).