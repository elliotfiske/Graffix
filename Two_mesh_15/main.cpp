//  
//example code to draw ground and bunny - ZJ Wood
//

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>
#include "GLSL.h"
#include "tiny_obj_loader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" //perspective, trans etc
#include "glm/gtc/type_ptr.hpp" //value_ptr

GLFWwindow* window;
using namespace std;
using namespace glm;

vector<tinyobj::shape_t> bunny;
vector<tinyobj::shape_t> hand;
vector<tinyobj::shape_t> finger;
vector<tinyobj::material_t> materials;

int g_SM = 1;
int g_width;
int g_height;
float g_Camtrans = -2.5;
float cam_phi = 0;
float cam_theta = 0;

glm::vec3 g_light(0, 2, 0);
glm::vec3 camLocation = glm::vec3(0.0f, 0, 0);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0);
glm::vec3 lookPoint = glm::vec3(0.0f, 0, 0.0f);
const float WALK_SPEED = 0.5;

GLuint ShadeProg;

GLuint posBufObjB = 0;
GLuint norBufObjB = 0;
GLuint indBufObjB = 0;

GLuint posBufObjH = 0;
GLuint norBufObjH = 0;
GLuint indBufObjH = 0;


GLuint posBufObjF = 0;
GLuint norBufObjF = 0;
GLuint indBufObjF = 0;

GLuint posBufObjG = 0;
GLuint norBufObjG = 0;

//Handles to the shader data
GLint h_aPosition;
GLint h_aNormal;
GLint h_uModelMatrix;
GLint h_uViewMatrix;
GLint h_uProjMatrix;
GLint h_uLightPos;
GLint h_uMatAmb, h_uMatDif, h_uMatSpec, h_uMatShine;
GLint h_uShadeM;


int printOglError (const char *file, int line) {
   /* Returns 1 if an OpenGL error occurred, 0 otherwise. */
   GLenum glErr;
   int    retCode = 0;
  
   glErr = glGetError ();
   while (glErr != GL_NO_ERROR)
    {
      printf ("glError in file %s @ line %d: %s\n", file, line, gluErrorString (glErr));
      retCode = 1;
      glErr = glGetError ();
    }
   return retCode;
}

inline void safe_glUniformMatrix4fv(const GLint handle, const GLfloat data[]) {
  if (handle >= 0)
    glUniformMatrix4fv(handle, 1, GL_FALSE, data);
}

void SetMaterial(int i) {
    
    glUseProgram(ShadeProg);
    switch (i) {
        case 0: //shiny blue plastic
            glUniform3f(h_uMatAmb, 0.04, 0.02, 0.2);
            glUniform3f(h_uMatDif, 0.9, 0.16, 0.0);
            glUniform3f(h_uMatSpec, 0.14, 0.2, 0.8);
            glUniform1f(h_uMatShine, 120.0);
            break;
        case 1: // flat red
            glUniform3f(h_uMatAmb, 1, .1, .1);
            glUniform3f(h_uMatDif, 1, .1, .1);
            glUniform3f(h_uMatSpec, 1, .1, .1);
            glUniform1f(h_uMatShine, 4.0);
            break;
        case 2: //gold
            glUniform3f(h_uMatAmb, 0.09, 0.07, 0.08);
            glUniform3f(h_uMatDif, 0.91, 0.782, 0.82);
            glUniform3f(h_uMatSpec, 1.0, 0.913, 0.8);
            glUniform1f(h_uMatShine, 200.0);
            break;
        case 3: //gold
            glUniform3f(h_uMatAmb, 0.09, 0.07, 0.08);
            glUniform3f(h_uMatDif, 0.91, 0.2, 0.91);
            glUniform3f(h_uMatSpec, 1.0, 0.7, 1.0);
            glUniform1f(h_uMatShine, 100.0);
            break;
        case 4: // black
            glUniform3f(h_uMatAmb, 0.08, 0.08, 0.08);
            glUniform3f(h_uMatDif, 0.08, 0.08, 0.08);
            glUniform3f(h_uMatSpec, 0.08, 0.08, 0.08);
            glUniform1f(h_uMatShine, 10.0);
            break;
        case 5: //spooky material
            glUniform3f(h_uMatAmb, 0.09, 0.07, 0.08);
            glUniform3f(h_uMatDif, 0.2, 0.2, 0.2);
            glUniform3f(h_uMatSpec, 1, .1, .1);
            glUniform1f(h_uMatShine, 100.0);
            break;
    }
}

