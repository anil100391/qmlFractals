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
    void allocatePositionBuffer();

    FractalParams             m_params;
    QSize                     m_size{600, 400};

    // gl stuff
    QOpenGLBuffer            *m_positionBuffer = nullptr;
    QOpenGLBuffer            *m_indexBuffer = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;
    QOpenGLShaderProgram     *m_program = nullptr;
};

#endif // RENDERER_H
