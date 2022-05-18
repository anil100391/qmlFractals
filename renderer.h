#ifndef RENDERER_H
#define RENDERER_H

#include <QSize>

#include <QObject>
#include <QOpenGLFunctions>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class QQuickWindow;
class QOpenGLShaderProgram;

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
    QSize                     m_viewportSize;
    qreal                     m_t;
    QOpenGLShaderProgram     *m_program;
    QQuickWindow             *m_window;
};

#endif // RENDERER_H
