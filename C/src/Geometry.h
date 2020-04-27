#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Vector.h"
#include "math.h"
#include <vector>
//#include printParameters.h

typedef Vector Point;

struct lineSegment
{
    Point start;
    Point end;

    lineSegment() {} //Default constructor
    lineSegment(const Point& A, const Point& B) : start(A), end(B) { } //Parameterized Constructor

    void add(Point p)
    {
      Point zeroPoint;
        if (start == zeroPoint)
        {
            start = p;
        }
        else
        {
            end = p;
        }
    }
};

bool isMatch(lineSegment& line, Point inputPoint, Point& outputPoint){
    float epsilon = 0.0000001;
    if ((line.start == inputPoint) || (calcDistance(line.start,inputPoint) <= epsilon)) {
        outputPoint = line.end;
        return true;
    }
    if ((line.end == inputPoint) || (calcDistance(line.end,inputPoint) <= epsilon)) {
        outputPoint = line.start;
        return true;
    }
    return false;
}

struct Triangle
{
    Point a;
	Point b;
	Point c;

    Triangle() { }
	Triangle(const Point& p1, const Point& p2, const Point& p3) : a(p1), b(p2), c(p3) { }
};

struct Plane
{
	Vector normal;
	float distance;

	Plane() : normal(1, 0, 0), distance(0.0f) { }
	Plane(const Vector& n, float d) : normal(n), distance(d) { }

    float DistFromPlane(const Vector& v)
    {
        return dotProduct(normal,v) + distance;
    }

    bool GetSegmentPlaneIntersection(Vector p1, Vector p2, Vector& outP)
    {
        float d1 = DistFromPlane(p1);
        float d2 = DistFromPlane(p2);

        if (d1*d2 > 0)  // points on the same side of plane
        {
            return false;
        }

        float t = d1 / (d1 - d2); // 'time' of intersection point on the segment
        Vector p3(p2 - p1);
        outP = p1 + (p3 * t);

        return true;
    }

    void TrianglePlaneIntersection(Vector triA, Vector triB, Vector triC, lineSegment& outSegTips)
    {
        Vector IntersectionPoint;
        if( GetSegmentPlaneIntersection( triA, triB, IntersectionPoint))
        {
            outSegTips.add(IntersectionPoint);
        }
        if( GetSegmentPlaneIntersection( triB, triC, IntersectionPoint))
        {
            outSegTips.add(IntersectionPoint);
        }
        if( GetSegmentPlaneIntersection( triC, triA, IntersectionPoint))
        {
            outSegTips.add(IntersectionPoint);
        }
    }

    void TrianglePlaneIntersection(Triangle Tri, lineSegment& outSegTips)
    {
        TrianglePlaneIntersection(Tri.a, Tri.b, Tri.c, outSegTips);
    }

    void planeFromPoints(Point a, Point b, Point c)
    {
        normal = normalized(crossProduct((b-a),(c-b)));
    }

    float calcPointPlaneDistance(const Point& p)
    {
        float d = fabs(dotProduct(normal,p) + distance);
        float e = calcMagnitude(normal);
        return (d/e);
    }
};

std::ostream& operator<<(std::ostream& os, const Plane& p)
{
    os << (p.normal).x << "x + " << (p.normal).y << "y + " << (p.normal).z << "z + " << p.distance << " = 0 ";
    return os;
}

struct SlicingCircle
{
    SlicingCircle () : radius(1.0f), filamentThickness(1.0f){}
    SlicingCircle (const float rad) : radius(rad), filamentThickness(1.0f){}
    SlicingCircle (const float rad, const float spaceBetween) : radius(rad),filamentThickness(spaceBetween) {}
    //Angles are expressed in radians not degrees
    std::vector<float> angles;
    std::vector<Plane> slicingPlanes;
    std::vector<Plane> leftBoundPlane;
    std::vector<Plane> rightBoundPlane;
    float radius;
    float filamentThickness;

    //Calculates and stores the angles
    void setAngles()
    {
        float N = ((2*M_PI*radius)/filamentThickness);;
        for (int i = 0; i < N; i++) {
            angles.push_back((float)i * (float)((2*M_PI)/N));
        }

    }

    //Calculates and stores the planes that will be use for intersections
    void setPlanes()
    {
        setAngles();
        Plane p, leftBound, rightBound;
        Point origin;
        Point otherOrigin(0.0f,0.0f,5.0f);

        float N = ((2*M_PI*radius)/filamentThickness);

        for (int i = 0; i < N; i++) {
            float x1 = cos(angles[i]);
            float y1 = sin(angles[i]);

            float x2 = cos(angles[i+1]);
            float y2 = sin(angles[i+1]);

            Point a(x1,y1,0.0f);
            Point b(x2,y2,0.0f);
            Point rb(-x2,-y2,0.0f);
            Point c(x2,y2,5.0f);

            p.planeFromPoints(a,b,c);
            p.distance = radius;
            slicingPlanes.push_back(p);

            leftBound.planeFromPoints(rb,origin,otherOrigin);
            leftBound.distance = 0.0f;
            leftBoundPlane.push_back(leftBound);

            rightBound.planeFromPoints(a,origin,otherOrigin);
            rightBound.distance = 0.0f;
            rightBoundPlane.push_back(rightBound);
        }
    }
};

float calcLayerRadius(float initialRadius, float layerHeight, int layer)
{
    return (((float)layer*layerHeight)+initialRadius);
}

float calcTheta(float x, float y, float r)
{
    float d = sqrtf(pow((x - r), 2) + pow(y, 2));
    float theta = acos(1-((pow(d,2))/(2*pow(r,2))));
    if (y >= 0)
    {
        return theta;
    }
    else if (y < 0 && x >= 0){
      return (theta + ((3*M_PI)/2));
    }
    else
    {
        return (theta + M_PI);
    }
}

void flipSegment(lineSegment& l)
{
    lineSegment temp(l.end,l.start);
    l.start = temp.start;
    l.end = temp.end;
}

bool operator==(lineSegment a, lineSegment b)
{
    if ((a.start == b.start) && (a.end == b.end))
    {
        return true;
    }
    if ((a.start == b.end) && (a.end == b.start))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(lineSegment a, lineSegment b)
{
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const lineSegment& l)
{
    os << "(" << l.start << ", " << l.end << ")";
    return os;
}

void subSegment(Plane& left, Plane& right, lineSegment& sublineSegment)
{
    Vector IntersectionPointLeft;
    Vector IntersectionPointRight;
    lineSegment temp;
    bool intersectsLeft = left.GetSegmentPlaneIntersection(sublineSegment.start, sublineSegment.end, IntersectionPointLeft);
    bool intersectsRight = right.GetSegmentPlaneIntersection(sublineSegment.start, sublineSegment.end, IntersectionPointRight);
    if(intersectsLeft && intersectsRight)
    {
         sublineSegment.start = IntersectionPointLeft;
         sublineSegment.end = IntersectionPointRight;
    }
    if(intersectsLeft)
    {
         if (right.calcPointPlaneDistance(sublineSegment.start) >= right.calcPointPlaneDistance(sublineSegment.end))
         {
             sublineSegment.end = IntersectionPointLeft;
         }
         else
         {
             sublineSegment.start = IntersectionPointLeft;
         }
    }

    if(intersectsRight)
    {

        if (left.calcPointPlaneDistance(sublineSegment.start) >= left.calcPointPlaneDistance(sublineSegment.end))
        {
            sublineSegment.start = IntersectionPointRight;
        }
        else
        {
            sublineSegment.end = IntersectionPointRight;
        }
    }

}

#endif
