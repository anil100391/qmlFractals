#include "renderer.h"

#include <QRunnable>
#include <QQuickWindow>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void MeshRenderer::init()
{
    if (!m_program)
    {
        // Create VAO for first object to render
        m_vao = new QOpenGLVertexArrayObject();
        m_vao->create();
        m_vao->bind();

        // Setup VBOs and IBO (use QOpenGLBuffer to buffer data,
        // specify format, usage hint etc). These will be
        // remembered by the currently bound VAO
        m_positionBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_positionBuffer->create();
        m_positionBuffer->setUsagePattern( QOpenGLBuffer::StaticDraw );
        allocatePositionBuffer(600, 400);

        m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_indexBuffer->create();
        m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_indexBuffer->bind();
        unsigned int indexData[] = { 0, 1, 2, 0, 2, 3 };
        m_indexBuffer->allocate( indexData, 3 * 2 * sizeof( unsigned int ) );

        m_program = new QOpenGLShaderProgram();
        m_program->create();
        m_program->bind();

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

        m_positionBuffer->bind();
        m_program->enableAttributeArray("position");
        m_program->setAttributeBuffer("position", GL_FLOAT, 0, 2);
        m_vao->release();
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void MeshRenderer::paint()
{
    auto cxt = QOpenGLContext::currentContext();
    auto f = cxt->functions();

    GLint viewportSize[4];
    f->glGetIntegerv(GL_VIEWPORT, viewportSize);
    QSize m_viewportSize;
    m_viewportSize.setWidth(viewportSize[2]);
    m_viewportSize.setHeight(viewportSize[3]);
    float w = m_viewportSize.width();
    float h = m_viewportSize.height();

    f->glDisable(GL_DEPTH_TEST);
    f->glEnable(GL_BLEND);
    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // Bind shader program, textures for first set of objects
    m_program->bind();
    QMatrix4x4 mvp;
    mvp.ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);

    QVector2D m_c0(0.0f, 0.0f);
    float m_spanY = 3.0f;
    QVector2D m_center(0.0f, 0.0f);
    bool m_showGrid = true;
    m_program->setUniformValue("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
    m_program->setUniformValue("u_MVP", mvp);
    m_program->setUniformValue("u_C0", -3 + (4.0 * m_c0.x())/w, -1.5 + (3.0 * m_c0.y())/h);
    m_program->setUniformValue("u_AspectRatio", 1.0f * w / h);
    m_program->setUniformValue("u_SpanY", m_spanY);
    m_program->setUniformValue("u_Center", m_center);
    m_program->setUniformValue("u_Mode", m_mode);
    m_program->setUniformValue("u_Width", (int)w);
    m_program->setUniformValue("u_Height", (int)h);
    m_program->setUniformValue("u_ShowGrid", (m_showGrid && m_mode != 2) ? 1 : 0);

    m_vao->bind();
    f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    m_vao->release();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
MeshRenderer::~MeshRenderer()
{
    m_positionBuffer->destroy();
    m_indexBuffer->destroy();
    m_vao->destroy();
    delete m_program;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void MeshRenderer::allocatePositionBuffer(int w, int h)
{
    if (w == -1)
        w = 600;
    if (h == -1)
        h = 400;

    w*=2;
    h*=2;
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