/* projection matrix */
void SetProjectionMatrix() {
  glm::mat4 Projection = glm::perspective(50.0f, (float)g_width/g_height, 0.1f, 100.f);
  safe_glUniformMatrix4fv(h_uProjMatrix, glm::value_ptr(Projection));
}

/* camera controls - do not change */
void SetView() {
    float lookX = cos(cam_phi) * cos(cam_theta); // change to THETA
    float lookY = sin(cam_phi);
    float lookZ = cos(cam_phi) * cos(90 - cam_theta);
    
    lookPoint = glm::vec3(lookX, lookY, lookZ);
    
    glm::mat4 CamProject = glm::lookAt(camLocation, camLocation + lookPoint, cameraUp);
    
    safe_glUniformMatrix4fv(h_uViewMatrix, glm::value_ptr(CamProject));
}

/* model transforms */
glm::mat4 handTransform;
void SetModel(vec3 trans, float rotX, float rotZ, float sc) {
    glm::mat4 Trans = glm::translate( glm::mat4(1.0f), trans);
    glm::mat4 RotateX = glm::rotate( glm::mat4(1.0f), rotX, glm::vec3(1.0f, 0.0f, 0));
    glm::mat4 RotateZ = glm::rotate( glm::mat4(1.0f), rotZ, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Sc = glm::scale( glm::mat4(1.0f), vec3(sc));
    glm::mat4 com = Trans*RotateX*RotateZ*Sc;
    safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(com));
    handTransform = com;
}

//Given a vector of shapes which has already been read from an obj file
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
   float maxExtent, xExtent, yExtent, zExtent;
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
    scaleX = 2.0 /maxExtent;
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



void loadShapes(const string &objFile, std::vector<tinyobj::shape_t>& shapes)
{
	string err = tinyobj::LoadObj(shapes, materials, objFile.c_str());
	if(!err.empty()) {
		cerr << err << endl;
	}
   resize_obj(shapes);
}

void initBunny(std::vector<tinyobj::shape_t>& shape) {
    
    // Send the position array to the GPU
    const vector<float> &posBuf = shape[0].mesh.positions;
    glGenBuffers(1, &posBufObjB);
    glBindBuffer(GL_ARRAY_BUFFER, posBufObjB);
    glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
    
    // Send the normal array to the GPU
    vector<float> norBuf;
    glm::vec3 v1, v2, v3;
    glm::vec3 edge1, edge2, norm;
    int idx1, idx2, idx3;
    //for every vertex initialize the vertex normal to 0
    for (int j = 0; j < shape[0].mesh.positions.size()/3; j++) {
        norBuf.push_back(0);
        norBuf.push_back(0);
        norBuf.push_back(0);
    }
    //process the mesh and compute the normals - for every face
    //add its normal to its associated vertex
    for (int i = 0; i < shape[0].mesh.indices.size()/3; i++) {
        idx1 = shape[0].mesh.indices[3*i+0];
        idx2 = shape[0].mesh.indices[3*i+1];
        idx3 = shape[0].mesh.indices[3*i+2];
        v1 = glm::vec3(shape[0].mesh.positions[3*idx1 +0],shape[0].mesh.positions[3*idx1 +1], shape[0].mesh.positions[3*idx1 +2]);
        v2 = glm::vec3(shape[0].mesh.positions[3*idx2 +0],shape[0].mesh.positions[3*idx2 +1], shape[0].mesh.positions[3*idx2 +2]);
        v3 = glm::vec3(shape[0].mesh.positions[3*idx3 +0],shape[0].mesh.positions[3*idx3 +1], shape[0].mesh.positions[3*idx3 +2]);
        edge1 = v2 - v1;
        edge2 = v3 - v1;
        norm = glm::cross(edge1, edge2);
        norBuf[3*idx1+0] += (norm.x);
        norBuf[3*idx1+1] += (norm.y);
        norBuf[3*idx1+2] += (norm.z);
        norBuf[3*idx2+0] += (norm.x);
        norBuf[3*idx2+1] += (norm.y);
        norBuf[3*idx2+2] += (norm.z);
        norBuf[3*idx3+0] += (norm.x);
        norBuf[3*idx3+1] += (norm.y);
        norBuf[3*idx3+2] += (norm.z);
    }
    glGenBuffers(1, &norBufObjB);
    glBindBuffer(GL_ARRAY_BUFFER, norBufObjB);
    glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
    
    // Send the index array to the GPU
    const vector<unsigned int> &indBuf = shape[0].mesh.indices;
    glGenBuffers(1, &indBufObjB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);
    
    // Unbind the arrays
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GLSL::checkVersion();
    assert(glGetError() == GL_NO_ERROR);
}


