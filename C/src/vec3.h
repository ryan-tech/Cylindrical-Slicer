//

#ifndef VEC3_H
#define VEC3_H

#include <QtOpenGL/QtOpenGL>

struct Vector3
{
    Vector3() {}
    Vector3(float x, float y, float z) : x_val(x), y_val(y), z_val(z) {}

    GLfloat x_val, y_val, z_val;
    GLuint i=0;

    bool operator!=(const Vector3& other) const
    {
        return x_val != other.x_val || y_val != other.y_val || z_val != other.z_val;
    }
    bool operator<(const Vector3& rhs) const
    {
        if      (x_val != rhs.x_val)    return x_val < rhs.x_val;
        else if (y_val != rhs.y_val)    return y_val < rhs.y_val;
        else if (z_val != rhs.z_val)    return z_val < rhs.z_val;
        else                    return false;
    }
};

#endif