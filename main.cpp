#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "fractal.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:main.qml"));
    view.show();

    return app.exec();
}