void initHand(std::vector<tinyobj::shape_t>& shape) {

	// Send the position array to the GPU
	const vector<float> &posBuf = shape[0].mesh.positions;
	glGenBuffers(1, &posBufObjH);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObjH);
	glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
	
	// Send the normal array to the GPU
	vector<float> norBuf;
   glm::vec3 v1, v2, v3;
   glm::vec3 edge1, edge2, norm;
   int idx1, idx2, idx3;
   //for every vertex initialize the vertex normal to 0
   for (int j = 0; j < shape[0].mesh.positions.size()/3; j++) {
      norBuf.push_back(0);
      norBuf.push_back(0);
      norBuf.push_back(0);
   }
   //process the mesh and compute the normals - for every face
   //add its normal to its associated vertex
   for (int i = 0; i < shape[0].mesh.indices.size()/3; i++) {
      idx1 = shape[0].mesh.indices[3*i+0];
      idx2 = shape[0].mesh.indices[3*i+1];
      idx3 = shape[0].mesh.indices[3*i+2];
      v1 = glm::vec3(shape[0].mesh.positions[3*idx1 +0],shape[0].mesh.positions[3*idx1 +1], shape[0].mesh.positions[3*idx1 +2]);
      v2 = glm::vec3(shape[0].mesh.positions[3*idx2 +0],shape[0].mesh.positions[3*idx2 +1], shape[0].mesh.positions[3*idx2 +2]);
      v3 = glm::vec3(shape[0].mesh.positions[3*idx3 +0],shape[0].mesh.positions[3*idx3 +1], shape[0].mesh.positions[3*idx3 +2]);
      edge1 = v2 - v1;
      edge2 = v3 - v1;
      norm = glm::cross(edge1, edge2);
      norBuf[3*idx1+0] += (norm.x);
      norBuf[3*idx1+1] += (norm.y);
      norBuf[3*idx1+2] += (norm.z);
      norBuf[3*idx2+0] += (norm.x);
      norBuf[3*idx2+1] += (norm.y);
      norBuf[3*idx2+2] += (norm.z);
      norBuf[3*idx3+0] += (norm.x);
      norBuf[3*idx3+1] += (norm.y);
      norBuf[3*idx3+2] += (norm.z);
   }
	glGenBuffers(1, &norBufObjH);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObjH);
	glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
	
	// Send the index array to the GPU
	const vector<unsigned int> &indBuf = shape[0].mesh.indices;
	glGenBuffers(1, &indBufObjH);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjH);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);

	// Unbind the arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLSL::checkVersion();
	assert(glGetError() == GL_NO_ERROR);
}


