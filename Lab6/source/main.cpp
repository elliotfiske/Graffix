//
// seriously modified ZJ Wood January 2015 - conversion to glfw
// inclusion of matrix stack Feb. 2015
// original from Shinjiro Sueda
// October, 2014
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>
#include "tiny_obj_loader.h"
#include "ObjectNode.h"


GLFWwindow* window;
using namespace std;

vector<tinyobj::shape_t> shapes;
vector<tinyobj::material_t> materials;
GLuint prog;
GLuint posBufObj = 0;
GLuint norBufObj = 0;
GLuint indBufObj = 0;
GLint aPos = 0;
GLint aNor = 0;
GLint uMV = 0;
GLint uP = 0;

static float g_width, g_height;
float theta;

// Here's the fun part of the robot!
ObjectNode *bodyNode = new ObjectNode(0, 0, -5, 0, 0, 0, 1, 2, 1, 0, 0);

ObjectNode *rightForeArm = new ObjectNode(  1, 0.75, 0,  0, 0, 0,      1, 0.25, 0.5,     -0.5, 0);
ObjectNode *rightMainArm = new ObjectNode(  1, 0, 0,  0, 0, 0,      1, 0.25, 0.5,         -0.5, 0);

ObjectNode *leftForeArm = new ObjectNode(-1, 0.75, 0, 0, 0, 0, 1, 0.25, 0.5, 0.5, 0);
ObjectNode *leftMainArm = new ObjectNode(-1, 0, 0, 0, 0, 0, 1, 0.25, 0.5, 0.5, 0);

ObjectNode *leftLeg = new ObjectNode(-0.25, -1.5, 0, 0, 0, 0, 0.25, 1, 1, 0, 0.5);
ObjectNode *rightLeg = new ObjectNode(0.25, -1.5, 0, 0, 0, 0, 0.25, 1, 1, 0, 0.5);

ObjectNode *head = new ObjectNode(0, 1.4, 0, 0, 0, 0, .75, .5, .5, 0, 0);

void loadShapes(const string &objFile)
{
    string err = tinyobj::LoadObj(shapes, materials, objFile.c_str());
    if(!err.empty()) {
        cerr << err << endl;
    }
}

void initGL()
{
    
    leftForeArm->children.push_back(leftMainArm);
    
    rightForeArm->children.push_back(rightMainArm);
    
    bodyNode->children.push_back(leftForeArm);
    bodyNode->children.push_back(rightForeArm);
    bodyNode->children.push_back(head);
    bodyNode->children.push_back(leftLeg);
    bodyNode->children.push_back(rightLeg);
    
    
    // Set the background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Enable Z-buffer test
    glEnable(GL_DEPTH_TEST);
    
    // Send the position array to the GPU
    const vector<float> &posBuf = shapes[0].mesh.positions;
    glGenBuffers(1, &posBufObj);
    glBindBuffer(GL_ARRAY_BUFFER, posBufObj);
    glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
    
    // Send the normal array to the GPU
    const vector<float> &norBuf = shapes[0].mesh.normals;
    glGenBuffers(1, &norBufObj);
    glBindBuffer(GL_ARRAY_BUFFER, norBufObj);
    glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
    
    // Send the index array to the GPU
    const vector<unsigned int> &indBuf = shapes[0].mesh.indices;
    glGenBuffers(1, &indBufObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);
    
    // Unbind the arrays
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GLSL::checkVersion();
    assert(glGetError() == GL_NO_ERROR);
    
    
    
    theta = 0;
}

bool installShaders(const string &vShaderName, const string &fShaderName)
{
    GLint rc;
    
    // Create shader handles
    GLuint VS = glCreateShader(GL_VERTEX_SHADER);
    GLuint FS = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Read shader sources
    const char *vshader = GLSL::textFileRead(vShaderName.c_str());
    const char *fshader = GLSL::textFileRead(fShaderName.c_str());
    glShaderSource(VS, 1, &vshader, NULL);
    glShaderSource(FS, 1, &fshader, NULL);
    
    // Compile vertex shader
    glCompileShader(VS);
    GLSL::printError();
    glGetShaderiv(VS, GL_COMPILE_STATUS, &rc);
    GLSL::printShaderInfoLog(VS);
    if(!rc) {
        printf("Error compiling vertex shader %s\n", vShaderName.c_str());
        return false;
    }
    
    // Compile fragment shader
    glCompileShader(FS);
    GLSL::printError();
    glGetShaderiv(FS, GL_COMPILE_STATUS, &rc);
    GLSL::printShaderInfoLog(FS);
    if(!rc) {
        printf("Error compiling fragment shader %s\n", fShaderName.c_str());
        return false;
    }
    
    // Create the program and link
    prog = glCreateProgram();
    glAttachShader(prog, VS);
    glAttachShader(prog, FS);
    glLinkProgram(prog);
    GLSL::printError();
    glGetProgramiv(prog, GL_LINK_STATUS, &rc);
    GLSL::printProgramInfoLog(prog);
    if(!rc) {
        printf("Error linking shaders %s and %s\n", vShaderName.c_str(), fShaderName.c_str());
        return false;
    }
    
    // Set up the shader variables
    aPos = GLSL::getAttribLocation(prog, "aPos");
    aNor = GLSL::getAttribLocation(prog, "aNor");
    uMV = GLSL::getUniformLocation(prog, "MV");
    uP = GLSL::getUniformLocation(prog, "P");
    
    assert(glGetError() == GL_NO_ERROR);
    return true;
}


