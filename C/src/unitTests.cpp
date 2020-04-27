void viewTestAngles()
{
    SlicingCircle test(5.0f, 4.0f);
    test.setAngles();
    for (auto i = (test.angles).begin(); i != (test.angles).end(); ++i) {
      std::cout << *i << '\n';
    }
}

void viewTestPlanes()
{
    SlicingCircle test(1.0f, 0.01f);
    test.setAngles();
    test.setPlanes();
    auto i = (test.slicingPlanes).begin();
    auto j = (test.leftBoundPlane).begin();
    auto k = (test.rightBoundPlane).begin();
    std::cout << "Slice planes:" << '\n';
    for (int n = 0; n < 25 ; ++n) {
        std::cout << (j->normal) << '\n';
        std::cout << (i->normal) << '\n';
        std::cout << (k->normal) << '\n'<< '\n';
        ++i;
        ++j;
        ++k;
    }
}

bool SliceOutputTestView()
{
    Point a(5.0f,5.0f,5.0f);
    Point b(6.0f,5.0f,5.0f);
    Point c(5.0f,6.0f,5.0f);
    Point d(5.0f,5.0f,6.0f);

    Triangle T1(a,b,c);
    Triangle T2(a,b,d);
    Triangle T3(a,c,d);
    Triangle T4(b,c,d);

    std::vector<Triangle> test;

    test.push_back(T1);
    test.push_back(T2);
    test.push_back(T3);
    test.push_back(T4);

    Layer layerTest(3, 5.0f, 0.1f,0.02f);
    layerTest.slicing(test);

    for (auto i = (layerTest.catesianSegments).begin(); i != (layerTest.catesianSegments).end(); ++i)
    {
        std::cout << *i << '\n';
    }
    return true;
}

void buildPolygonsTestFunction(std::vector<lineSegment>& lines)
{
    int maxNumShapes = lines.size();
    Polygon shapes[maxNumShapes];
    int k = 0;
    int counter = 0;
    while (counter != maxNumShapes)
    {
        auto lineIterator = lines.begin();
        shapes[k].path.push_back(lineIterator->start);
        shapes[k].path.push_back(lineIterator->end);
        lines.erase(lineIterator);
        counter++;

        while (shapes[k].path.back() != shapes[k].path.front())
        {
            for (auto i = lines.begin(); i != lines.end(); ++i)
            {
                if (shapes[k].path.back() == i->start)
                {
                    shapes[k].path.push_back(i->end);
                    lines.erase(i);
                    counter++;
                    break;
                }
                if (shapes[k].path.back() == i->end)
                {
                    shapes[k].path.push_back(i->start);
                    lines.erase(i);
                    counter++;
                    break;
                }
            }
        }
        k++;
    }
    for (auto n = shapes[0].path.begin(); n != shapes[0].path.end(); ++n) {
        std::cout << *n << '\n';
    }
}

bool buildPolygonsTestView()
{
    Point a(1.0f,0.0f,0.0f);
    Point b(0.0f,1.0f,0.0f);
    Point c(0.0f,0.0f,1.0f);

    lineSegment l1(a,b);
    lineSegment l2(c,b);
    lineSegment l3(a,c);

    std::vector<lineSegment> linesegs;

    linesegs.push_back(l1);
    linesegs.push_back(l2);
    linesegs.push_back(l3);

    buildPolygonsTestFunction(linesegs);
    return true;
}

void convertPolygonsTestFunction(std::vector<lineSegment>& lines, float radius)
{
    int maxNumShapes = lines.size();
    Polygon shapes[maxNumShapes];
    Polygon convertedShapes[maxNumShapes];
    int k = 0;
    int counter = 0;
    while (counter != maxNumShapes)
    {
        auto lineIterator = lines.begin();
        shapes[k].path.push_back(lineIterator->start);
        shapes[k].path.push_back(lineIterator->end);
        lines.erase(lineIterator);
        counter++;

        while (shapes[k].path.back() != shapes[k].path.front())
        {
            for (auto i = lines.begin(); i != lines.end(); ++i)
            {
                if (shapes[k].path.back() == i->start)
                {
                    shapes[k].path.push_back(i->end);
                    lines.erase(i);
                    counter++;
                    break;
                }
                if (shapes[k].path.back() == i->end)
                {
                    shapes[k].path.push_back(i->start);
                    lines.erase(i);
                    counter++;
                    break;
                }
            }
        }
        convertedShapes[k].convertCartToCyl(shapes[k], radius);
        k++;
    }
    std::cout <<'\n';
    for (auto n = convertedShapes[0].path.begin(); n != convertedShapes[0].path.end(); ++n) {
        std::cout << *n << '\n';
    }
}

bool convertPolygonsTestView()
{
    float oneOverRootTwo = (1/sqrtf(2));
    Point a(1.0f,0.0f,0.0f);
    Point b(oneOverRootTwo,oneOverRootTwo,0.0f);
    Point c(0.0f,1.0f,0.0f);
    Point d(-oneOverRootTwo,oneOverRootTwo,0.0f);
    Point e(-1.0f,0.0f,0.0f);
    Point f(-oneOverRootTwo,-oneOverRootTwo,0.0f);
    Point g(0.0f,-1.0f,0.0f);
    Point h(oneOverRootTwo,-oneOverRootTwo,0.0f);

    lineSegment l1(a,b);
    lineSegment l2(c,b);
    lineSegment l3(d,c);
    lineSegment l4(e,d);
    lineSegment l5(e,f);
    lineSegment l6(f,g);
    lineSegment l7(h,g);
    lineSegment l8(a,h);

    std::vector<lineSegment> linesegs;

    linesegs.push_back(l1);
    linesegs.push_back(l2);
    linesegs.push_back(l3);
    linesegs.push_back(l4);
    linesegs.push_back(l5);
    linesegs.push_back(l6);
    linesegs.push_back(l7);
    linesegs.push_back(l8);

    convertPolygonsTestFunction(linesegs,1.0f);
    return true;
}

bool layerTest()
{
    Point a(5.0f,5.0f,5.0f);
    Point b(6.0f,5.0f,5.0f);
    Point c(5.0f,6.0f,5.0f);
    Point d(5.0f,5.0f,6.0f);

    Triangle T1(a,b,c);
    Triangle T2(a,b,d);
    Triangle T3(a,c,d);
    Triangle T4(b,c,d);

    std::vector<Triangle> test;

    test.push_back(T1);
    test.push_back(T2);
    test.push_back(T3);
    test.push_back(T4);

    bool polygonTest;

    Layer layerTest(3, 5.0f, 0.1f,0.02f);
    layerTest.slicing(test);
    polygonTest = layerTest.buildPolygons();
    layerTest.convertPolygonsListToCyl();


    return true;
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
