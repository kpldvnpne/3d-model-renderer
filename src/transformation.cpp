#include "Model.h"
#include<cmath>

#define PI 3.1415

void Model::rotateY(float angle)
{

    angle = angle * PI /180;
    float cosA = cos(angle);
    float sinA = sin(angle);

    Vector3d center((xmax + xmin)/2,(ymax + ymin)/2,(zmax + zmin)/2);

    float x,z;
    int i;
    for(i=0; i<vertexCount; i++)
    {
        Vector3d &v = vertexTable[i];
        v = v - center;
        z = v.z * cosA - v.x * sinA;
        x = v.z * sinA + v.x * cosA;

        v.z = z;
        v.x = x;
        v = v + center;
    }
}

void Model::rotateX(float angle)
{

    angle = angle * PI /180;
    float cosA = cos(angle);
    float sinA = sin(angle);

    Vector3d center((xmax + xmin)/2,(ymax + ymin)/2,(zmax + zmin)/2);

    float y,z;
    int i;
    for(i=0; i<vertexCount; i++)
    {
        Vector3d &v = vertexTable[i];
        v = v - center;
        y = v.y * cosA - v.z * sinA;
        z = v.y * sinA + v.z * cosA;

        v.y = y;
        v.z = z;
        v = v + center;
    }
}
void Model::rotateZ(float angle)
{

    angle = angle * PI /180;
    float cosA = cos(angle);
    float sinA = sin(angle);

    Vector3d center((xmax + xmin)/2,(ymax + ymin)/2,(zmax + zmin)/2);

    float x,y;
    int i;
    for(i=0; i<vertexCount; i++)
    {
        Vector3d &v = vertexTable[i];
        v = v - center;
        x = v.x * cosA - v.y * sinA;
        y = v.x * sinA + v.y * cosA;

        v.x = x;
        v.y = y;
        v = v + center;
    }
}

void Model::scale(float s)
{
    Vector3d center((xmax + xmin)/2,(ymax + ymin)/2,(zmax + zmin)/2);
    for(auto &v : vertexTable) {
        v = v - center;
        v = v.multiply(s);
        v = v + center;
    }
}
