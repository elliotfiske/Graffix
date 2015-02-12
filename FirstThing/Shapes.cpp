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
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

Point::Point(double x, double y, double z): x(x), y(y), z(z) {
    // good job boo you mace a point.  hope you feel good about it.
}

/**
 * Get the determinant of 3 points. Only accurate for counter-clockwise triangles.
 */
double getDeterminant(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}



Triangle::Triangle(Point v1, Point v2, Point v3): v1(v1), v2(v2), v3(v3) {
    // We want to make sure all our triangles are the same direction (counter-clockwise!)
    if (getDeterminant(v1, v2, v3) < 0) {
        Point temp = v1;
        v1 = v2;
        v2 = temp;
    }
}

/**
 * Get the rectangle that completely surrounds this triangle
 */
Rect Triangle::boundingBox() {
    Rect result;
    result.x = getMin(v1.x, v2.x, v3.x);
    result.y = getMin(v1.y, v2.y, v3.y);
    
    result.x = floor(result.x);
    result.y = floor(result.y);
    
    double _maxX = getMax(v1.x, v2.x, v3.x);
    double _maxY = getMax(v1.y, v2.y, v3.y);
    
    result.width =  ceil(_maxX - result.x);
    result.height = ceil(_maxY - result.y);
    
    return result;
}

/**
 * Given a point, determine what the z-value of the point in the triangle.
 *  Returns -100 if the point is outside the triangle.
 */
double Triangle::zDeterminant(Point inside) {
    double alpha = 0; // Opposite to vertex 1
    double beta  = 0; // Opposite to vertex 2
    double gamma = 0; // Opposite to vertex 3
    
    alpha = getDeterminant(inside, v2, v3);
    beta  = getDeterminant(inside, v3, v1);
    gamma = getDeterminant(inside, v1, v2);
    
    if (alpha < 0 || beta < 0 || gamma < 0) {
        return -100;
    }
    
    double totalArea = alpha + beta + gamma;
    
    alpha /= totalArea;
    beta  /= totalArea;
    gamma /= totalArea;
    
    return v1.z*alpha + v2.z*beta + v3.z*gamma;
}

/**
 * Return a Point object based on the specified shapes vector.
 */
Point pointAtIndex(std::vector<tinyobj::shape_t> &shapes, int shapeNdx, int index) {
    Point result(0, 0, 0);
    
    result.x = shapes[shapeNdx].mesh.positions[index*3 + 0];
    result.y = shapes[shapeNdx].mesh.positions[index*3 + 1];
    result.z = shapes[shapeNdx].mesh.positions[index*3 + 2];
    
    return result;
}

/**
 * Given a bunch of shapes, make a bunch of triangle objects that repreesnt them.
 */
std::vector<Triangle> getTriangles(std::vector<tinyobj::shape_t> &shapes) {
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

/**
 * Scales up a triangle from world coords to pixel coords
 */
Triangle triangleToImageCoords(Triangle in, double scale, double xOffset, double yOffset) {
    in.v1.x *= scale;
    in.v1.x += xOffset;
    in.v1.y *= scale;
    in.v1.y += yOffset;
    
    in.v2.x *= scale;
    in.v2.x += xOffset;
    in.v2.y *= scale;
    in.v2.y += yOffset;
    
    in.v3.x *= scale;
    in.v3.x += xOffset;
    in.v3.y *= scale;
    in.v3.y += yOffset;
    
    return in;
}

