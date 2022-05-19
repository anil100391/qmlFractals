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
void FractalFrameBufferObject::setMode(int mode)
{
    if (mode == m_params.type)
        return;

    m_params.type = static_cast<FractalParams::TYPE>(mode);

    auto r = static_cast<FractalFrameBufferObjectRenderer*>(getRenderer());
    if (r)
    {
        r->setFractalParams(m_params);
    }

    emit modeChanged();
    update();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void FractalFrameBufferObject::mousePressEvent(QMouseEvent *event)
{

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void FractalFrameBufferObject::mouseMoveEvent(QMouseEvent *event)
{
    int h = window()->height();
    int x = event->position().x();
    int y = h - event->position().y();

    // h -> m_spanY
    float ycoord = m_left.y() + (m_spanY * y) / h;
    float xcoord = m_left.x() + (m_spanY * x / h);
    m_params.m_c0.setX(x);
    m_params.m_c0.setY(y);

    auto r = static_cast<FractalFrameBufferObjectRenderer*>(getRenderer());
    if (r)
    {
        r->setFractalParams(m_params);
    }

    QQuickItem::mouseMoveEvent(event);
    update();
}
