#include "Geometry.h"


std::ostream& operator<<(std::ostream& os, const Plane& p)
{
    os << (p.normal).x << "x + " << (p.normal).y << "y + " << (p.normal).z << "z + " << p.distance << " = 0 ";
    return os;
}


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

