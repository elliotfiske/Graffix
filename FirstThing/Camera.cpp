//
//  Camera.cpp
//  FirstThing
//
//  Created by Elliot Fiske on 1/12/15.
//  Copyright (c) 2015 Elliot Fiske. All rights reserved.
//

#include "Camera.h"
#include <limits>

Camera::Camera(Point pos,
               double focalLength,
               double xRot,
               double yRot,
               double zRot): position(pos), focalLength(focalLength), xRot(xRot), yRot(yRot), zRot(zRot) {
    // GOOD JUB DUNKY U MADE CAMERA
}

/**
 * Tell the camera what shapes you want rendered.
 *  Here we also figure out the smallest/biggest X/Y value we need to draw.
 */
void Camera::setShapes(std::vector<tinyobj::shape_t> shapes) {
    _shapes = shapes;

    // Find the bounds of the vertices
    _minX = _minY = _minZ = std::numeric_limits<float>::max();
    _minY = _minX;
    _minZ = _minX;
    _maxX = std::numeric_limits<float>::min();
    _maxY = _maxX;
    _maxZ = _maxX;
    
    std::numeric_limits<float>::min();
    for (int ndx = 0; ndx < shapes.size(); ndx++) {
        for (size_t vert = 0; vert < shapes[ndx].mesh.positions.size() / 3; vert++) {
            float currX = _shapes[ndx].mesh.positions[3*vert+0];
            float currY = _shapes[ndx].mesh.positions[3*vert+1];
            float currZ = _shapes[ndx].mesh.positions[3*vert+2];
            
            if (currX < _minX) { _minX = currX; }
            
            if (currX > _maxX) { _maxX = currX; }
            
            if (currY < _minY) { _minY = currY; }
            
            if (currY > _maxY) { _maxY = currY; }
            
            if (currZ < _minZ) { _minZ = currZ; }
            
            if (currZ > _maxZ) { _maxZ = currZ; }
        }
    }
    
    float xRange = _maxX - _minX;
    float yRange = xRange; // Make sure we don't scale the X and Y coords differently
    
    float TARGET_X_MAX = 0.8, TARGET_X_MIN = -0.8;
    float TARGET_Y_MAX = 0.8, TARGET_Y_MIN = -0.8;
    
    // Fix those dumb vertices if they're in a weird scale
    for (int ndx = 0; ndx < shapes.size(); ndx++) {
        for (size_t vert = 0; vert < shapes[ndx].mesh.positions.size() / 3; vert++) {
            float currX = _shapes[ndx].mesh.positions[3*vert+0];
            float currY = _shapes[ndx].mesh.positions[3*vert+1];
            
            _shapes[ndx].mesh.positions[3*vert+0] = (currX - _minX) * (TARGET_X_MAX - TARGET_X_MIN) / xRange + TARGET_X_MIN;
            _shapes[ndx].mesh.positions[3*vert+1] = (currY - _minY) * (TARGET_Y_MAX - TARGET_Y_MIN) / yRange + TARGET_Y_MIN;
            
            printf("converting to: %f, %f\n",             _shapes[ndx].mesh.positions[3*vert+0],             _shapes[ndx].mesh.positions[3*vert+1]);
        }
    }
    
    _triangles = getTriangles(_shapes);
}


/** Generate image of dimension (xRes, yRes) */
Image Camera::makeImage(int width, int height) {
    Image result(width, height);
    color_t white;
    white.r = white.b = white.g = 1;
    
    double xScale = 1, xOffset = 0;
    double yScale = 1, yOffset = 0;
    
    double L = 1, R = 1, B = 1, T = 1;
    
    if (width >= height) {
        L = -width / height;
        R =  width / height;
        B = -1;
        T =  1;
    }
    else {
        L = -1;
        R =  1;
        B = -height / width;
        T =  height / width;
    }
    
    // BEHOLD, MATH!!
    xScale = (1 - width) / (L - R);
    xOffset = -xScale * L;
    
    yScale = (1 - height) / (B - T);
    yOffset = -yScale * B;
    
    for (size_t ndx = 0; ndx < _shapes.size(); ndx++) {
        for (size_t triNdx = 0; triNdx < _shapes[ndx].mesh.indices.size() / 3; triNdx++) {
                        printf("  triangle[%ld] = %d, %d, %d\n", triNdx, _shapes[ndx].mesh.indices[3*triNdx+0], _shapes[ndx].mesh.indices[3*triNdx+1], _shapes[ndx].mesh.indices[3*triNdx+2]);
        }
        
        for (size_t vert = 0; vert < _shapes[ndx].mesh.positions.size() / 3; vert++) {
            float vX = _shapes[ndx].mesh.positions[3*vert+0];
            float vY = _shapes[ndx].mesh.positions[3*vert+1];
            float vZ = _shapes[ndx].mesh.positions[3*vert+2];
            
            int imgX = vX * xScale + xOffset;// / vZ * REAL_TO_IMAGE;
            int imgY = vY * yScale + yOffset;// / vZ * REAL_TO_IMAGE;
            
//            printf("Rendering vertex[%ld] = (%d, %d)\n", vert, imgX, imgY);
            
            if (imgX < 0 || imgY < 0) {
                // Vertex is behind us.  Awkward.
                continue;
            }
            
            // Check if rendered vertex is even on screen
            if (imgX < width - 1 && imgY < height - 1) {
//                result.pixel(imgX, imgY, white);
            }
        }
    }
    
    
    return result;
}