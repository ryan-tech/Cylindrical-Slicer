#ifndef VEC3_H
#define VEC3_H

#include <QtOpenGL/QtOpenGL>
#include <iostream>
#include <cmath>

/*
 *  Represents an optionally-indexed vertex in space
 */
struct Vector3
{
    Vector3() {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    GLfloat x, y, z;
    GLuint i=0;

    bool operator!=(const Vector3& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }
    bool operator<(const Vector3& rhs) const
    {
        if      (x != rhs.x)    return x < rhs.x;
        else if (y != rhs.y)    return y < rhs.y;
        else if (z != rhs.z)    return z < rhs.z;
        else                    return false;
    }

    Vector3 operator+(const Vector3& a)
    {
    return Vector3((a.x + this->x),(a.y + this->y),(a.z + this->z));
    }

    Vector3 operator-(const Vector3& a)
    {
        return Vector3((a.x - this->x),(a.y - this->y),(a.z - this->z));
    }

    Vector3 operator*(float c)
    {
        return Vector3((c * this->x),(c * this->y),(c * this->z));
    }

    Vector3 operator/(float c)
    {
        return Vector3((this->x / c),(this->y / c),(this->z / c));
    }

    std::ostream& operator<<(std::ostream& os)
    {
        os << "(" << this->x << ", " << this->y << ", " << this->z << ")";
        return os;
    }

    bool operator==(const Vector3& rhs)
    {
        return ((rhs.x == this->x) && (rhs.y == this->y) && (rhs.z == this->z));
    }

    bool operator!=(const Vector3& rhs)
    {
        return !((rhs.x == this->x) && (rhs.y == this->y) && (rhs.z == this->z));
    }

    float dotProduct(const Vector3& rhs)
    {
        return ((rhs.x * this->x) + (rhs.y * this->y) + (rhs.z * this->z));
    }

    Vector3 crossProduct(const Vector3& rhs)
    {
        return Vector3(((rhs.y * this->z) - (rhs.z * this->y)), ((rhs.z * this->x) - (rhs.x * this->z)), ((rhs.x * this->y) - (rhs.y * this->x)) );
    }

};

#endif
