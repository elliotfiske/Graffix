//
//  ObjectNode.cpp
//  Lab6
//
//  Created by Elliot Fiske on 2/12/15.
//
//

#include "ObjectNode.h"


RenderingHelper currHelper;

ObjectNode::ObjectNode(double posX, double posY, double posZ, double rotX, double rotY, double rotZ, double sX, double sY, double sZ, double pivotX, double pivotY):
    posX(posX), posY(posY), posZ(posZ), rotX(rotX), rotY(rotY), rotZ(rotZ), sX(sX), sY(sY), sZ(sZ), pivotX(pivotX), pivotY(pivotY) {
    // Congrats, ObjectNode initialized!
}

void ObjectNode::draw(int mvID, int nVertices) {
    // Draw me!
    
    currHelper.translate(glm::vec3(posX, posY, posZ));
    currHelper.translate(glm::vec3(pivotX, pivotY, 0));
    currHelper.rotate(rotX, glm::vec3(1, 0, 0));
    currHelper.rotate(rotY, glm::vec3(0, 1, 0));
    currHelper.rotate(rotZ, glm::vec3(0, 0, 1));
    currHelper.translate(glm::vec3(-pivotX, -pivotY, 0));
    
    currHelper.pushMatrix();
        currHelper.scale(sX, sY, sZ); // We don't want scale to affect the children
    
        glUniformMatrix4fv(mvID, 1, GL_FALSE, glm::value_ptr(currHelper.modelViewMatrix));
        glDrawElements(GL_TRIANGLES, nVertices, GL_UNSIGNED_INT, 0);
    currHelper.popMatrix();
    
    // Draw my children!
    for (int ndx = 0; ndx < children.size(); ndx++) {
        currHelper.pushMatrix();
        children[ndx]->draw(mvID, nVertices);
        currHelper.popMatrix();
    }
}

void initHelper() {
    currHelper.useModelViewMatrix();
    currHelper.loadIdentity();
}