#ifndef FRACTAL_H
#define FRACTAL_H

#include "fractalParams.h"

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

    int mode() const { return m_params.type; }
    void setMode(int mode);

    Renderer* getRenderer() const { return m_renderer; }

signals:
    void modeChanged();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:

    Renderer      *m_renderer = nullptr;
    FractalParams  m_params;
    QVector2D      m_left{-3.0f, -1.5f};
    float          m_spanY = 3.0f;
};

#endif // FRACTAL_H
