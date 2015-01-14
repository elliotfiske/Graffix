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

