//
//  ObjectNode.h
//  Lab6
//
//  Created by Elliot Fiske on 2/12/15.
//
//

#ifndef __Lab6__ObjectNode__
#define __Lab6__ObjectNode__

#include <stdio.h>
#include <vector>

#include "RenderingHelper.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr
#include "GLSL.h"


class ObjectNode {
    ObjectNode(double posX, double posY, double posZ, double rotX, double rotY, double rotZ);
    
    static RenderingHelper currHelper;
    double posX, posY, posZ, rotX, rotY, rotZ;
    std::vector<ObjectNode> children;
    
    void draw(int mvID, int nVertices);
};



#endif /* defined(__Lab6__ObjectNode__) */