void initFinger(std::vector<tinyobj::shape_t>& shape) {
    
    // Send the position array to the GPU
    const vector<float> &posBuf = shape[0].mesh.positions;
    glGenBuffers(1, &posBufObjF);
    glBindBuffer(GL_ARRAY_BUFFER, posBufObjF);
    glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
    
    // Send the normal array to the GPU
    vector<float> norBuf;
    glm::vec3 v1, v2, v3;
    glm::vec3 edge1, edge2, norm;
    int idx1, idx2, idx3;
    //for every vertex initialize the vertex normal to 0
    for (int j = 0; j < shape[0].mesh.positions.size()/3; j++) {
        norBuf.push_back(0);
        norBuf.push_back(0);
        norBuf.push_back(0);
    }
    //process the mesh and compute the normals - for every face
    //add its normal to its associated vertex
    for (int i = 0; i < shape[0].mesh.indices.size()/3; i++) {
        idx1 = shape[0].mesh.indices[3*i+0];
        idx2 = shape[0].mesh.indices[3*i+1];
        idx3 = shape[0].mesh.indices[3*i+2];
        v1 = glm::vec3(shape[0].mesh.positions[3*idx1 +0],shape[0].mesh.positions[3*idx1 +1], shape[0].mesh.positions[3*idx1 +2]);
        v2 = glm::vec3(shape[0].mesh.positions[3*idx2 +0],shape[0].mesh.positions[3*idx2 +1], shape[0].mesh.positions[3*idx2 +2]);
        v3 = glm::vec3(shape[0].mesh.positions[3*idx3 +0],shape[0].mesh.positions[3*idx3 +1], shape[0].mesh.positions[3*idx3 +2]);
        edge1 = v2 - v1;
        edge2 = v3 - v1;
        norm = glm::cross(edge1, edge2);
        norBuf[3*idx1+0] += (norm.x);
        norBuf[3*idx1+1] += (norm.y);
        norBuf[3*idx1+2] += (norm.z);
        norBuf[3*idx2+0] += (norm.x);
        norBuf[3*idx2+1] += (norm.y);
        norBuf[3*idx2+2] += (norm.z);
        norBuf[3*idx3+0] += (norm.x);
        norBuf[3*idx3+1] += (norm.y);
        norBuf[3*idx3+2] += (norm.z);
    }
    glGenBuffers(1, &norBufObjF);
    glBindBuffer(GL_ARRAY_BUFFER, norBufObjF);
    glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
    
    // Send the index array to the GPU
    const vector<unsigned int> &indBuf = shape[0].mesh.indices;
    glGenBuffers(1, &indBufObjF);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjF);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);
    
    // Unbind the arrays
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GLSL::checkVersion();
    assert(glGetError() == GL_NO_ERROR);
}

void initGround() {

  float G_edge = 20;
  GLfloat g_backgnd_data[] = {
      -G_edge, -1.0f, -G_edge,
        -G_edge,  -1.0f, G_edge,
        G_edge, -1.0f, -G_edge,
        -G_edge,  -1.0f, G_edge,
        G_edge, -1.0f, -G_edge,
        G_edge, -1.0f, G_edge,
  };


  GLfloat nor_Buf_G[] = { 
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
  };

   glGenBuffers(1, &posBufObjG);
   glBindBuffer(GL_ARRAY_BUFFER, posBufObjG);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_backgnd_data), g_backgnd_data, GL_STATIC_DRAW);
	
   glGenBuffers(1, &norBufObjG);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObjG);
	glBufferData(GL_ARRAY_BUFFER, sizeof(nor_Buf_G), nor_Buf_G, GL_STATIC_DRAW);

}

