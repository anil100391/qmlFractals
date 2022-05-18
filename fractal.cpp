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
    CleanupJob(Renderer *renderer) : m_renderer(renderer) {}
    void run() override { delete m_renderer; }
private:
    Renderer *m_renderer;
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
        m_renderer = new Renderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &Renderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &Renderer::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());
}
