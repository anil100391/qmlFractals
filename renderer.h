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
class MeshRenderer : public QObject
{
    Q_OBJECT
public:
    MeshRenderer() : m_t(0), m_program(0) {}
    ~MeshRenderer();

    void setT(qreal t) { m_t = t; }

public slots:
    void init();
    void paint();

private:
    void allocatePositionBuffer(int w, int h);

    qreal                     m_t;
    QOpenGLBuffer            *m_positionBuffer = nullptr;
    QOpenGLBuffer            *m_indexBuffer = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;
    QOpenGLShaderProgram     *m_program = nullptr;
};

#endif // RENDERER_H
