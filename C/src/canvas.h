#ifndef CANVAS_H
#define CANVAS_H

#include <QtOpenGL>
#include <QSurfaceFormat>
#include <QOpenGLShaderProgram>
#include "ModelPrint.h"

class GLMesh;
class Mesh;
class Backdrop;


class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
	explicit Canvas(const QSurfaceFormat& format, QWidget* parent=0);
    ~Canvas();

    void view_orthographic();
    void view_perspective();
    void draw_shaded();
    void draw_wireframe();
    void set_sliced(bool s) { sliced = s;}
    void draw_slice(std::vector<lineSegment> v);

public slots:
    void set_status(const QString& s);
    void clear_status();
    void load_mesh(Mesh* m, Mesh* b, bool is_reload);

protected:
	void paintGL() override;
	void initializeGL() override;
	void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    
	void set_perspective(float p);
    void set_drawMode(int mode);
    void view_anim(float v);

private:
    void draw_mesh(GLMesh* m);

    QMatrix4x4 transform_matrix() const;
    QMatrix4x4 view_matrix() const;

    QOpenGLShaderProgram mesh_shader;
    QOpenGLShaderProgram mesh_wireframe_shader;
	QOpenGLShaderProgram quad_shader;

    GLMesh* mesh;
    GLMesh* slice;
    GLMesh* bedMesh;
    Backdrop* backdrop;

    QVector3D center;
    float scale;
    float zoom;
    float tilt;
    float yaw;

    float perspective;
    int drawMode;
    Q_PROPERTY(float perspective MEMBER perspective WRITE set_perspective);
    QPropertyAnimation anim;

    QPoint mouse_pos;
    QString status;

    bool sliced;
};

#endif // CANVAS_H
