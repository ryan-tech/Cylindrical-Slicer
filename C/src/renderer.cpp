#include <QMouseEvent>

#include <cmath>
#include <utility>

#include "renderer.h"
#include "background.h"
#include "glmesh.h"
#include "mesh.h"

Renderer::Renderer(const QSurfaceFormat& format, QWidget *parent)
    : QOpenGLWidget(parent), mesh(nullptr),
      scale(1), zoom(1), tilt(90), yaw(0),
      perspective(0.25), anim(this, "perspective"), status(" ")
{
	setFormat(format);
    QFile styleFile(":/qt/style.qss");
    styleFile.open( QFile::ReadOnly );
    setStyleSheet(styleFile.readAll());
    sliced = false;
    anim.setDuration(100);
}

Renderer::~Renderer()
{
	makeCurrent();
	delete mesh;
	delete bedMesh;
	doneCurrent();
}

void Renderer::view_anim(float v)
{
    anim.setStartValue(perspective);
    anim.setEndValue(v);
    anim.start();
}

void Renderer::orthographic_view()
{
    view_anim(0);
}

void Renderer::perspective_view()
{
    view_anim(0.25);
}

void Renderer::render_shaded_shader()
{
    setDrawMode(0);
}

void Renderer::render_wireframe_shader()
{
    setDrawMode(1);
}

void Renderer::load_mesh(Mesh* m, Mesh* b, bool is_reload)
{
    mesh = new GLMesh(m);
    bedMesh = new GLMesh(b);

    if (!is_reload)
    {
        QVector3D lower(m->xmin(), m->ymin(), m->zmin());
        QVector3D upper(m->xmax(), m->ymax(), m->zmax());
        center = (lower + upper) / 2;
        scale = 2 / (upper - lower).length();

        // Reset other camera parameters
        zoom = .5;
        yaw = 0;
        tilt = 90;
    }

    update();

    delete m;
}

void Renderer::setStatus(const QString &s)
{
    status = s;
    update();
}

void Renderer::setPerspective(float p)
{
    perspective = p;
    update();
}

void Renderer::setDrawMode(int mode)
{
    drawMode = mode;
    update();
}

void Renderer::clearStatus()
{
    status = "";
    update();
}

void Renderer::initializeGL()
{
    initializeOpenGLFunctions();

    mesh_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/gl_files/mesh.vert");
    mesh_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/gl_files/mesh.frag");
    mesh_shader.link();
    mesh_wireframe_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/gl_files/mesh.vert");
    mesh_wireframe_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/gl_files/mesh_wireframe.frag");
    mesh_wireframe_shader.link();

    backdrop = new Background();
}

void Renderer::draw_slice(std::vector<lineSegment> vec) {

    for (int i = 0; i < v.size(); i++)
    {
        glBegin(GL_LINES);
        glVertex3f(v.at(i).start.x,v.at(i).start.y,v.at(i).start.z);//.at(i).start.x,i.start.y,i.start.z);
        glVertex3f(v.at(i).end.x,v.at(i).end.y,v.at(i).end.z);
        glEnd();
    }

    update();
}

void Renderer::paintGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    backdrop->draw();
    if(sliced)
    {
        for (int i = 0; i < v.size(); i++) {
            glBegin(GL_LINES);
            glVertex3f(v.at(i).start.x, v.at(i).start.y, v.at(i).start.z);//.at(i).start.x,i.start.y,i.start.z);
            glVertex3f(v.at(i).end.x, v.at(i).end.y, v.at(i).end.z);
            glEnd();
        }
    }
    else
    {
        if (mesh)
        {
            draw_mesh(mesh);
            draw_mesh(bedMesh);
        }
    }
    if (status.isNull())  return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawText(10, height() - 10, status);


	update();
}

void Renderer::draw_mesh(GLMesh* m)
{
    QOpenGLShaderProgram* selected_mesh_shader = NULL;
    // Set gl_files draw mode
    if(drawMode == 1)
    {
        selected_mesh_shader = &mesh_wireframe_shader;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        selected_mesh_shader = &mesh_shader;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    selected_mesh_shader->bind();

    // Load the transform and view matrices into the shader
    glUniformMatrix4fv(
                selected_mesh_shader->uniformLocation("transform_matrix"),
                1, GL_FALSE, transform_matrix().data());
    glUniformMatrix4fv(
                selected_mesh_shader->uniformLocation("view_matrix"),
                1, GL_FALSE, view_matrix().data());

    // Compensate for z-flattening when zooming
    glUniform1f(selected_mesh_shader->uniformLocation("zoom"), 1/zoom);

    // Find and enable the attribute location for vertex position
    const GLuint vp = selected_mesh_shader->attributeLocation("vertex_position");
    glEnableVertexAttribArray(vp);

    // Then draw the mesh with that vertex position
    m->draw(vp);

    // Reset draw mode for the background and anything else that needs to be drawn
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Clean up state machine
    glDisableVertexAttribArray(vp);
    selected_mesh_shader->release();
}

QMatrix4x4 Renderer::transform_matrix() const
{
    QMatrix4x4 m;
    m.rotate(tilt, QVector3D(1, 0, 0));
    m.rotate(yaw,  QVector3D(0, 0, 1));
    m.scale(-scale, scale, -scale);
    m.translate(-center);
    return m;
}

QMatrix4x4 Renderer::view_matrix() const
{
    QMatrix4x4 m;
    if (width() > height())
    {
        m.scale(-height() / float(width()), 1, 0.5);
    }
    else
    {
        m.scale(-1, width() / float(height()), 0.5);
    }
    m.scale(zoom, zoom, 1);
    m(3, 2) = perspective;
    return m;
}

void Renderer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton ||
        event->button() == Qt::RightButton)
    {
        mouse_pos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void Renderer::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton ||
        event->button() == Qt::RightButton)
    {
        unsetCursor();
    }
}

void Renderer::mouseMoveEvent(QMouseEvent* event)
{
    auto p = event->pos();
    auto d = p - mouse_pos;


    if (event->buttons() & Qt::LeftButton)
    {
        yaw = fmod(yaw - d.x(), 360);
        tilt = fmod(tilt - d.y(), 360);
        update();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        center = transform_matrix().inverted() *
                 view_matrix().inverted() *
                 QVector3D(-d.x() / (0.5*width()),
                            d.y() / (0.5*height()), 0);
        update();
    }
    mouse_pos = p;
}

void Renderer::wheelEvent(QWheelEvent *event)
{
    // Find GL position before the zoom operation
    // (to zoom about mouse cursor)
    auto p = event->pos();
    QVector3D v(1 - p.x() / (0.5*width()),
                p.y() / (0.5*height()) - 1, 0);
    QVector3D a = transform_matrix().inverted() *
                  view_matrix().inverted() * v;

    if (event->delta() < 0)
    {
        for (int i=0; i > event->delta(); --i)
            zoom *= 1.001;
    }
    else if (event->delta() > 0)
    {
        for (int i=0; i < event->delta(); ++i)
            zoom /= 1.001;
    }

    // Then find the cursor's GL position post-zoom and adjust center.
    QVector3D b = transform_matrix().inverted() *
                  view_matrix().inverted() * v;
    center += b - a;
    update();
}

void Renderer::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::set_slice(std::vector<lineSegment> vec) {
    v = std::move(vec);
}
