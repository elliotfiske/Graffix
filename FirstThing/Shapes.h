//
//  Shapes.h
//  FirstThing
//
//  Created by Elliot Fiske on 1/8/15.
//  Copyright (c) 2015 Elliot Fiske. All rights reserved.
//

#ifndef __FirstThing__Triangle__
#define __FirstThing__Triangle__

#include <stdio.h>


/* Color struct */
typedef struct color_struct {
    double r;
    double g;
    double b;
    double f; // "filter" or "alpha"
} color_t;


/**
 * Defines a 3D Point in space.
 *  You can also give the vertex a color.
 */
class Point {
public:
    Point(double x, double y, double z);
    
    double x, y, z;
    color_t color;
};

/** Rectangles are GO! */
typedef struct GET_REKT {
    double x, y;
    double width, height;
} Rect;

/** Handy way to return all the stuff we need from the determinant */
typedef struct determinantResult {
    double alpha, beta, gamma;
} determinantResult;

/**
 * Defines a triangle in 3D space.
 *  A triangle is made up of 3 vertices, each with a specified color.
 *  The Triangle class contains helper functions that allow us to render
 *  it on a 2D image.
 */
class Triangle {
public:
    Triangle(Point v1, Point v2, Point v3);
    
    Point v1, v2, v3;
    Rect boundingBox();
};



#endif /* defined(__FirstThing__Triangle__) */