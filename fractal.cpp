#include "fractal.h"
#include "renderer.h"

#include <QQuickWindow>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QQuickOpenGLUtils>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
FractalFrameBufferObject::FractalFrameBufferObject(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
    setMirrorVertically(false);
    setAcceptedMouseButtons(Qt::AllButtons);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
QQuickFramebufferObject::Renderer *FractalFrameBufferObject::createRenderer() const
{
    auto ncthis = const_cast<FractalFrameBufferObject*>(this);
    ncthis->m_renderer = new FractalFrameBufferObjectRenderer;
    return m_renderer;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int FractalFrameBufferObject::mode() const
{
    auto r = static_cast<FractalFrameBufferObjectRenderer*>(getRenderer());
    if (r)
    {
        auto params = r->getFractalParams();
        return params.type;
    }

    return FractalParams().type;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void FractalFrameBufferObject::setMode(int mode)
{
    auto r = static_cast<FractalFrameBufferObjectRenderer*>(getRenderer());
    if (r)
    {
        auto params = r->getFractalParams();
        if (mode == params.type)
            return;

        params.type = static_cast<FractalParams::TYPE>(mode);
        r->setFractalParams(params);
        emit modeChanged();
        update();
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void FractalFrameBufferObject::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void FractalFrameBufferObject::wheelEvent(QWheelEvent *event)
{
    auto r = static_cast<FractalFrameBufferObjectRenderer*>(getRenderer());
    if (r)
    {
        auto viewParams = r->getViewParams();
        viewParams.m_distPerPixel += (event->angleDelta().y() > 0 ? 1 : -1) * 0.001f;
        r->setViewParams(viewParams);
        update();
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void FractalFrameBufferObject::mouseMoveEvent(QMouseEvent *event)
{
    int h = window()->height();
    int x = event->position().x();
    int y = h - event->position().y();

    auto r = static_cast<FractalFrameBufferObjectRenderer*>(getRenderer());
    if (r)
    {
        auto params = r->getFractalParams();
        params.m_c0.setX(x);
        params.m_c0.setY(y);
        r->setFractalParams(params);
    }

    QQuickItem::mouseMoveEvent(event);
    update();
}
