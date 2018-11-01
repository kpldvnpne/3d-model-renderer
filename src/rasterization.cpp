//This file contains all the functions necessary for the rasterization of triangle
#include "Model.h"

#include<algorithm>


/**
 * @brief This function initializes Z Buffer and Color Buffer
 */
void Model::initializeBuffers()
{
    int i,j;
    for(i = 0; i < windowY; i++)
        for(j = 0; j < windowX; j++)
        {
            zBuffer[i*windowX + j] = -INF;
            colorBuffer[i*windowX + j] = bgcolor;
        }
}


/**
 * @brief This function checks if a point P(x,y) in screen coordinate or say projected coordinate lies inside or ourside
 * the edge.
 * This is actually an area given by cross product of vector V0V1 and V0P
 * @param End points of an edge and point to check P(x,y)
 * @return Area given by cross product of V0V1 and V0P vectors
 */
float Model::edgeFunction(const Vector3d &V0, const Vector3d &V1, const int &Px, const int &Py)
{
    return (Px - V0.x) * (V1.y - V0.y) - (Py - V0.y) * (V1.x - V0.x);
}

/**
 * @brief This function calculates the Z-depth of P(x,y)
 */


/**
 * @brief This returns the rectangular boundry of the triangle in 2D
 */
BoundingBox getBoundry(const Vector3d &v0, const Vector3d &v1, const Vector3d &v2)
{
    BoundingBox bbox;

    float xArr[] = {v0.x,v1.x,v2.x};
    float yArr[] = {v0.y,v1.y,v2.y};

    std::sort(xArr, xArr + 3);
    std::sort(yArr, yArr + 3);

    bbox.xMin = xArr[0]; bbox.xMax = xArr[2];
    bbox.yMin = yArr[0]; bbox.yMax = yArr[2];

    return bbox;
}
