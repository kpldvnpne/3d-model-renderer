#include <iostream>
#include <cstring>
#include <stdio.h>

using std::cout;
using std::endl;

#include "Model.h"
#include "Vector3d.h"
#include "Face.h"

Model::Model()
{
    //initialize variables
    scaleFactor = 1;
    viewUp = Vector3d(0,1,0);
}

//-----BEFORE CALLING loadModel CALL setViewCoordinate-----//
/**
 * @brief Function to load obj file for the model to render
 * Constructs vertex table and face table.
 * It also transforms World Coordinate vertex to View Coordinate
 * as soon as the vertex is read.
 * @param Path to obj file
 * @return File success or fail to read
 */
bool Model::loadModel(const char* modelPath){

    vertexCount=0,normalCount=0,faceCount=0;

    float x,y,z;
    float nx,ny,nz;
    int v0,v1,v2,n0,n1,n2;

    xmin = ymin = zmin = INF;
    xmax = ymax = zmax = -INF;

    FILE * file = fopen(modelPath, "r");
    if( file == NULL ){
        std::cerr<<"File cannot open"<<endl;
        return false;
    }


    while(1){
        char lineHeader[1024];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v" ) == 0 ){
            fscanf(file, "%f %f %f\n", &x, &y, &z);

            xmax = std::max(xmax,x); ymax = std::max(ymax,y); zmax = std::max(zmax,z);
            xmin = std::min(xmin,x); ymin = std::min(ymin,y); zmin = std::min(zmin,z);

            vertexTable.push_back(Vector3d(x,y,z));
            vertexCount++;
        }

        //'vn' is normal vector to the vertex and may not be unit vectors
        else if(strcmp(lineHeader, "vn")==0){
            fscanf(file, "%f %f %f\n", &nx, &ny, &nz);
            normalTable.push_back(Vector3d(nx,ny,nz));
            normalCount++;
        }

        //'f' for faces
        else if(strcmp(lineHeader,"f")==0){

            fscanf(file,"%d//%d %d//%d %d//%d", &v0, &n0, &v1, &n1, &v2, &n2);

            v0--; v1--; v2--;
            n0--; n1--; n2--;

            faceTable.push_back(Face(v0,v1,v2,n0,n1,n2));
            faceCount++;
        }

    }
    fclose(file);
    return true;
}


void Model::printData()
{
    int i;
    for(i = 0; i< vertexCount; i++)
    {
        cout<<"v ";
        vertexTable[i].printData();
        cout<<endl;
    }

    for(i = 0; i< normalCount; i++)
    {
        cout<<"vn ";
        normalTable[i].printData();
        cout<<endl;
    }

    for(i = 0; i< faceCount; i++)
    {
        cout<<"f "<<faceTable[i].v0<<" "<<faceTable[i].v1<<" "<<faceTable[i].v0<<endl;
    }
    cout<<"xmax "<<xmax<<" ymax "<<ymax<<" zmax "<<zmax<<endl;
    cout<<"xmin "<<xmin<<" ymin "<<ymin<<" zmin "<<zmin<<endl<<endl;
}

