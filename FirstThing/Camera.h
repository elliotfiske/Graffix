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
#include "Triangle.h"

/**
 * Defines a camera that can generate images from a 3D space
 *  with points / triangles in it.
 */
class Camera {
public:
    Camera(Point pos, double xRot, double yRot, double zRot);
    
    Point position;
    double xRot, yRot, zRot; /** Defines where the camera is pointing.  (0, 0, 0) is straight up. */
};

#endif /* defined(__FirstThing__Camera__) */
