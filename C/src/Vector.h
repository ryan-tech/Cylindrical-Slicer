#ifndef VEC3_H
#define VEC3_H

//#include <QtOpenGL/QtOpenGL>
#include <ostream>

/*
 *  Represents an optionally-indexed vertex in space
 */
struct Vector
{
    Vector() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

    float x, y, z;
    int i=0;

    Vector& operator=(const Vector& v)
    {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
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

#endif
