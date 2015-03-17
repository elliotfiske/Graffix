// Include GLFW
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 0 );
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

double totalScrolling = 0;
float FoV = initialFoV;

double maxH = 4.62, minH = 1.64;
double maxV = 1.24, minV = -0.44;

void handle_scroll(GLFWwindow* window, double xOffset, double yOffset) {
    double horizChange = xOffset * mouseSpeed;
    double vertChange  = yOffset * mouseSpeed;
    
    if (horizChange > 0) {
        double diff = maxH - horizontalAngle;
        if (diff < 0.2) {
            horizChange *= diff;
        }
    }
    else {
        double diff = horizontalAngle - minH;
        if (diff < 0.2) {
            horizChange *= diff;
        }
    }
    
    if (vertChange > 0) {
        double diff = maxV - verticalAngle;
        if (diff < 0.2) {
            vertChange *= diff;
        }
    }
    else {
        double diff = verticalAngle - minV;
        if (diff < 0.2) {
            vertChange *= diff;
        }
    }
    
    horizontalAngle += horizChange;
    verticalAngle   += vertChange;
}

/** User collected a sanity bubble.  Restore some FOV over a bit. */
double targetFOV = initialFoV;
void relaxFOV() {
    targetFOV += 1;
}

void setUpCallbacks() {
    glfwSetScrollCallback(window, handle_scroll);
}

void computeMatricesFromInputs(){
    // Slooowly tighten FOV over time
    targetFOV -= 0.001;
    double diff = targetFOV - FoV;
    FoV += diff / 4;
    
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);
    
	// Compute new orientation  (not working for my comp for some reason)
//	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
//	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	} 
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}