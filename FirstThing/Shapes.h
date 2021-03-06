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
#include "tiny_obj_loader.h"
#include <math.h>


/* Color struct */
typedef struct color_struct {
    double r;
    double g;
    double b;
    double f; // "filter" or "alpha"
} color_t;

/** Some basic colors */
#define BG_COLOR { 0.5, 0.5, 0.9, 1 }
#define RED      { 1,   0,   0,   1 }
#define WHITE    /* Thomas Steinke */{ 1,   1,   1,   1 }
#define BLACK    { 0, 0, 0, 1 }
#define GREEN    { 0, 1, 0, 1 }

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

double getDeterminant(Point a, Point b, Point c);

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
    double zDeterminant(Point inside);
};

std::vector<Triangle> getTriangles(std::vector<tinyobj::shape_t> &shapes);

Triangle triangleToImageCoords(Triangle in, double scale, double xOffset, double yOffset);


#endif /* defined(__FirstThing__Triangle__) */