void initGL()
{
	// Set the background color
	glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
	// Enable Z-buffer test
	glEnable(GL_DEPTH_TEST);
   glPointSize(18);

   initHand(hand);
    initFinger(finger);
    initBunny(bunny);
   initGround();
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
   std::cout << "just compiled the v shader" << std::endl;
   printOglError(__FILE__, __LINE__);
	GLSL::printError();
	glGetShaderiv(VS, GL_COMPILE_STATUS, &rc);
	GLSL::printShaderInfoLog(VS);
	if(!rc) {
		printf("Error compiling vertex shader %s\n", vShaderName.c_str());
		return false;
	}
	
	// Compile fragment shader
	glCompileShader(FS);
   std::cout << "just compiled the f shader" << std::endl;
	GLSL::printError();
	glGetShaderiv(FS, GL_COMPILE_STATUS, &rc);
	GLSL::printShaderInfoLog(FS);
	if(!rc) {
		printf("Error compiling fragment shader %s\n", fShaderName.c_str());
		return false;
	}
	
	// Create the program and link
	   ShadeProg = glCreateProgram();
	   glAttachShader(ShadeProg, VS);
	   glAttachShader(ShadeProg, FS);
	   glLinkProgram(ShadeProg);
      std::cout << "just linked the shaders" << std::endl;
   
	   GLSL::printError();
	   glGetProgramiv(ShadeProg, GL_LINK_STATUS, &rc);
	   GLSL::printProgramInfoLog(ShadeProg);
	   if(!rc) {
		   printf("Error linking shaders %s and %s\n", vShaderName.c_str(), fShaderName.c_str());
		   return false;
	   }

   /* get handles to attribute data */
    h_aPosition = GLSL::getAttribLocation(ShadeProg, "aPosition");
    h_aNormal = GLSL::getAttribLocation(ShadeProg, "aNormal");
    h_uProjMatrix = GLSL::getUniformLocation(ShadeProg, "uProjMatrix");
    h_uViewMatrix = GLSL::getUniformLocation(ShadeProg, "uViewMatrix");
    h_uModelMatrix = GLSL::getUniformLocation(ShadeProg, "uModelMatrix");
//    h_uLightPos = GLSL::getUniformLocation(ShadeProg, "uLightPos");
    h_uMatAmb = GLSL::getUniformLocation(ShadeProg, "UaColor");
    h_uMatDif = GLSL::getUniformLocation(ShadeProg, "UdColor");
    h_uMatSpec = GLSL::getUniformLocation(ShadeProg, "UsColor");
    h_uMatShine = GLSL::getUniformLocation(ShadeProg, "Ushine");
    h_uShadeM = GLSL::getUniformLocation(ShadeProg, "shade");
	
	assert(glGetError() == GL_NO_ERROR);
	return true;
}

void drawHand(float x, float y, float z, float xRot, float zRot, float scale) {
    //draw the hand
    int nIndices = (int)hand[0].mesh.indices.size();
    SetModel(vec3(x, y, z), xRot, zRot, scale);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
}

void drawBunny(float x, float y, float z, float xRot, float zRot, float scale) {
    //draw the hand
    int nIndices = (int)bunny[0].mesh.indices.size();
    SetModel(vec3(x, y, z), xRot, zRot, scale);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
}

