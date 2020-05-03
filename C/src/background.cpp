#include "background.h"

Background::Background()
{
    initializeOpenGLFunctions();

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/gl_files/quad.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/gl_files/quad.frag");
    shaderProgram.link();

    float vbuf[] = {
        -1, -1, 0.00, 0.10, 0.15,
        -1,  1, 0.03, 0.21, 0.26,
         1, -1, 0.00, 0.12, 0.18,
         1,  1, 0.06, 0.26, 0.30};

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vbuf, sizeof(vbuf));
    vertexBuffer.release();
}

void Background::draw()
{
    shaderProgram.bind();
    vertexBuffer.bind();

    const GLuint vertex_pos = shaderProgram.attributeLocation("vertex_position");
    const GLuint vertex_color = shaderProgram.attributeLocation("vertex_color");

    glEnableVertexAttribArray(vertex_pos);
    glEnableVertexAttribArray(vertex_color);

    glVertexAttribPointer(vertex_pos, 2, GL_FLOAT, false,
                          5 * sizeof(GLfloat), 0);
    glVertexAttribPointer(vertex_color, 3, GL_FLOAT, false,
                          5 * sizeof(GLfloat),
                          (GLvoid*)(2 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

    vertexBuffer.release();
    shaderProgram.release();
}