void drawGL()
{
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use our GLSL program
    glUseProgram(prog);
    
    // Enable and bind position array for drawing
    GLSL::enableVertexAttribArray(aPos);
    glBindBuffer(GL_ARRAY_BUFFER, posBufObj);
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Enable and bind normal array for drawing
    GLSL::enableVertexAttribArray(aNor);
    glBindBuffer(GL_ARRAY_BUFFER, norBufObj);
    glVertexAttribPointer(aNor, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Bind index array for drawing
    int nIndices = (int)shapes[0].mesh.indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObj);
    
    // Compute and send the projection matrix - leave this as is
    glm::mat4 Projection = glm::perspective(80.0f, (float)g_width/g_height, 0.1f, 100.f);
    glUniformMatrix4fv(uP, 1, GL_FALSE, glm::value_ptr(Projection));
    
    initHelper();
    
    float maxTheta = 315;
    float minTheta = 40 + 360;
    
    float minBodyBob = -0.5;
    float maxBodyBob = 0.5;
    
    float minBodyRot = 25;
    float maxBodyRot = 65;
    
    float minLegRot = 15;
    float maxLegRot = 55;
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        theta += 0.1;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        theta -= 0.1;
    }
    
    float armRot = (sin(theta) + 1.0) / 2;    // Value is now between 0 and 1
    armRot *= (maxTheta - minTheta);                     // Value now has the correct range, but needs a little offset
    armRot += minTheta;
    
    float bodyBob = (sin(theta * 2) + 1.0) / 2;    // Value is now between 0 and 1
    bodyBob *= (minBodyBob - maxBodyBob);                     // Value now has the correct range, but needs a little offset
    bodyBob += minBodyBob;
    
    
    float bodyRot = (sin(theta) + 1.0) / 2;    // Value is now between 0 and 1
    bodyRot *= (minBodyRot - maxBodyRot);                     // Value now has the correct range, but needs a little offset
    bodyRot += minBodyRot;
    
    float legRot = (sin(theta * 6) + 1.0) / 2;    // Value is now between 0 and 1
    legRot *= (minLegRot - maxLegRot);                     // Value now has the correct range, but needs a little offset
    legRot += minLegRot;
    

    
    
    
    rightForeArm->rotZ = armRot;
    rightMainArm->rotZ = armRot;
    
    leftForeArm->rotZ = armRot;
    leftMainArm->rotZ = armRot;
    
    leftForeArm->rotX = theta * .8;
    rightForeArm->rotX = theta * .8;
    
    leftLeg->rotZ = legRot;
    rightLeg->rotZ = -legRot;
    
    bodyNode->posY = bodyBob;
    bodyNode->rotZ = bodyRot;
    bodyNode->posX = -theta * .8;
    
    head->rotY = theta * 80;
    
    
    bodyNode->draw(uMV, nIndices);
    
    // Disable and unbind
    GLSL::disableVertexAttribArray(aPos);
    GLSL::disableVertexAttribArray(aNor);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
    assert(glGetError() == GL_NO_ERROR);
    
}

void reshapeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    g_width = w;
    g_height = h;
}


int main(int argc, char **argv)
{
    
    // Initialise GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    g_width = 1024;
    g_height = 768;
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( g_width, g_height, "lab 6 - HM", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Ensure we can capture the escape key being pressed below
//    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    loadShapes("cube.obj");
    
    std::cout << " loaded the object " << endl;
    
    // Initialize glad
    if (!gladLoadGL()) {
        fprintf(stderr, "Unable to initialize glad");
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    
    initGL();
    installShaders("vert.glsl", "frag.glsl");
    
    do{
        drawGL();
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
