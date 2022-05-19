#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "fractal.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);
    qmlRegisterType<MyFrameBufferObject>("MyRenderLibrary", 42, 0, "MeshRenderer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:main.qml"));
    view.resize(600, 400);
    view.show();

    return app.exec();
}
