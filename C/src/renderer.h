#ifndef RENDERER_H
#define RENDERER_H
#include "ModelPrint.h"
#include "background.h"
#include "mesh.h"
#include "glmesh.h"

#include <QtOpenGL>
#include <QMouseEvent>
#include <cmath>
#include <utility>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>


class Background;
class Mesh;
class GLMesh;

class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
	explicit Renderer(const QSurfaceFormat& format, QWidget* parent=0);
    ~Renderer();

    void orthographic_view();
    void perspective_view();
    void render_shaded_shader();
    void render_wireframe_shader();
    void set_sliced(bool s) { sliced = s;}
    void draw_slice(std::vector<lineSegment> v);
    void set_slice(std::vector<lineSegment> v);

public slots:
    void setStatus(const QString& s);
    void clearStatus();
    void load_mesh(Mesh* m, Mesh* b, bool is_reload);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    void setDrawMode(int mode);
    void view_anim(float v);
    void setPerspective(float p);

    void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;


private:
    void draw_mesh(GLMesh* m);

    QMatrix4x4 view_matrix() const;
    QMatrix4x4 transform_matrix() const;


    QOpenGLShaderProgram mesh_shader;
    QOpenGLShaderProgram quad_shader;
    QOpenGLShaderProgram mesh_wireframe_shader;


    float perspective;
    int drawMode;

    float camera_scale;
    float camera_tilt;
    float camera_yaw;
    float camera_zoom;

    QVector3D center;


    Q_PROPERTY(float perspective MEMBER perspective WRITE setPerspective);
    QPropertyAnimation anim;

    GLMesh* mesh;
    std::vector<lineSegment> v;
    GLMesh* bedMesh;
    Background* backdrop;

    QPoint mouse_pos;
    QString status;

    bool sliced;
};

#endif