float fingerRotator = 0;
void drawFingers(float x, float y, float z, float xRot, float zRot, float scale) {
    int nIndices = (int)finger[0].mesh.indices.size();
    SetModel(vec3(x, y, z), xRot, zRot, scale);
    
    float fingerRot = 0;
    
    // POINTER
    fingerRot = sin(fingerRotator) * 10;
    glm::mat4 fInitTrans = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 fTrans = glm::translate( glm::mat4(1.0f), glm::vec3(0.1f, 0.16f, -0.6f));
    glm::mat4 fRotateX = glm::rotate( glm::mat4(1.0f), fingerRot, glm::vec3(1.0f, 0.0f, 0));
    glm::mat4 fSc = glm::scale( glm::mat4(1.0f), vec3(0.5));
    
    glm::mat4 fingerTransform = handTransform * fTrans * fRotateX * fSc * fInitTrans;
    safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(fingerTransform));
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
    
    
    // MIDDLE
    fingerRot = sin(fingerRotator + 20) * 10;
    fInitTrans = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    fTrans = glm::translate( glm::mat4(1.0f), glm::vec3(-0.15f, 0.16f, -0.6f));
    fRotateX = glm::rotate( glm::mat4(1.0f), fingerRot, glm::vec3(1.0f, 0.0f, 0));
    fSc = glm::scale( glm::mat4(1.0f), vec3(0.5));
    
    fingerTransform = handTransform * fTrans * fRotateX * fSc * fInitTrans;
    safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(fingerTransform));
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
    
    // ring
    fingerRot = sin(fingerRotator + 40) * 10;
    fInitTrans = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    fTrans = glm::translate( glm::mat4(1.0f), glm::vec3(-0.43f, 0.16f, -0.4f));
    fRotateX = glm::rotate( glm::mat4(1.0f), fingerRot, glm::vec3(1.0f, 0.0f, 0));
    fSc = glm::scale( glm::mat4(1.0f), vec3(0.5));
    
    fingerTransform = handTransform * fTrans * fRotateX * fSc * fInitTrans;
    safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(fingerTransform));
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
    
    // pinky
    fingerRot = sin(fingerRotator + 60) * 10;
    fInitTrans = glm::translate( glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    fTrans = glm::translate( glm::mat4(1.0f), glm::vec3(-0.72f, 0.16f, -0.2f));
    fRotateX = glm::rotate( glm::mat4(1.0f), fingerRot, glm::vec3(1.0f, 0.0f, 0));
    fSc = glm::scale( glm::mat4(1.0f), vec3(0.5));
    
    fingerTransform = handTransform * fTrans * fRotateX * fSc * fInitTrans;
    safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(fingerTransform));
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
}

