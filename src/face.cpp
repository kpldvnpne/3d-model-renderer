#include "Face.h"

Face::Face() {}
Face::~Face() {}

/**
 * @brief Constructor of Face
 * Each face has 3 vertices
 * Each vertex has position and normal indices
 *
 * @param Index of position and normal of 3 vertices
 * vn - represent vertex, normal - two items
 */
Face::Face(int v0, int v1, int v2, int n0, int n1, int n2) : v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2) {}
