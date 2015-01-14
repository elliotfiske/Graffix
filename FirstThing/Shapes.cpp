//
//  Triangle.cpp
//  FirstThing
//
//  Created by Elliot Fiske on 1/8/15.
//  Copyright (c) 2015 Elliot Fiske. All rights reserved.
//

#include "Shapes.h"
#include <stdarg.h>

double getMin(double a, double b, double c) {
    double min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

double getMax(double a, double b, double c) {
    double max = a;
    if (b < max) max = b;
    if (c < max) max = c;
    return max;
}

Point::Point(double x, double y, double z): x(x), y(y), z(z) {
    // good job boo you made a point.  hope you feel good about it.
}

Triangle::Triangle(Point v1, Point v2, Point v3): v1(v1), v2(v2), v3(v3) {
    // whoo you did it!
}

/**
 * Get the rectangle that completely surrounds this triangle
 */
Rect Triangle::boundingBox() {
    Rect result;
    result.x = getMin(v1.x, v2.x, v3.x);
    result.y = getMin(v1.y, v2.y, v3.y);
    
    double _maxX = getMax(v1.x, v2.x, v3.x);
    double _maxY = getMax(v1.y, v2.y, v3.y);
    
    result.width =  _maxX - result.x;
    result.height = _maxY - result.y;
    
    return result;
}

/**
 * Return a Point object based on the specified shapes vector.
 */
Point pointAtIndex(std::vector<tinyobj::shape_t> shapes, int shapeNdx, int index) {
    Point result(0, 0, 0);
    
    result.x = shapes[shapeNdx].mesh.positions[index*3 + 0];
    result.y = shapes[shapeNdx].mesh.positions[index*3 + 1];
    result.z = shapes[shapeNdx].mesh.positions[index*3 + 2];
    
    return result;
}

/**
 * Given a bunch of shapes, make a bunch of triangle objects that repreesnt them.
 */
std::vector<Triangle> getTriangles(std::vector<tinyobj::shape_t> shapes) {
    std::vector<Triangle> result;
    
    for (int ndx = 0; ndx < shapes.size(); ndx++) {
        for (size_t triNdx = 0; triNdx < shapes[ndx].mesh.indices.size() / 3; triNdx++) {
            int index1 = shapes[ndx].mesh.indices[3*triNdx+0];
            int index2 = shapes[ndx].mesh.indices[3*triNdx+1];
            int index3 = shapes[ndx].mesh.indices[3*triNdx+2];
            
            Point vert1 = pointAtIndex(shapes, ndx, index1);
            Point vert2 = pointAtIndex(shapes, ndx, index2);
            Point vert3 = pointAtIndex(shapes, ndx, index3);
            
            Triangle newTriangle(vert1, vert2, vert3);
            result.push_back(newTriangle);
        }
    }
    
    return result;
}

