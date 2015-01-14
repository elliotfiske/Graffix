//
//  Camera.h
//  FirstThing
//
//  Created by Elliot Fiske on 1/12/15.
//  Copyright (c) 2015 Elliot Fiske. All rights reserved.
//

#ifndef __FirstThing__Camera__
#define __FirstThing__Camera__

#include <stdio.h>
#include "Image.h"
#include <iostream>
#include "tiny_obj_loader.h"

/** Temp variable to figure out how to map from "real" coordinates to image coordinates */
#define REAL_TO_IMAGE 100

/**
 * Defines a camera that can generate images from a 3D space
 *  with points / triangles in it.
 */
class Camera {
public:
    Camera(Point pos, double focalLength, double xRot, double yRot, double zRot);
    
    Point position;
    double focalLength;
    
    /** Defines where the camera is pointing.  (0, 0, 0) is straight up. */
    double xRot, yRot, zRot;
    
    /** Generate image of dimension (xRes, yRes) */
    Image makeImage(int xRes, int yRes);
    
    void setShapes(std::vector<tinyobj::shape_t> shapes);
    
private:
    /** What will the camera be rendering? */
    std::vector<tinyobj::shape_t> _shapes;
    /** Bounds of the vertices we're rendering */
    float _minX, _maxX, _minY, _maxY;
};

#endif /* defined(__FirstThing__Camera__) */
