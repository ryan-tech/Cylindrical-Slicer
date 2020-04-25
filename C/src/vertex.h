#ifndef VEC3_H
#define VEC3_H

#include <QtOpenGL/QtOpenGL>
#include <cmath>

/*
 *  Represents an optionally-indexed vertex in space
 */
struct Vertex
{
    Vertex() {}
    Vertex(float x, float y, float z) : x(x), y(y), z(z) {}

    GLfloat x, y, z;
    GLuint i=0;

    bool operator!=(const Vertex& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }
    bool operator<(const Vertex& rhs) const
    {
        if      (x != rhs.x)    return x < rhs.x;
        else if (y != rhs.y)    return y < rhs.y;
        else if (z != rhs.z)    return z < rhs.z;
        else                    return false;
    }

    Vertex operator*(float c)
    {
        return Vertex((c * this->x),(c * this->y),(c * this->z));
    }

    float dotProduct(const Vertex& rhs)
    {
        return ((rhs.x * this->x) + (rhs.y * this->y) + (rhs.z * this->z));
    }

    float calcMagnitude(const Vertex& rhs)
    {
        return sqrtf(dotProduct(rhs));
    }

    Vertex normalize(Vertex& rhs)
    {
        Vertex n;
        n = rhs * (1.0f / calcMagnitude(rhs));
        return n;
    }

};

#endif
