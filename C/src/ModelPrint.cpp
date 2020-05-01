#include "ModelPrint.h"
//#include printParameters.h

//A polygon does not represent a whole layer only part of it
//Layers can have one or more polygons
struct Polygon
{
    std::vector<Point> path;

    void convertCartToCyl(Polygon& cartesian, float radius)
    {
      int size = cartesian.path.size();
      Point converted[size];
      int it = 0;
        for (auto i = (cartesian.path).begin(); i != (cartesian.path).end(); ++i)
        {
            converted[it].x = i->z;
            converted[it].y = radius*(calcTheta(i->x,i->y,radius));
            converted[it].z = radius;
            path.push_back(converted[it]);
            it++;
        }
    }
};

struct Layer
{
    //This variable defines which layer this is (i.e. first, second, etc)
    //Note that there is no layer 0 because that is the print bed
    int numLayer;
    float layerRadius;
    float layerHeight;
    float filamentThickness;
    SlicingCircle circle;

    //segments without conversion for gcode
    std::vector<lineSegment> cartesianSegments;
    //Converted segments
    std::vector<lineSegment> cylindricalSegments;

    //These polygons have not been converted for g-code
    std::vector<Polygon> cartesianShapes;

    //These polygons have been converted for g-code
    std::vector<Polygon> cylindricalShapes;

    Layer() : numLayer(1) {}
    Layer(const int num) : numLayer(num) {}
    Layer(const int num, const float rad) : numLayer(num), circle(rad) {}
    Layer(const int num, const float rad, const float space) : numLayer(num), circle(rad,space) {}
    Layer(const int num, const float rad, const float space, const float height) : numLayer(num), layerHeight(height), circle(rad,space) {}

    void slicing(std::vector<Triangle>& triangles)
    {
        circle.radius = calcLayerRadius(circle.radius, layerHeight, numLayer);
        layerRadius = circle.radius;
        circle.setPlanes();
        Point zeroP(0.0f,0.0f,0.0f);
        lineSegment zero(zeroP,zeroP);
        int maxNumLineSeg = (triangles.size() * (circle.slicingPlanes).size());
        lineSegment lineSeg[maxNumLineSeg];
        int it = 0;
        auto LBIterator = (circle.leftBoundPlane).begin();
        auto RBIterator = (circle.rightBoundPlane).begin();
        for (auto SPIterator = (circle.slicingPlanes).begin(); SPIterator != (circle.slicingPlanes).end(); ++SPIterator)
        {
            for (auto TriIterator = (triangles).begin(); TriIterator != (triangles).end(); ++TriIterator)
            {
                (*SPIterator).TrianglePlaneIntersection(*TriIterator, lineSeg[it]);
                if (lineSeg[it] != zero)
                {
                    subSegment(*LBIterator, *RBIterator, lineSeg[it]);
                    cartesianSegments.push_back(lineSeg[it]);
                it++;
                }
            }

            ++LBIterator;
            ++RBIterator;
        }
    }
    bool buildPolygons()
    {
        int maxNumShapes = cartesianSegments.size();
        Polygon shapes[maxNumShapes];
        Point outPoint[maxNumShapes];
        bool used[maxNumShapes];
        for (int it = 0; it <= maxNumShapes; it++)
        {used[it] = false;}
        int firstUsedCount = 0;
        int secondUsedCount = 0;
        int count = 0;
        int k = 0;

        for (auto polygonStart = cartesianSegments.begin(); polygonStart != cartesianSegments.end(); ++polygonStart)
        {
            if (used[firstUsedCount] == false)
            {
                shapes[k].path.push_back(polygonStart->start);
                shapes[k].path.push_back(polygonStart->end);
                used[firstUsedCount] = true;

                for (auto i = cartesianSegments.begin(); i != cartesianSegments.end(); ++i)
                {
                    if ((used[secondUsedCount] == false) && (isMatch(*i, shapes[k].path.back(), outPoint[count])))
                    {
                        shapes[k].path.push_back(outPoint[count]);
                        used[secondUsedCount] = true;
                        count++;

                        if (shapes[k].path.front() == outPoint[count])
                        {
                            cartesianShapes.push_back(shapes[k]);
                            k++;
                        }
                        i = cartesianSegments.begin();
                        secondUsedCount = 0;
                    }

                    secondUsedCount++;
                }
                secondUsedCount = 0;
            }
            if (firstUsedCount == maxNumShapes-1)
            {
                cartesianShapes.push_back(shapes[k]);
                return true;
            }
            firstUsedCount++;
        }
        return false;
    }

