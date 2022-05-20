#ifndef FRACTAL_H
#define FRACTAL_H

#include <QQuickWindow>
#include <QQuickFramebufferObject>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class FractalFrameBufferObject : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)

public:
    explicit FractalFrameBufferObject(QQuickItem *parent = nullptr);
    Renderer *createRenderer() const Q_DECL_OVERRIDE;

    int mode() const;
    void setMode(int mode);

    Renderer* getRenderer() const { return m_renderer; }

signals:
    void modeChanged();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:

    Renderer      *m_renderer = nullptr;
};

#endif // FRACTAL_H
