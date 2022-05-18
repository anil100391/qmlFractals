#ifndef RENDERER_H
#define RENDERER_H

#include <QSize>

#include <QObject>
#include <QOpenGLFunctions>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class QQuickWindow;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class Renderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Renderer() : m_t(0), m_program(0) {}
    ~Renderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

public slots:
    void init();
    void paint();

private:
    void allocatePositionBuffer(int w, int h);

    QSize                     m_viewportSize;
    qreal                     m_t;
    QOpenGLBuffer            *m_positionBuffer = nullptr;
    QOpenGLBuffer            *m_indexBuffer = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;
    QOpenGLShaderProgram     *m_program = nullptr;
    QQuickWindow             *m_window = nullptr;
};

#endif // RENDERER_H
