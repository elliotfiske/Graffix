//
// Shinjiro Sueda
// modified ZJ Wood January 2015 - conversion to glfw
// October, 2014
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
GLint uShapeID = 0;

int DEBUG = 0;
int width = 1;
int height = 1;

float cameraAngle = 0;

void loadShapes(const string &objFile)
{
    string err = tinyobj::LoadObj(shapes, materials, objFile.c_str());
    if(!err.empty()) {
        cerr << err << endl;
    }
}

void initGL()
{
    // Set the background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Enable Z-buffer test
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
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
    uShapeID = GLSL::getUniformLocation(prog, "shapeID");
    
    assert(glGetError() == GL_NO_ERROR);
    return true;
}

void printMat(float *A, const char *name = 0)
{
    // OpenGL uses col-major ordering:
    // [ 0  4  8 12]
    // [ 1  5  9 13]
    // [ 2  6 10 14]
    // [ 3  7 11 15]
    // The (i,j)th element is A[i+4*j].
    if(name) {
        printf("%s=[\n", name);
    }
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            printf("%- 5.2f ", A[i+4*j]);
        }
        printf("\n");
    }
    if(name) {
        printf("];");
    }
    printf("\n");
}

#define MATRIX_SIZE 4

/** Fills up a 4 by 4 matrix with lovely 0's */
void createMatZeroes(float *mat) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            *mat++ = 0.0f;
        }
    }
}

/** Quick access to the [i, j]th element in the matrix */
float getMat(int i, int j, float *mat) {
    return mat[i + MATRIX_SIZE*j];
}

/** Const? Whatever, man. */
float getMat(int i, int j, const float *mat) {
    return mat[i + MATRIX_SIZE*j];
}

/** Handily set the [i, j]th element in the matrix */
void setMat(int i, int j, float *mat, float value) {
    mat[i + MATRIX_SIZE*j] = value;
}

void createIdentityMat(float *M)
{
    createMatZeroes(M);
    
    setMat(0, 0, M, 1);
    setMat(1, 1, M, 1);
    setMat(2, 2, M, 1);
    setMat(3, 3, M, 1);
}

void createTranslateMat(float *T, float x, float y, float z)
{
    createIdentityMat(T);
    setMat(0, 3, T, x);
    setMat(1, 3, T, y);
    setMat(2, 3, T, z);
}

void createScaleMat(float *S, float x, float y, float z)
{
    createIdentityMat(S);
    setMat(0, 0, S, x);
    setMat(1, 1, S, y);
    setMat(2, 2, S, z);
}

void createRotateMatX(float *R, float radians)
{
    createIdentityMat(R);
    float sinR = sin(radians);
    float cosR = cos(radians);
    
    setMat(1, 1, R,  cosR);
    setMat(1, 2, R, -sinR);
    setMat(2, 1, R,  sinR);
    setMat(2, 2, R,  cosR);
}

void createRotateMatY(float *R, float radians)
{
    createIdentityMat(R);
    float sinR = sin(radians);
    float cosR = cos(radians);
    
    setMat(0, 0, R,  cosR);
    setMat(2, 0, R, -sinR);
    setMat(0, 2, R,  sinR);
    setMat(2, 2, R,  cosR);
}

void createRotateMatZ(float *R, float radians)
{
    createIdentityMat(R);
    float sinR = sin(radians);
    float cosR = cos(radians);
    
    setMat(0, 0, R,  cosR);
    setMat(0, 1, R, -sinR);
    setMat(1, 0, R,  sinR);
    setMat(1, 1, R,  cosR);
}


void multMat(float *C, const float *A, const float *B)
{
    float c = 0;
    for(int k = 0; k < 4; ++k) {
        // Process kth column of C
        for(int i = 0; i < 4; ++i) {
            // Process ith row of C.
            // The (i,k)th element of C is the dot product
            // of the ith row of A and kth col of B.
            c = 0;
            //vector dot
            for(int j = 0; j < 4; ++j) {
                // Grab what we need from A
                float a = getMat(i, j, A);
                
                // Grab what we need from B
                float b = getMat(j, k, B);
                
                c += a*b;
            }
            
            setMat(i, k, C, c);
        }
    }
}


