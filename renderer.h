#ifndef RENDERER_H
#define RENDERER_H

#include "fractalParams.h"

#include <QSize>

#include <QObject>
#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class QQuickWindow;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class FractalFrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
public:

    FractalFrameBufferObjectRenderer() = default;
    virtual ~FractalFrameBufferObjectRenderer();

    void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;

    void setFractalParams(const FractalParams& params);

private:
    void init(QQuickFramebufferObject *item);
    void allocatePositionBuffer();
    QVector2D pixelToCoord(const QVector2D& pixel) const;

    FractalParams             m_fractalParams;
    CartesianGridView         m_viewParams;
    QSize                     m_size{600, 400};

    // gl stuff
    QOpenGLBuffer            *m_positionBuffer = nullptr;
    QOpenGLBuffer            *m_indexBuffer = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;
    QOpenGLShaderProgram     *m_program = nullptr;
};

#endif // RENDERER_H
