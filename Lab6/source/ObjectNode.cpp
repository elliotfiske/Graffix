//
//  ObjectNode.cpp
//  Lab6
//
//  Created by Elliot Fiske on 2/12/15.
//
//

#include "ObjectNode.h"

ObjectNode::ObjectNode(double posX, double posY, double posZ, double rotX, double rotY, double rotZ): posX(posX), posY(posY), posZ(posZ), rotX(rotX), rotY(rotY), rotZ(rotZ) {
    // Congrats, ObjectNode initialized!
}

void ObjectNode::draw(int mvID, int nVertices) {
    // Draw me!
    
    currHelper.translate(glm::vec3(posX, posY, posZ));
    currHelper.rotate(rotX, glm::vec3(1, 0, 0));
    currHelper.rotate(rotY, glm::vec3(0, 1, 0));
    currHelper.rotate(rotZ, glm::vec3(0, 0, 1));
    
    
    glUniformMatrix4fv(mvID, 1, GL_FALSE, glm::value_ptr(currHelper.modelViewMatrix));
    glDrawElements(GL_TRIANGLES, nVertices, GL_UNSIGNED_INT, 0);
    
    // Draw my children!
    for (int ndx = 0; ndx < children.size(); ndx++) {
        children[ndx].draw(mvID, nVertices);
    }
    
}