float wave = 0;
void drawGL()
{
    fingerRotator += 0.1;
    wave += 0.08;
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Use our GLSL program
	glUseProgram(ShadeProg);
   glUniform3f(h_uLightPos, g_light.x, g_light.y, g_light.z);
   glUniform1i(h_uShadeM, 0);

   SetProjectionMatrix();
   SetView();


	// Enable and bind position array for drawing
	GLSL::enableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, posBufObjH);
	glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Enable and bind normal array for drawing
	GLSL::enableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObjH);
	glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// Bind index array for drawing
	int nIndices = (int)hand[0].mesh.indices.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjH);

    //draw the hand
    SetMaterial(5);
    float handWave = sin(wave) * 50;
    drawHand(0.0, 0.0, -5.0, 0.0, 0.0, 1.0);
    drawHand(5.0, 3.0, 0.0, 0.0, 0.0, 1.0);
    drawHand(0.0, 3.0, 0.0, 0.0, 180.0, 2.0);
    drawHand(5.0, 0.0, 10.0, 80.0, handWave, 1.0);
    drawHand(15.0, 3.0, 4.0, 180.0, 0.0, 0.5);
    drawHand(-10.0, 1.0, -8.0, 0.0, -handWave, 1.0);
    drawHand(0.0, 40.0, -40.0, 270.0, handWave / 3.0, 30.0);

   GLSL::disableVertexAttribArray(h_aPosition);
	GLSL::disableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    /******     FINGERS      ****/
    // Enable and bind position array for drawing
    GLSL::enableVertexAttribArray(h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, posBufObjF);
    glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Enable and bind normal array for drawing
    GLSL::enableVertexAttribArray(h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, norBufObjF);
    glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Bind index array for drawing
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjF);
    
    //draw the fingers
    drawFingers(0.0, 0.0, -5.0, 0.0, 0.0, 1.0);
    drawFingers(5.0, 3.0, 0.0, 0.0, 0.0, 1.0);
    drawFingers(0.0, 3.0, 0.0, 0.0, 180.0, 2.0);
    drawFingers(5.0, 0.0, 10.0, 80.0, handWave, 1.0);
    drawFingers(15.0, 3.0, 4.0, 180.0, 0.0, 0.5);
    drawFingers(-10.0, 1.0, -8.0, 0.0, -handWave, 1.0);
    drawFingers(0.0, 40.0, -40.0, 270.0, handWave / 3.0, 30.0);
    
    GLSL::disableVertexAttribArray(h_aPosition);
    GLSL::disableVertexAttribArray(h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    
    /****  BUNNY   ***/
    // Enable and bind position array for drawing
    GLSL::enableVertexAttribArray(h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, posBufObjB);
    glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Enable and bind normal array for drawing
    GLSL::enableVertexAttribArray(h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, norBufObjB);
    glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Bind index array for drawing
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBufObjB);
    
    //draw the bunnies
   glUniform1i(h_uShadeM, 1);
    SetMaterial(1);
    drawBunny(5.0, 60.0, 60.0, handWave/10, handWave/10, 40); // GOD BUNNY
    SetMaterial(2);
    drawBunny(5.0, 0.0, 5.0, 38, 0, 1);
    drawBunny(-10.0, 0.0, 9.0, 0, 90, 0.5);
    drawBunny(5.0, 3.0, 5.0, 19, 0, 1);
    SetMaterial(3);
    drawBunny(-15.0, 0.0, 5.0, 0, 90, 1);
    drawBunny(-5.0, 0.0, 15.0, 0, 90, 1);
    drawBunny(5.0, 0.0, -8.0, 0, 0, 2);
    drawBunny(25.0, 5.0, 5.0, 270, 90, 3);
    SetMaterial(4);
    drawBunny(-8.0, 0.0, 5.0, 0, 0, 1);
    drawBunny(5.0, 0.0, -5.0, 180, 0, 1);
    drawBunny(5.0, 0.0, -15.0, 270, 0, 1);
    
    GLSL::disableVertexAttribArray(h_aPosition);
    GLSL::disableVertexAttribArray(h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    
    
    
    

   SetMaterial(0);
   SetModel(vec3(0), 0, 0, 1);
   //draw the ground
   glEnableVertexAttribArray(h_aPosition);
   glBindBuffer(GL_ARRAY_BUFFER, posBufObjG);
   glVertexAttribPointer( h_aPosition, 3,  GL_FLOAT, GL_FALSE, 0, (void*)0);
	GLSL::enableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, norBufObjG);
	glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

   glDrawArrays(GL_TRIANGLES, 0, 6);

   GLSL::disableVertexAttribArray(h_aPosition);
	GLSL::disableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glUseProgram(0);
    int error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error is: %s\n", gluErrorString(error));
//                assert(false);
    }
}

void window_size_callback(GLFWwindow* window, int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	g_width = w;
	g_height = h;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    glm::vec3 translation = glm::vec3(0, 0, 0);
    glm::vec3 strafe = glm::normalize(glm::cross(lookPoint, cameraUp));
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        translation = -strafe * WALK_SPEED;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        translation =  strafe * WALK_SPEED;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        translation = glm::normalize(lookPoint) * WALK_SPEED;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        translation = -glm::normalize(lookPoint) * WALK_SPEED;
    
    camLocation += translation;
}

float clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    cam_theta += xOffset / 5;
    
    cam_phi   += yOffset / 5;
    cam_phi = clip(cam_phi, - M_PI_2 + 0.6, M_PI_2 - 0.6);
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

    // Open a window and create its OpenGL context
   g_width = 1024;
   g_height = 768;
   window = glfwCreateWindow( g_width, g_height, "bunny and ground", NULL, NULL);
   if( window == NULL ){
      fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // Initialize GLEW
   if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
   }

   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 loadShapes("hand-nf.obj", hand);
    loadShapes("finger.obj", finger);
    loadShapes("bunny.obj", bunny);
	 initGL();
	 installShaders("vert.glsl", "frag.glsl");

	glClearColor(0.1f, 0.3f, 0.1f, 1.0f);

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
