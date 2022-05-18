#ifndef FRACTAL_H
#define FRACTAL_H

#include <QQuickItem>
#include <QQuickWindow>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class Renderer;

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
class Fractal : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
    QML_ELEMENT

public:
    Fractal();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    void releaseResources() override;

    qreal            m_t;
    Renderer        *m_renderer;
};

#endif // FRACTAL_H