// NOTE: Scales, then rotates, then translates.
void makeCube(float *MAT, float tX, float tY, float tZ, float rX, float rY, float rZ, float sX, float sY, float sZ) {
    createIdentityMat(MAT);
    
    float OTHER[16] = {0};
    
    float T[16] = {0};
    float RX[16] = {0};
    float RY[16] = {0};
    float RZ[16] = {0};
    float R_CAM[16] = {0};
    
    float S[16] = {0};
    
    createTranslateMat(T, tX, tY, tZ);
    createRotateMatX(RX, rX);
    createRotateMatY(RY, rY);
    createRotateMatZ(RZ, rZ);
    
    createRotateMatY(R_CAM, cameraAngle);
    
    createScaleMat(S, sX, sY, sZ);
    
    
    multMat(MAT,    R_CAM, T); // Translate last
    multMat(OTHER, MAT, RX);
    multMat(MAT, OTHER, RZ);
    multMat(OTHER, MAT, RY);
    
    multMat(MAT, OTHER, S); // Camera last
}

void createPerspectiveMat(float *m, float fovy, float aspect, float zNear, float zFar)
{
    // http://www-01.ibm.com/support/knowledgecenter/ssw_aix_61/com.ibm.aix.opengl/doc/openglrf/gluPerspective.htm%23b5c8872587rree
    float f = 1.0f/tan(0.5f*fovy);
    m[ 0] = f/aspect;
    m[ 1] = 0.0f;
    m[ 2] = 0.0f;
    m[ 3] = 0.0f;
    m[ 4] = 0;
    m[ 5] = f;
    m[ 6] = 0.0f;
    m[ 7] = 0.0f;
    m[ 8] = 0.0f;
    m[ 9] = 0.0f;
    m[10] = (zFar + zNear)/(zNear - zFar);
    m[11] = -1.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 2.0f*zFar*zNear/(zNear - zFar);
    m[15] = 0.0f;
}

void drawGL()
{
    
    float PI = M_PI;
    
    
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
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraAngle += 0.1;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraAngle -= 0.1;
    }
    
    // Compute and send the projection matrix
    float Pin[16];
    createPerspectiveMat(Pin, 45.0f, (float)width/height, 0.01f, 100.0f);
    
    float T[16];
    makeCube(T, 0, 0, -6, 0, 0, 0, 1, 1, 1);
    
    float P[16];
    multMat(P, Pin, T);
    
    glUniformMatrix4fv(uP, 1, GL_FALSE, P);
    
    if (DEBUG) {
        float A[16], B[16], C[16];
        for(int i = 0; i < 16; ++i) { A[i] = i; }
        for(int i = 0; i < 16; ++i) { B[i] = i*i; }
        multMat(C, A, B);
        printMat(A, "A");
        printMat(B, "B");
        printMat(C, "C");
    }
    
    float MV[16] = {0};
    
    makeCube(MV, 0, 0, 0, 0, 0, 0, 0.3, 0.3, 0.3);
    glUniformMatrix4fv(uMV, 1, GL_FALSE, MV);
    glUniform1i(uShapeID, 0);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
    
    
    makeCube(MV, 0, 0, 0, 0, 0, 0, 0.04, 0.04, 0.04f );
    glUniformMatrix4fv(uMV, 1, GL_FALSE, MV);
    glUniform1i(uShapeID, 1);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
    
    
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
    width = w;
    height = h;
}


int main(int argc, char **argv)
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 768, 768, "lab 5 - object", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
//    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    loadShapes("dude.obj");
    initGL();
    installShaders("vert.glsl", "frag.glsl");
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
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
