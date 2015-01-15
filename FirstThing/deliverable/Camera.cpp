 //
//  Camera.cpp
//  FirstThing
//
//  Created by Elliot Fiske on 1/12/15.
//  Copyright (c) 2015 Elliot Fiske. All rights reserved.
//

#include "Camera.h"
#include <limits>
#include <assert.h>

Camera::Camera() {
    // GOOD JUB DUNKY U MADE CAMERA
}

// Given a vector of shapes which has already been read from an obj file
// resize all vertices to the range [-1, 1]
void resize_obj(std::vector<tinyobj::shape_t> &shapes){
    float minX, minY, minZ;
    float maxX, maxY, maxZ;
    float scaleX, scaleY, scaleZ;
    float shiftX, shiftY, shiftZ;
    float epsilon = 0.001;
    
    minX = minY = minZ = 1.1754E+38F;
    maxX = maxY = maxZ = -1.1754E+38F;
    
    //Go through all vertices to determine min and max of each dimension
    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
            if(shapes[i].mesh.positions[3*v+0] < minX) minX = shapes[i].mesh.positions[3*v+0];
            if(shapes[i].mesh.positions[3*v+0] > maxX) maxX = shapes[i].mesh.positions[3*v+0];
            
            if(shapes[i].mesh.positions[3*v+1] < minY) minY = shapes[i].mesh.positions[3*v+1];
            if(shapes[i].mesh.positions[3*v+1] > maxY) maxY = shapes[i].mesh.positions[3*v+1];
            
            if(shapes[i].mesh.positions[3*v+2] < minZ) minZ = shapes[i].mesh.positions[3*v+2];
            if(shapes[i].mesh.positions[3*v+2] > maxZ) maxZ = shapes[i].mesh.positions[3*v+2];
        }
    }
    
    //From min and max compute necessary scale and shift for each dimension
    float maxExtent = 1, xExtent, yExtent, zExtent;
    xExtent = maxX-minX;
    yExtent = maxY-minY;
    zExtent = maxZ-minZ;
    if (xExtent >= yExtent && xExtent >= zExtent) {
        maxExtent = xExtent;
    }
    if (yExtent >= xExtent && yExtent >= zExtent) {
        maxExtent = yExtent;
    }
    if (zExtent >= xExtent && zExtent >= yExtent) {
        maxExtent = zExtent;
    }
    scaleX = 2.0 / maxExtent;
    shiftX = minX + (xExtent/ 2.0);
    scaleY = 2.0 / maxExtent;
    shiftY = minY + (yExtent / 2.0);
    scaleZ = 2.0/ maxExtent;
    shiftZ = minZ + (zExtent)/2.0;
    
    //Go through all verticies shift and scale them
    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
            shapes[i].mesh.positions[3*v+0] = (shapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
            assert(shapes[i].mesh.positions[3*v+0] >= -1.0 - epsilon);
            assert(shapes[i].mesh.positions[3*v+0] <= 1.0 + epsilon);
            shapes[i].mesh.positions[3*v+1] = (shapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
            assert(shapes[i].mesh.positions[3*v+1] >= -1.0 - epsilon);
            assert(shapes[i].mesh.positions[3*v+1] <= 1.0 + epsilon);
            shapes[i].mesh.positions[3*v+2] = (shapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
            assert(shapes[i].mesh.positions[3*v+2] >= -1.0 - epsilon);
            assert(shapes[i].mesh.positions[3*v+2] <= 1.0 + epsilon);
        }
    }
}



/**
 * Tell the camera what shapes you want rendered.
 */
void Camera::setShapes(std::vector<tinyobj::shape_t> shapes) {
    _shapes = shapes;
    
    resize_obj(_shapes);
    _triangles = getTriangles(_shapes);
}


/** 
 * Generate image of dimension (xRes, yRes)
 *  If depth is true, does the funky shaded depth thing.  Otherwise, just goes from blue->green
 *  when you render
 */
Image Camera::makeImage(int width, int height, bool depth) {
    Image result(width, height);
    float zBuffer[width * height];
    for (int ndx = 0; ndx < width * height; ndx++) {
        zBuffer[ndx] = -10000;
    }
    
    color_t bgColor = WHITE;
    
    // Make the image background a pleasing shade of blue
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            result.pixel(x, y, bgColor);
        }
    }
    
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
    
    double scale = fmin(xScale, yScale);
    
    // Convert triangles to image coordinates
    std::vector<Triangle> scaledTriangles = _triangles;
    for (int ndx = 0; ndx < scaledTriangles.size(); ndx++) {
        scaledTriangles[ndx] = triangleToImageCoords(scaledTriangles[ndx], scale, xOffset, yOffset);
    }
    
    for (int ndx = 0; ndx < scaledTriangles.size(); ndx++) {
        Rect triBounds = scaledTriangles[ndx].boundingBox();
        
        for (int rx = triBounds.x; rx < triBounds.x + triBounds.width; rx++) {
            for (int ry = triBounds.y; ry < triBounds.y + triBounds.height; ry++) {
                if (rx < 0 || ry < 0) {
                    // Vertex is behind us.  Awkward.
                    continue;
                }
                
                if (rx < width - 1 && ry < height - 1) {
                    double zValue = scaledTriangles[ndx].zDeterminant(Point(rx, ry, 0));
                    
                    if (zValue == -100) {
                        continue;
                    }
                    
                    zValue++;
                    zValue /= 2;
                    
                    color_t shadedRed = BLACK;
                    shadedRed.r = zValue;
                    
                    if (zBuffer[width * ry + rx] > zValue) {
                        continue;
                    }
                    
                    if (depth) {
                        result.pixel(rx, ry, shadedRed);
                    }
                    else {
                        double blueness  = (rx + 1) / 2;
                        double greenness =  1 - blueness;
                        color_t teal = WHITE;
                        teal.b = blueness;
                        teal.g = greenness;
                        result.pixel(rx, ry, teal);
                    }
                    
                    zBuffer[width * ry + rx] = zValue;
                }
            }
        }
    }
    
    return result;
}