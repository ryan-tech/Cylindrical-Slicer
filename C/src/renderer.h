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

// This class uses Qt's openGL functions to utilize openGL inside a Qt Widget
class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    //Constructor
	explicit Renderer(const QSurfaceFormat& format, QWidget* parent=0);
    //Destructor
    ~Renderer();

    // This function modifies the QPropertyAnim variable to remove the angled viewing perspective from the viewing frustrum.
    void orthographic_view();

    // This function disables orthographic_view and is the default viewing mode.
    void perspective_view();

    // This function sets the shaders to those that render the object with a solid color
    void render_shaded_shader();

    // This function sets the shaders to those that render the object with a mesh wireframe
    void render_wireframe_shader();

    // This function sets the variable sliced to indicate that the object has been sliced
    void set_sliced(bool s) { sliced = s;}

    // This function renders the slice given in the lineSegment Vector v
    void draw_slice(std::vector<lineSegment> v);

    // This function indicates which slice is currently selected from the qtSpinBox object from the gui
    void set_slice(std::vector<lineSegment> v);

public slots:
    void setStatus(const QString& s);
    void clearStatus();
    void load_mesh(Mesh* m, Mesh* b, bool is_reload);

protected:

    // Mouse events : Implements mouse controls for the gui
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    // Set function to update the drawMode variable
    void setDrawMode(int mode);
    // Set function to set the anim variable
    void set_anim(float v);
    // Set function to set the perspective variable
    void setPerspective(float p);

    // Initializes OpenGL
    void initializeGL() override;
    // Initializes the background and draws the meshes
	void paintGL() override;
	// Resizes the render screen with the window
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
