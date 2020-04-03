void viewTestAngles()
{
    SlicingCircle test(1.0f);
    test.setAngles((2*M_PI)/4);
    for (auto i = (test.angles).begin(); i != (test.angles).end(); ++i) {
      std::cout << *i << " ";
    }
}

void viewTestPlanes()
{
    SlicingCircle test(5.0f);
    test.setAngles((2*M_PI)/4);
    test.setPlanes((2*M_PI)/4);
    for (auto i = (test.slicingPlanes).begin(); i != (test.slicingPlanes).end(); ++i) {
      std::cout << (*i) << '\n';
    }
}

bool testFlipSegment()
{
    Point p(0,0,1);
    Point q(1,0,0);
    lineSegment original(p,q);
    flipSegment(original);
    if ((original.start == q) && (original.end == p))
    {
        return true;
    }
    return false;
}

bool testTrianglePlaneIntersection()
{
    Vector v(0,0,1);
    Plane p(v,-1.0f);
    Point a(0,0,2);
    Point b(0,2,2);
    Point c(0,0,0);
    Point testP1(0,0,1);
    Point testP2(0,1,1);
    lineSegment test(testP1,testP2);
    lineSegment result;
    p.TrianglePlaneIntersection(a, b, c, result);
    if (result ==  test)
    {
        return true;
    }
    return false;
}

bool testTrianglePlaneIntersection()
{
    Point a(1,1,0);
    Point b(1,2,0);
    Point c(2,45,0);
    Vector v(0,0,-1);
    Plane test(v,0.0f);
    Plane p;
    p.planeFromPoints(a, b, c);
    if ((p.normal == test.normal) && (p.distance == test.distance))
    {
        return true;
    }
    return false;
}

bool testCalcPointPlaneDistance()
{
    Vector v(0,0,1);
    Plane test(v,1.0f);
    Point p(0,0,0);
    float testVal = test.calcPointPlaneDistance(p);
    if (testVal == 1)
    {
        return true;
    }
    return false;
}

bool testSubSegment()
{
    Vector v(0,1,0);
    Plane testPlaneLeft(v,1.0f);
    Plane testPlaneRight(v,-1.0f);
    Point ll(0,-2,0);
    Point lr(0,2,0);
    Point testPointA(0,1,0);
    Point testPointB(0,-1,0);
    lineSegment l(ll,lr);
    lineSegment testLine(testPointA,testPointB);
    subSegment(testPlaneLeft, testPlaneRight, l);
    if (l == testLine)
    {
        return true;
    }
    return false;
}
