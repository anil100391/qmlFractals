#ifndef FRACTAL_H
#define FRACTAL_H

#include <QQuickWindow>
#include <QQuickFramebufferObject>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class FractalFrameBufferObject : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY iterationsChanged)
    Q_PROPERTY(float iterations READ iterations WRITE setIterations NOTIFY modeChanged)

public:
    explicit FractalFrameBufferObject(QQuickItem *parent = nullptr);
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    int mode() const;
    void setMode(int mode);

    float iterations() const;
    void setIterations(float iterations);

    Renderer* getRenderer() const { return m_renderer; }

signals:
    void modeChanged();
    void iterationsChanged();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
#if !ANDROID
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif

private:

    float          m_iterations = 100.0f;
    Renderer      *m_renderer = nullptr;
};

#endif // FRACTAL_H
