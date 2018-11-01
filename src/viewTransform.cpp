#include "Model.h"

#include<iostream>

using std::cout;
using std::endl;
using std::max;

/**
 * @brief Convert model into unit cube and then to cube in range 0 to 100. THis is done to define any model in
 * same range
 */
void Model::normalize ()
{
    //xvmin = yvmin = zvmin = 0;
    float vmax = 100;
    float autoScale;
    float wmax = max(xmax,max(ymax,zmax));
    if(wmax == xmax)
        autoScale = vmax / (xmax - xmin);
    else if(wmax == ymax)
        autoScale = vmax / (ymax - ymin);
    else
        autoScale = vmax / (zmax - zmin);

    int i;
    for(i = 0; i < vertexCount; i++) {
        Vector3d &v = vertexTable[i];
        v.x = (v.x - xmin) * autoScale;
        v.y = (v.y - ymin) * autoScale;
        v.z = (v.z - zmin) * autoScale;
    }
/*
    for(auto &n : normalTable) {
        n.x = (n.x - xmin) * autoScale;
        n.y = (n.y - ymin) * autoScale;
        n.z = (n.z - zmin) * autoScale;
    }
*/
    //At this point our model is defined in 100x100x100 cube
    //so
    xmax = (xmax - xmin) * autoScale;
    ymax = (ymax - ymin) * autoScale;
    zmax = (zmax - zmin) * autoScale;
    xmin = ymin = zmin = 0;
}

// to auto adjust the camera and view plane
void Model::autoFocus()
{
    camera = Vector3d((xmax + xmin)/2, (ymax + ymin)/2,(2*zmax + zmin));
    lookAt = Vector3d((xmax + xmin)/2, (ymax + ymin)/2, zmax);
    viewUp = Vector3d(0,1,0);
    Zprp = camera.z;
    lightSource = camera;
    color = sf::Color(150,150,150);
    bgcolor = sf::Color(0,0,0);
}

/**
 * @brief This function sets up a viewing coordinate based on
 * view reference (camera position), Normal Vector and View Up Vector
 * @param Camera Point, Look-at-point, view UP vector and Zvp
 * @return void - sets up view coordinate
 */
void Model::setViewCoordinate()
{
    n = (camera - lookAt).unitVector();
    u = (viewUp.crossProduct(n)).unitVector();
    v = n.crossProduct(u);

    //repeated values in viewTransform; so calculated at once
    val1 = u.x * camera.x + u.y * camera.y + u.z * camera.z;
    val2 = v.x * camera.x + v.y * camera.y + v.z * camera.z;
    val3 = n.x * camera.x + n.y * camera.y + n.z * camera.z;
}


/**
 * @brief viewTransform transforms the Model in world coordinate
 * to viewing coordinate.And also PERSPECTIVE PROJECTION is performed.
 * This function is called from within loadModel().
 * @param camera - camera point, N - normal vector, U - view Up vector
 * @return void - transforms vertex table to view coordinate
 */
void Model::viewTransform()
{
    int i;
    float xt,yt,zt;
    for(i = 0; i < vertexCount; i++) {
        Vector3d &vt = vertexTable[i];

        xt = u.x * vt.x + u.y * vt.y + u.z * vt.z - val1;
        yt = v.x * vt.x + v.y * vt.y + v.z * vt.z - val2;
        zt = n.x * vt.x + n.y * vt.y + n.z * vt.z - val3;

        vt.x = xt * scaleFactor;
        vt.y = yt * scaleFactor;
        vt.z = zt * scaleFactor;

        //initialize projectionTable
        projectionTable.push_back(Vector3d(0,0,0));
    }

    xt = u.x * xmax + u.y * ymax + u.z * zmax - val1;
    yt = v.x * xmax + v.y * ymax + v.z * zmax - val2;
    zt = n.x * xmax + n.y * ymax + n.z * zmax - val3;
    xmax = xt * scaleFactor; ymax = yt * scaleFactor; zmax = zt * scaleFactor;

    xt = u.x * xmin + u.y * ymin + u.z * zmin - val1;
    yt = v.x * xmin + v.y * ymin + v.z * zmin - val2;
    zt = n.x * xmin + n.y * ymin + n.z * zmin - val3;
    xmin = xt * scaleFactor; ymin = yt * scaleFactor; zmin = zt * scaleFactor;

    for(auto &n : normalTable) {
        xt = u.x * n.x + u.y * n.y + u.z * n.z - val1;
        yt = v.x * n.x + v.y * n.y + v.z * n.z - val2;
        zt = n.x * n.x + n.y * n.y + n.z * n.z - val3;
    }
  //  Zvp = ((ymax - ymin - windowY) * Zprp + windowY * zmax) / (ymax - ymin);
    Zvp = (Zprp - zmax)/2;
    dp = Zprp - Zvp;
}

Vector3d Model::viewTransform(Vector3d &vt) {
    float xt,yt,zt;
    xt = u.x * vt.x + u.y * vt.y + u.z * vt.z - val1;
    yt = v.x * vt.x + v.y * vt.y + v.z * vt.z - val2;
    zt = n.x * vt.x + n.y * vt.y + n.z * vt.z - val3;

    vt.x = xt * scaleFactor;
    vt.y = yt * scaleFactor;
    vt.z = zt * scaleFactor;

    return v;
}
/*
Vector3d Model::project(const Vector3d &v)
{

    //Now is the time for PERSPECTIVE PROJECTION of ViewCoordinate point
    float xp,yp, zp = v.z;
    h = (Zprp - v.z)/dp;
    xp = v.x / h;
    yp = v.y / h;

    //translate projected point to SFML window
    xp += windowX/2;
    yp += windowY/2;
    // v.y = -v.y;

    // cout<<"vp "<<v.x<<" "<<v.y<<" "<<v.z<<endl;
    return Vector3d(xp,yp,zp);
}
*/

void Model::project()
{
    Vector3d v;
    float xp,yp,zp;
    int i;
    for(i = 0; i < vertexCount; i++) {
        v = vertexTable[i];
        zp = v.z;
        h = (Zprp - v.z)/dp;
        xp = v.x / h;
        yp = v.y / h;

        //translate projected point to SFML window
        xp += windowX/2;
        yp += windowY/2;

        projectionTable[i] = Vector3d(xp,yp,zp);
    }
}
void Model::toView(Vector3d &v)
{
    v.x -= windowX/2;
    v.y -= windowY/2;

    v.x *= h;
    v.y *= h;
}
