#ifndef PYRAMID_H
#define PYRAMID_H

// Defines a point in 3D space
struct Point3D {
    float x, y, z;
};

// Defines an edge between two points, using their indices
struct Edge {
    int start; // Index of the start point
    int end;   // Index of the end point
};

#endif // PYRAMID_H
#pragma once
