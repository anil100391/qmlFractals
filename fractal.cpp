#include "fractal.h"
#include "renderer.h"

#include <QtCore/QRunnable>

#include <QQuickWindow>
#include <QOpenGLContext>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class CleanupJob : public QRunnable
{
public:
    CleanupJob(MeshRenderer *renderer) : m_renderer(renderer) {}
    void run() override { delete m_renderer; }
private:
    MeshRenderer *m_renderer;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Fractal::Fractal()
    : m_t(0),
      m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &Fractal::handleWindowChanged);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Fractal::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Fractal::handleWindowChanged(QQuickWindow *win)
{
    if (win)
    {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &Fractal::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Fractal::cleanup, Qt::DirectConnection);
        // Ensure we start with cleared to black. The squircle's blend mode relies on this.
        win->setColor(Qt::black);
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Fractal::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Fractal::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Fractal::sync()
{
    if (!m_renderer)
    {
        m_renderer = new MeshRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &MeshRenderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &MeshRenderer::paint, Qt::DirectConnection);
    }
//    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
 //   m_renderer->setWindow(window());
}

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QQuickOpenGLUtils>

class MyFrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
public:
    MyFrameBufferObjectRenderer()
    {
    }

    void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE
    {
        m_render.init();

        MyFrameBufferObject *i = static_cast<MyFrameBufferObject *>(item);
        // m_render.setAzimuth(i->azimuth());
        // m_render.setElevation(i->elevation());
        // m_render.setDistance(i->distance());
    }

    void render() Q_DECL_OVERRIDE
    {
        m_render.paint();
        QQuickOpenGLUtils::resetOpenGLState();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE
    {
        QOpenGLFramebufferObjectFormat format;
        format.setSamples(4);
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        return new QOpenGLFramebufferObject(size, format);
    }

private:
    MeshRenderer m_render;
};



// MyFrameBufferObject implementation

MyFrameBufferObject::MyFrameBufferObject(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
{
    setMirrorVertically(false);
}

QQuickFramebufferObject::Renderer *MyFrameBufferObject::createRenderer() const
{
    return new MyFrameBufferObjectRenderer;
}

void MyFrameBufferObject::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    update();
}
