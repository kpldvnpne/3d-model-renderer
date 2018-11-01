#ifndef MODEL_H
#define MODEL_H

#include "Face.h"
#include "Vector3d.h"

#include <vector>
#include <array>
#include "SFML/Graphics.hpp"

const int windowX = 1024, windowY = 586;
const float INF = 1.0e10;

/**
 * @brief Class Model is everything for a model to load and transform
 * It has functions for loading obj file, construct tables, transform and stuffs
 */
class Model
{
private:
    std::vector<Vector3d> vertexTable;
    std::vector<Vector3d> normalTable;
    std::vector<Face> faceTable;
    std::vector<Vector3d> projectionTable;

    int vertexCount, faceCount, normalCount;
    float xmax, ymax, zmax, xmin, ymin, zmin;

    // values calculated in world to view transform
    float h, dp, val1, val2, val3; //< calculated in setViewCoordinate and used in viewTransform
    Vector3d u, v, n; //< unit vectors uvn for view plane

public:
//attributes for defining view coordinate
    Vector3d camera;
    Vector3d lookAt;
    Vector3d viewUp;
    float Zvp, Zprp; //< Z-VIEW POINT and Z-PROJECTION REFERENCE POINT
    float scaleFactor; //< to scale the model to fit in window


private:
//These are the attributes and tables we need for Z-BUFFER
    float *zBuffer = new float[windowY * windowX];
    sf::Color *colorBuffer = new sf::Color[windowY * windowX];
    sf::Vertex vertex; //< to draw vertex -- used in drawModel() in renderer.cpp

public:
//These are the attributes required for ILLUMINATION AND SHADING
    Vector3d lightSource;
    sf::Color color;
    sf::Color bgcolor;
    float Iamb; //< ambient light intensity
    float Ipoint; //< point source intensity
    float Ka, Kd, Ks; //< reflection coefficients respectively for ambient, diffused and specular reflection
    float ns; //< specular reflection parameter


public:
    Model();
    virtual ~Model() {delete zBuffer; delete colorBuffer;}

    bool loadModel(const char *);

public:
//-- Methods for view coordinate --//
    void rotateX(float);    //< defined in transformation.cpp
    void rotateY(float);
    void rotateZ(float);
    void scale(float);
    //defined in viewTransform.cpp
    void normalize(); //< to  normalize the vertex
    void autoFocus();
    void setViewCoordinate();
    void viewTransform();
    Vector3d viewTransform(Vector3d &);
    // Vector3d project(const Vector3d &);
    void project();
    void toView(Vector3d &);

    void printData();


public:
//And these are the methods for the RASTERIZATION -- Z-BUFFER AND SHADING
//these are defined in rasterization.cpp
    void initializeBuffers();
    float edgeFunction(const Vector3d &, const Vector3d &, const int&, const int&);
//And these are in renderer.cpp
    void renderModel();
    void render(int,int);
    void drawModel(sf::RenderWindow &);

};



//-----------To define the 2D boundry of triangle to reduce point check-----------//
struct BoundingBox
{
    int xMin,xMax;
    int yMin,yMax;
};

/**
 * This returns the rectangular boundry of the triangle in 2D
 */
BoundingBox getBoundry(const Vector3d &v0, const Vector3d &v1, const Vector3d &v2);

#endif // MODEL_H
