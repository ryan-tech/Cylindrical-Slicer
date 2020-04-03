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
         return false;

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

struct SlicingCircle
{
    SlicingCircle () : radius(1.0f) {}
    SlicingCircle (const float rad) : radius(rad) {}
    //Angles are expressed in radians not degrees
    std::vector<float> angles;
    std::vector<Plane> slicingPlanes;
    std::vector<Plane> leftBoundPlane;
    std::vector<Plane> rightBoundPlane;
    float radius;

    void calcLayerRadius(float initialRadius, float layerHeight, int layer)
    {
        radius = ((layer*layerHeight)+initialRadius);
    }

    //Calculates and stores the angles
    void setAngles(float spaceBetween)
    {
        float N = ((2*M_PI*radius)/spaceBetween);;
        for (int i = 0; i < N; i++) {
            angles.push_back((float)i * (float)((2*M_PI)/N));
        }

    }

    //Calculates and stores the planes that will be use for intersections
    void setPlanes(float spaceBetween)
    {
        float x1,x2,y1,y2;
        Point a,b,c;
        Plane p, leftBound, rightBound;
        Point origin;
        Point otherOrigin(0.0f,0.0f,5.0f);

        float N = ((2*M_PI*radius)/spaceBetween);

        for (int i = 0; i < N; i++) {
            x1 = cos(angles[i]);
            y1 = sin(angles[i]);

            x2 = cos(angles[i+1]);
            y2 = sin(angles[i+1]);

            Point a(x1,y1,0.0f);
            Point b(x2,y2,0.0f);
            Point c(x2,y2,5.0f);

            p.planeFromPoints(a,b,c);
            p.distance = -radius;
            slicingPlanes.push_back(p);

            leftBound.planeFromPoints(origin,a,otherOrigin);
            leftBoundPlane.push_back(leftBound);

            rightBound.planeFromPoints(origin,b,otherOrigin);
            rightBoundPlane.push_back(rightBound);
        }
    }
};

struct Polygon
{
    std::vector<lineSegment> path;
};

struct Layers
{
    int numLayer;
    //std::vector<Triangle> triangles;
    std::vector<lineSegment> segments;
    SlicingCircle circle;

    //These polygons have not been converted for g-code
    std::vector<Polygon> catesianShapes;

    //These polygons have not been converted for g-code
    std::vector<Polygon> cylindricalShapes;
};

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

std::ostream& operator<<(std::ostream& os, const lineSegment& l)
{
    os << "(" << l.start << ", " << l.end << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Plane& p)
{
    os << (p.normal).x << "x + " << (p.normal).y << "y + " << (p.normal).z << "z + " << p.distance << " = 0 ";
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
