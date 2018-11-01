#include "Vector3d.h"
#include<iostream>
#include<cmath>

/**
 * @brief Calculate cross product of two vectors
 * Should explicitely be used with real 3D vectors
 * @param real 3D vector
 * @return cross product of this vector with input vector (AxB)
 */
Vector3d Vector3d::crossProduct(const Vector3d &B)
{ return Vector3d(y*B.z - z*B.y, z*B.x - x*B.z, x*B.y - y*B.x);}

float Vector3d::dot(const Vector3d &B)
{return (x * B.x + y * B.y + z * B.z);}


/**
 * @brief Calculates unit vector of the calling vector
 * @param this
 * @return unit vector of type Vector3d
 */
Vector3d Vector3d::unitVector()
{
    float mag = getMagnitude();
    return Vector3d(x/mag, y/mag, z/mag);
}


float Vector3d::getMagnitude()
{return sqrt(x*x + y*y + z*z);}


//operator - overloaded to calculate vector from A to B
Vector3d Vector3d::operator - (const Vector3d &B)
{return Vector3d(x - B.x, y - B.y, z - B.z);}

//operator + overloaded to calculate vector A + B
Vector3d Vector3d::operator + (const Vector3d &B)
{return Vector3d(x + B.x, y + B.y, z + B.z);}

//operator / overloaded for division by scalar
Vector3d Vector3d::operator / (float scalar)
{ return Vector3d(x/scalar, y/scalar, z/scalar);}

//multiply by scalar
Vector3d Vector3d::multiply (float scalar)
{ return Vector3d(x * scalar, y * scalar, z * scalar);}
