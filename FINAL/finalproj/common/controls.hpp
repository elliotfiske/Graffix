#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void setUpCallbacks();
bool didCollectLight(double minH, double maxH, double minV, double maxV);
bool checkAngle(double minH, double maxH, double minV, double maxV);
void suggestAngle(double h, double v);

#endif