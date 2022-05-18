#include "renderer.h"

#include <QRunnable>
#include <QQuickWindow>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Renderer::init()
{
    if (!m_program)
    {
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);

        initializeOpenGLFunctions();

        // Create VAO for first object to render
        m_vao = new QOpenGLVertexArrayObject();
        m_vao->create();
        m_vao->bind();

        // Setup VBOs and IBO (use QOpenGLBuffer to buffer data,
        // specify format, usage hint etc). These will be
        // remembered by the currently bound VAO
        m_positionBuffer = new QOpenGLBuffer();
        m_positionBuffer->create();
        m_positionBuffer->setUsagePattern( QOpenGLBuffer::StaticDraw );
        allocatePositionBuffer(m_window->width(), m_window->height());

        m_indexBuffer = new QOpenGLBuffer();
        m_indexBuffer->create();
        m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_indexBuffer->bind();
        unsigned int indexData[] = { 0, 1, 2, 0, 2, 3 };
        m_indexBuffer->allocate( indexData, 3 * 2 * sizeof( unsigned int ) );

        m_program = new QOpenGLShaderProgram();
        m_program->create();
        m_program->bind();

        m_program->enableAttributeArray(0);
        m_program->setAttributeBuffer( 0, GL_FLOAT, 0, 2 );

        #include "vert.shader"
        std::string versionStr;
#if ANDROID
        versionStr = "#version 300 es\n";
#else
        versionStr = "#version 330 core\n";
#endif
        std::string vertexShader = versionStr + vshader;

        if ( !m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShader.c_str()) )
        {
        QString log = m_program->log();
        }

        #include "frag.shader"
        std::string fragShader = versionStr + fshader;
        if ( !m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragShader.c_str()) )
        {
        QString log = m_program->log();
        }

        m_program->link();
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Renderer::paint()
{
    // Play nice with the RHI. Not strictly needed when the scenegraph uses
    // OpenGL directly.
    m_window->beginExternalCommands();

    float w = m_viewportSize.width();
    float h = m_viewportSize.height();

    glViewport(0, 0, w, h);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT );
    // Bind shader program, textures for first set of objects
    m_vao->bind();
    m_positionBuffer->bind();
    m_indexBuffer->bind();
    m_program->bind();
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer( 0, GL_FLOAT, 0, 2 );

    auto log = m_program->log();
    QMatrix4x4 mvp;
    mvp.ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);

    QVector2D m_c0(0.0f, 0.0f);
    float m_spanY = 3.0f;
    QVector2D m_center(0.0f, 0.0f);
    int m_mode = 1;
    bool m_showGrid = true;
    m_program->setUniformValue("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
    m_program->setUniformValue("u_MVP", mvp);
    m_program->setUniformValue("u_C0", -3 + (4.0 * m_c0.x())/w, -1.5 + (3.0 * m_c0.y())/h);
    m_program->setUniformValue("u_AspectRatio", 1.0f * w / h);
    m_program->setUniformValue("u_SpanY", m_spanY);
    m_program->setUniformValue("u_Center", m_center);
    m_program->setUniformValue("u_Mode", m_mode);
    m_program->setUniformValue("u_Width", w);
    m_program->setUniformValue("u_Height", h);
    m_program->setUniformValue("u_ShowGrid", (m_showGrid && m_mode != 2) ? 1 : 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    m_program->disableAttributeArray(0);
    /*
    m_vao->release();
    m_positionBuffer->release();
    m_indexBuffer->release();
    m_program->release();
    */

    m_window->endExternalCommands();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
Renderer::~Renderer()
{
    delete m_positionBuffer;
    delete m_indexBuffer;
    delete m_vao;
    delete m_program;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void Renderer::allocatePositionBuffer(int w, int h)
{
    if (w == -1)
        w = m_window->width();
    if (h == -1)
        h = m_window->height();

    m_positionBuffer->bind();
    float pad = 0.0f;
    float positionData[] = { pad, pad,
                             w - pad, pad,
                             w - pad, h - pad,
                             pad, h - pad
                           };
    int vertexCount = 4;
    m_positionBuffer->allocate( positionData, vertexCount * 2 * sizeof( float ) );
}

