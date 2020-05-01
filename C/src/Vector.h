#ifndef VEC3_H
#define VEC3_H

#include <QtOpenGL/QtOpenGL>
#include <ostream>

/*
 *  Represents an optionally-indexed vertex in space
 */
struct Vector
{
    Vector() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

    GLfloat x, y, z;
    GLuint i=0;

    Vector& operator=(const Vector& v)
    {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
    }

    bool operator<(const Vector& rhs) const
    {
        if      (x != rhs.x)    return x < rhs.x;
        else if (y != rhs.y)    return y < rhs.y;
        else if (z != rhs.z)    return z < rhs.z;
        else                    return false;
    }


};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& v, float c);
Vector operator/(const Vector& v, float c);
Vector operator*(const Vector& l, const Vector& r);
Vector operator/(const Vector& l, const Vector& r);

std::ostream& operator<<(std::ostream& os, const Vector& v);

bool operator==(const Vector& a, const Vector& b);
bool operator!=(const Vector& a, const Vector& b);

float dotProduct(const Vector& a, const Vector& b);
Vector crossProduct(const Vector& a, const Vector& b);
float calcDistance(const Vector& a, const Vector& b);

float calcMagnitude(const Vector& v);

void normalize(Vector& v);
Vector normalized(const Vector& v);
/*
Vector operator+(const Vector& a, const Vector& b)
{
    Vector c((a.x + b.x),(a.y + b.y),(a.z + b.z));
    return c;
}

Vector operator-(const Vector& a, const Vector& b)
{
    Vector c((a.x - b.x),(a.y - b.y),(a.z - b.z));
    return c;
}

Vector operator*(const Vector& v, float c)
{
    Vector vec((c * v.x),(c * v.y),(c * v.z));
    return vec;
}

Vector operator*(const Vector& l, const Vector& r)
{
    Vector result(l.x * r.x, l.y * r.y, l.z * r.z);
    return result;
}

Vector operator/(const Vector& v, float c)
{
    Vector vec((v.x / c),(v.y / c),(v.z / c));
    return vec;
}

Vector operator/(const Vector& l, const Vector& r)
{
    Vector result(l.x / r.x, l.y / r.y, l.z / r.z);
    return result;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

bool operator==(const Vector& a, const Vector& b)
{
    return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
}

bool operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}

float dotProduct(const Vector& a, const Vector& b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

Vector crossProduct(const Vector& a, const Vector& b)
{
    Vector result;
    result.x = (a.y * b.z) - (a.z * b.y);
    result.y = (a.z * b.x) - (a.x * b.z);
    result.z = (a.x * b.y) - (a.y * b.x);
    return result;
}

float calcMagnitude(const Vector& v)
{
    return sqrtf(dotProduct(v,v));
}

float calcDistance(const Vector& a, const Vector& b)
{
    return calcMagnitude(a - b);
}

void normalize(Vector& v)
{
    v = v * (1.0f / calcMagnitude(v));
}

Vector normalized(const Vector& v)
{
    Vector temp;
    temp = v * (1.0f / calcMagnitude(v));
    return temp;
}*/



#endif