    void convertPolygonsListToCyl()
    {
        int arraySize = cartesianShapes.size();
        Polygon dummyShape[cartesianShapes.size()];
        int it = 0;
        for (auto i = cartesianShapes.begin(); i != cartesianShapes.end(); ++i)
        {

            dummyShape[it].convertCartToCyl(*i, layerRadius);
            cylindricalShapes.push_back(dummyShape[it]);
            it++;
            //for (auto n = (dummyShape[0].path).begin(); n != (dummyShape[0].path).end(); ++n) { std::cout << "draw (" <<n->x<<','<<n->y << ") node[] {$\ bullet$};" << '\n'; }
        }
    }
};

struct ModelPrint
{
    float m_filament;
    float m_extruderTemp;
    float m_bedTemp;
    float m_layerHeight;
    float m_firstLayerHeight;
    float m_zOffset;
    float m_travelSpeed;
    float m_firstLayerSpeed;
    float m_printSpeed;
    float m_printBedRadius;
    std::string outputFileName;

    std::vector<Triangle> ModelTriangles;
    std::vector<Layer> PrintSlices;

    ModelPrint() : m_printBedRadius(1.0f), m_filament(0.1f), m_layerHeight(0.01f), outputFileName("default") {}

    ModelPrint(const float rad, const float space, const float height, std::string name)
    : m_printBedRadius(rad), m_filament(space), m_layerHeight(height), outputFileName(name) {}

    void convertMeshToTriangles(const Mesh& original)
    {
        Triangle dummyTriangle;
        std::vector<GLfloat> copyVertices = original.get_vertices();
        std::vector<GLuint> copyIndices = original.get_indices();
        auto vertIt = copyVertices.begin();
        for (auto indexIt = copyIndices.begin(); indexIt != copyIndices.end(); indexIt+=9)
        {
            dummyTriangle.a.x = *vertIt;
            vertIt++;
            dummyTriangle.a.y = *vertIt;
            vertIt++;
            dummyTriangle.a.x = *vertIt;
            vertIt++;

            dummyTriangle.b.x = *vertIt;
            vertIt++;
            dummyTriangle.b.y = *vertIt;
            vertIt++;
            dummyTriangle.b.x = *vertIt;
            vertIt++;

            dummyTriangle.c.x = *vertIt;
            vertIt++;
            dummyTriangle.c.y = *vertIt;
            vertIt++;
            dummyTriangle.c.x = *vertIt;
            vertIt++;
            ModelTriangles.push_back(dummyTriangle);
        }
    }

    void buildPrint()
    {
        int i = 1;
        bool delimiter = false;
        while (delimiter == false)
        {
            Layer dummySlice(i, m_printBedRadius, m_filament, m_layerHeight);

            dummySlice.slicing(ModelTriangles);

            if (dummySlice.cartesianSegments.size() == 0)
            {
                delimiter = true;
            }

            dummySlice.buildPolygons();
            dummySlice.convertPolygonsListToCyl();
            PrintSlices.push_back(dummySlice);
            i++;
        }
    }

    void exportGcode()
    {
        std::ofstream fout;
        std::string completeOutputFileName = (outputFileName + ".txt");
        fout.open(completeOutputFileName);
        //Turn off print cooling fan
        fout << "M107" << '\n';
        //Set target temperature
        fout << "M104" << ' ' << 'S' << m_extruderTemp << '\n';
        //Auto-home
        fout << "G28" << '\n';
        //Lift nozzle
        fout << "G1 Z5 F5000" << '\n';
        //Wait for hotend temp (wait for temp to be reached)
        fout << "M109" << ' ' << 'S' << m_extruderTemp << '\n';
        //Set units to milimeters
        fout << "G21" << '\n';
        //Absolute positioning (use absolute coordinates)
        fout << "G90" << '\n';
        //E absolute: E axis is in absolute mode independent of the other axes (absolute distances for extrusion)
        fout << "M82" << '\n';
        //Set the current position to the values secified
        //Possibly at the beginning of every interation?
        fout << "G92" << ' ' << "E0" << '\n';

        for (auto i = PrintSlices.begin(); i != PrintSlices.end(); ++i)
        {
            fout << "G92 E0" << '\n';
            for (auto j = (i->cylindricalShapes).begin(); j != (i->cylindricalShapes).end(); ++j)
            {
                for (auto k = (j->path).begin(); k != (j->path).end(); ++k)
                {
                    fout << "G1 X" << k->x << " Y" << k->y << " E" << calcDistance(*k,*(k+1)) << '\n';
                }
            }
        }

        //Set the current position to the values secified
        //Possibly at the beginningor end of every interation?
        fout << "G92" << ' ' << "E0" << '\n';
        //Turn off temperature
        fout << "M104" << ' ' << "S0" << '\n';
        //Home x axis
        fout << "G28" << "X0" << '\n';
        //Disable motor
        fout << "M84" << '\n';
        fout.close();
    }
};


