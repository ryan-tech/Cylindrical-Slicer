#ifndef CANVAS_H
#define CANVAS_H

#include <QtOpenGL>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>
#include "ModelPrint.h"

class GLMesh;
class Mesh;
class Background;


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
	void paintGL() override;
	void initializeGL() override;
	void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    
	void setPerspective(float p);
    void setDrawMode(int mode);
    void view_anim(float v);

private:
    void draw_mesh(GLMesh* m);

    QMatrix4x4 transform_matrix() const;
    QMatrix4x4 view_matrix() const;

    QOpenGLShaderProgram mesh_shader;
    QOpenGLShaderProgram mesh_wireframe_shader;
	QOpenGLShaderProgram quad_shader;

    GLMesh* mesh;
    std::vector<lineSegment> v;
    GLMesh* bedMesh;
    Background* backdrop;

    QVector3D center;
    float scale;
    float zoom;
    float tilt;
    float yaw;

    float perspective;
    int drawMode;
    Q_PROPERTY(float perspective MEMBER perspective WRITE setPerspective);
    QPropertyAnimation anim;

    QPoint mouse_pos;
    QString status;

    bool sliced;
};

#endif // CANVAS_H
