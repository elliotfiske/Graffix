//
//  Camera.h
//  FirstThing
//
//  Created by Elliot Fiske on 1/12/15.
//  Copyright (c) 2015 Elliot Fiske. All rights reserved.
//

#ifndef __FirstThing__Camera__
#define __FirstThing__Camera__

#include "Image.h"
#include <iostream>

/** Temp variable to figure out how to map from "real" coordinates to image coordinates */
#define REAL_TO_IMAGE 100

/**
 * Defines a camera that can generate images from a 3D space
 *  with points / triangles in it.
 */
class Camera {
public:
    Camera();
    
    /** Generate image of dimension (xRes, yRes) */
    Image makeImage(int xRes, int yRes);
    
    void setShapes(std::vector<tinyobj::shape_t> shapes);
    
private:
    /** What will the camera be rendering? */
    std::vector<tinyobj::shape_t> _shapes;
    /** Bounds of the vertices we're rendering */
    float _minX, _maxX, _minY, _maxY, _minZ, _maxZ;
    std::vector<Triangle> _triangles;
};

#endif /* defined(__FirstThing__Camera__) */
