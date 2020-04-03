#include "Vector.h"
#include <cmath>

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

Vector operator/(const Vector& v, float c)
{
    Vector vec((v.x / c),(v.y / c),(v.z / c));
    return vec;
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

float calcDistance(const Vector& a, const Vector& b)
{
    return calcMagnitude(a - b);
}

float calcMagnitude(const Vector& v)
{
    return sqrtf(dotProduct(v,v));
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
}
