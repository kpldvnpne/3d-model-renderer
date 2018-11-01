#ifndef VECTOR3D_H
#define VECTOR3D_H

#include<iostream>

/**
 * @brief Vector3d - class to represent packet of three values
 * Actually it is array of size 3
 * Values should be float
 * Created to represent x,y,z param of vertex, and v1,v2,v3 of face
 * Has functions for real 3D vectors - unitVector(), crossProduct()
 */
class Vector3d
{
public:
    float x,y,z;

public:
    Vector3d() {}
    virtual ~Vector3d() {}
    Vector3d(float a, float b, float c): x(a), y(b), z(c) {}

    Vector3d(const Vector3d &A)
    {x = A.x; y = A.y; z = A.z;}

    float getMagnitude();
    Vector3d crossProduct(const Vector3d &);
    float dot(const Vector3d &);
    Vector3d multiply(float scalar);
    Vector3d unitVector();

    Vector3d operator - (const Vector3d &);
    Vector3d operator + (const Vector3d &);
    Vector3d operator / (float scalar); //< divide by a scalar
    // Vector3d operator * (float scalar); //< multiply by a scalar

    void printData()
    {std::cout<<x<<" "<<y<<" "<<z;}
};

#endif // VECTOR3D__H
