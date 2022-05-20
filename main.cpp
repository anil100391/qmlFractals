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
#if ANDROID
    format.setVersion(3, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGLES);
#else
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
#endif
    QSurfaceFormat::setDefaultFormat(format);
    qmlRegisterType<FractalFrameBufferObject>("MyRenderLibrary", 42, 0, "MeshRenderer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:main.qml"));
    view.show();

    return app.exec();
}
