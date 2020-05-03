#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Background : protected QOpenGLFunctions
{
public:
    Background();
    void draw();
private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
};

#endif
