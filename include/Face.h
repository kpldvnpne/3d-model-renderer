#ifndef FACE_H
#define FACE_H

#include "Vector3d.h"
/**
 * @brief Class for each face of the triangular mesh
 * Each face has three vertices
 * Each vertex has position and normal
 * Vector2d for face has Index for vertex and index for normal
 * vn1.x is index of vertex and vn1.y is index of normal of that vertex
 */
class Face
{
public:
    int v0, v1, v2, n0, n1, n2;    //< Three vertices of a face along with their normal

public:
    Face();
    virtual ~Face();

    Face(int,int,int,int,int,int);
};

#endif // FACE_H
