#ifndef VEC3_H
#define VEC3_H

#include <QtOpenGL/QtOpenGL>
#include <ostream>

/*
 *  Represents an optionally-indexed vertex in space
 */
struct Vector
{
    Vector() {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    GLfloat x, y, z;
    GLuint i=0;

    Vector operator+(const Vector& a, const Vector& b);
    Vector operator-(const Vector& a, const Vector& b);
    Vector operator*(const Vector& v, float c);
    Vector operator/(const Vector& v, float c);

    std::ostream& operator<<(std::ostream& os, const Vector& v);

    bool operator==(const Vector& a, const Vector& b);
    bool operator!=(const Vector& a, const Vector& b);

    float dotProduct(const Vector& a, const Vector& b);
    float crossProduct(const Vector& a, const Vector& b);
    float calcDistance(const Vector& a, const Vector& b);

    float calcMagnitude(const Vector& v);

    void normalize(const Vector& v);
    Vector normalized(const Vector& v);
};

#endif
