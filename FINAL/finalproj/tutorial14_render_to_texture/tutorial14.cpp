// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
using namespace std;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

int vertexPosition_modelspaceID;
int vertexNormal_modelspaceID;
GLuint diffuseMatID;
GLuint shininessID;
GLuint ambientID;
GLuint collectibleID;

/** Defines everything we need to make the model matrix */
typedef struct model_pos {
    float x, y, z;
    float rx, ry, rz;
} ModelPos;

// Matrices
GLuint MatrixID;
GLuint ModelMatrixID;
GLuint ViewMatrixID;
int timeTicks = 0;

vector<tinyobj::material_t> materials;

void loadPoints(GLuint *posBufID) {
    // Send the position array to the GPU
    static GLfloat g_point_buffer_data[3] = {0.1, 0.2, -0.3};
    glGenBuffers(1, posBufID);
    glBindBuffer(GL_ARRAY_BUFFER, *posBufID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_point_buffer_data), g_point_buffer_data, GL_STATIC_DRAW);
    
    // Unbind the arrays
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

void loadShapes(const string &objFile, std::vector<tinyobj::shape_t>& shapes, GLuint *posBufID, GLuint *norBufID, GLuint *indBufID) {
    string err = tinyobj::LoadObj(shapes, materials, objFile.c_str());
    if(!err.empty()) {
        printf("OBJ error: %s\n", err.c_str());
    }
    
    // Send the position array to the GPU
    const vector<float> &posBuf = shapes[0].mesh.positions;
    glGenBuffers(1, posBufID);
    glBindBuffer(GL_ARRAY_BUFFER, *posBufID);
    glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
    
    // Send the normal array to the GPU
    const vector<float> &norBuf = shapes[0].mesh.normals;
    glGenBuffers(1, norBufID);
    glBindBuffer(GL_ARRAY_BUFFER, *norBufID);
    glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
    
    // Send the index array to the GPU
    const vector<unsigned int> &indBuf = shapes[0].mesh.indices;
    glGenBuffers(1, indBufID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indBufID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size()*sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);
}

void setMaterial(float r, float g, float b, float shininess, float ambient) {
    glUniform3f(diffuseMatID, r, g, b);
    glUniform1f(shininessID, shininess);
    glUniform1f(ambientID, ambient);
}

void drawShapes(std::vector<tinyobj::shape_t> shape, GLuint vertexBuffer, GLuint normalBuffer, GLuint indexBuffer, GLuint numVertices, ModelPos modelPosition) {
    glm::mat4 TransMatrix = glm::translate(glm::mat4(1.0), glm::vec3(modelPosition.x, modelPosition.y, modelPosition.z));
    glm::mat4 XRotMatrix  = glm::rotate(glm::mat4(1.0), modelPosition.rx, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 YRotMatrix  = glm::rotate(glm::mat4(1.0), modelPosition.ry, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 ZRotMatrix  = glm::rotate(glm::mat4(1.0), modelPosition.rz, glm::vec3(0.0, 0.0, 1.0));
    
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = TransMatrix * XRotMatrix * YRotMatrix * ZRotMatrix;
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    
    // 1rst attribute buffer : vertices`1
    glEnableVertexAttribArray(vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
                          vertexPosition_modelspaceID,  // The attribute we want to configure
                          3,                            // size
                          GL_FLOAT,                     // type
                          GL_FALSE,                     // normalized?
                          0,                            // stride
                          (void*)0                      // array buffer offset
                          );
    
    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(vertexNormal_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(
                          vertexNormal_modelspaceID,    // The attribute we want to configure
                          3,                            // size
                          GL_FLOAT,                     // type
                          GL_FALSE,                     // normalized?
                          0,                            // stride
                          (void*)0                      // array buffer offset
                          );
    
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    // Draw the triangles !
    glDrawElements(
                   GL_TRIANGLES,      // mode
                   numVertices*3,    // count
                   GL_UNSIGNED_INT, // type
                   (void*)0           // element array buffer offset
                   );
    
    glDisableVertexAttribArray(vertexPosition_modelspaceID);
    glDisableVertexAttribArray(vertexNormal_modelspaceID);
}

void drawPoint(glm::vec3 point, GLuint posBufID) {
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2, -5));
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    // Tell shader we're drawing points now
    glUniform1i(collectibleID, 1);
    
    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    
    glEnableVertexAttribArray(vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, posBufID);
    glVertexAttribPointer(
                          vertexPosition_modelspaceID, // The attribute we want to configure
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    glDrawArrays(GL_POINTS, 0, 1);
    
    // Tell shader we're done drawing points
    glUniform1i(collectibleID, 0);
}

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 14 - Render To Texture", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
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
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
    
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShadingRTT.vertexshader", "StandardShadingRTT.fragmentshader" );

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
    diffuseMatID = glGetUniformLocation(programID, "diffuse_color");
    shininessID = glGetUniformLocation(programID, "shininess");
    ambientID = glGetUniformLocation(programID, "ambient");
    collectibleID = glGetUniformLocation(programID, "isCollectible");

	// Get a handle for our buffers
	vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// The depth buffer
	if ( !GLEW_ARB_framebuffer_object ){ // OpenGL 2.1 doesn't require this, 3.1+ does
		printf("Your GPU does not provide framebuffer objects. Use a texture instead.");
		return -1;
	}
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    vector<tinyobj::shape_t> slenderFace;
    GLuint pos_slender, nor_slender, ind_slender;
    
    vector<tinyobj::shape_t> shadowMan;
    GLuint pos_shadow, nor_shadow, ind_shadow;
    
    vector<tinyobj::shape_t> sheets;
    GLuint pos_sheets, nor_sheets, ind_sheets;
    
    vector<tinyobj::shape_t> room;
    GLuint pos_room, nor_room, ind_room;
    
    vector<tinyobj::shape_t> door;
    GLuint pos_door, nor_door, ind_door;
    
    vector<tinyobj::shape_t> clockBase;
    GLuint pos_clockB, nor_clockB, ind_clockB;
    
    vector<tinyobj::shape_t> clockFace;
    GLuint pos_clockF, nor_clockF, ind_clockF;
    
    vector<tinyobj::shape_t> clockHand;
    GLuint pos_clockH, nor_clockH, ind_clockH;
    
    vector<tinyobj::shape_t> light;
    GLuint pos_light, nor_light, ind_light;
    
    GLuint pos_collectible;
    
    loadShapes("slenderFace.obj", slenderFace, &pos_slender, &nor_slender, &ind_slender);
//    loadShapes("shadow.obj", shadowMan,    &pos_shadow,  &nor_shadow,  &ind_shadow);
    loadShapes("sheets.obj", sheets,       &pos_sheets,  &nor_sheets,  &ind_sheets);
    loadShapes("room.obj", room,           &pos_room,    &nor_room,    &ind_room);
    loadShapes("door.obj", door,           &pos_door,    &nor_door,    &ind_door);
    loadShapes("clockBody.obj", clockBase, &pos_clockB,  &nor_clockB,  &ind_clockB);
    loadShapes("clockFace.obj", clockFace, &pos_clockF,  &nor_clockF,  &ind_clockF);
    loadShapes("clockHand.obj", clockHand, &pos_clockH,  &nor_clockH,  &ind_clockH);
    loadShapes("light.obj",     light,     &pos_light,   &nor_light,   &ind_light);
    
    
    loadPoints(&pos_collectible);
    
    
	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	static const GLfloat g_quad_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint quad_programID = LoadShaders( "Passthrough.vertexshader", "WobblyTexture.fragmentshader" );
	GLuint quad_vertexPosition_modelspace = glGetAttribLocation(quad_programID, "vertexPosition_modelspace");
	GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
	GLuint timeID = glGetUniformLocation(quad_programID, "time");


    ModelPos baseSlenderModel = { -3, 1.8, -2,
        0, -45, -13  };
    ModelPos slenderModel = baseSlenderModel;
    bool twitching = false;
    
    
    ModelPos roomModel = { 0, 0, 0,
                           0, 0, 0  };
    
    ModelPos sheetModel = {0, 0.3, 0, 0, 0, 0};
    ModelPos doorModel = {0, 0, -46, 0, 0, 0};
    ModelPos shadowModel = {20, 0, -20, 0, 0, 0};
    ModelPos clockModel = {12, -4, 0, 0, 0, 0};
    ModelPos clockFaceModel = {10.1, 6.7, 0, 0, -90, 0};
    ModelPos hourHandModel = {9.9,   6.7, 0, -15, 0, 0};
    ModelPos minuteHandModel = {9.9,   6.7, 0, 0, 0, 0};
    ModelPos lightModel = {0, 0, 0, 0, 0, 0};
    
    
    // Set up scroll wheel and key callbacks in control.cpp
    setUpCallbacks();
	
    int timeToNextTwitch = timeTicks;

    const double minH[3] = {3.123, 2.34,  0};
    const double maxH[3] = {3.159, 2.36,  0};
    const double minV[3] = {0.363, 0.393, 0};
    const double maxV[3] = {0.397, 0.409, 0};
    
    glm::vec3 firstLight = glm::vec3(0, 2, -5); // show it off
    glm::vec3 secondLight = glm::vec3(10, 6, -10); // alleviate stress
    glm::vec3 thirdLight = glm::vec3(-10, 1, -10); // the 'out' from slenderbro -> finished?
    
    const glm::vec3 lol[3] = {firstLight, secondLight, thirdLight};
    const int times[3] = { 300, 500, 10000 };
    int lightNdx = -1;
    
    lightModel.x = 100000000;
    lightModel.y = lol[0].y;
    lightModel.z = lol[0].z;
    
    bool showingLight = false;
    
	do{
        timeTicks++;
        // 60 fps, should take 180 seconds to go 360 degrees
        // 360 degrees / 180 seconds * 1 second / 60 frames = 1/30 = 0.0333
        minuteHandModel.rx += 0.0333;
        
        // 15 degrees / 180 seconds * 1 second / 60 frames = 0.0014
        hourHandModel.rx += 0.0014;

        // see if we should twitch slendy
        if (timeTicks > timeToNextTwitch) {
            if (twitching) {
                slenderModel.rx = baseSlenderModel.rx + (rand() % 50) - 25;
                slenderModel.ry = baseSlenderModel.ry + (rand() % 50) - 25;
                timeToNextTwitch = timeTicks + rand() % 20 + 2;
                twitching = false;
            }
            else {
                slenderModel = baseSlenderModel;
                timeToNextTwitch = timeTicks + rand() % 40 + 10;
                twitching = true;
            }
        }
        
        slenderModel.x += (float) (rand() % 10 / 10.0 * (rand() % 10) / 10.0) / 5.0 - 1.0;
        slenderModel.y += (float) (rand() % 10 / 10.0 * (rand() % 10) / 10.0) / 5.0 - 1.0;
        slenderModel.z += (float) (rand() % 10 / 10.0 * (rand() % 10) / 10.0) / 5.0 - 1.0;
        
        
        
		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();

		glm::vec3 lightPos = glm::vec3(0,0,-14);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

        
        
        setMaterial(1, 1, 1, 1, 0.1);
        drawShapes(slenderFace, pos_slender, nor_slender, ind_slender, slenderFace[0].mesh.indices.size(), slenderModel);
        setMaterial(0.191, 0.211, 0.125, 0.6, 0.7);
        drawShapes(room,        pos_room,    nor_room,    ind_room,    room[0].mesh.indices.size(), roomModel);
        setMaterial(0.292, 0.149, 0.149, 0.1, 0.4);
        drawShapes(sheets,      pos_sheets,  nor_sheets,  ind_sheets,  sheets[0].mesh.indices.size(), sheetModel);
        setMaterial(0.25, 0.13, 0.1, 0.1, 0.4);
        drawShapes(door, pos_door, nor_door, ind_door, door[0].mesh.indices.size(), doorModel);
        setMaterial(0.110, 0.047, 0.02, 0.1, 0.4);
        drawShapes(clockBase, pos_clockB, nor_clockB, ind_clockB, clockBase[0].mesh.indices.size(), clockModel);
        setMaterial(0.8, 0.8, 0.8, 0, 0.7);
        drawShapes(clockFace, pos_clockF, nor_clockF, ind_clockF, clockFace[0].mesh.indices.size(), clockFaceModel);
        setMaterial(0, 0, 0, 0, 0);
        drawShapes(clockHand, pos_clockH, nor_clockH, ind_clockH, clockHand[0].mesh.indices.size(), hourHandModel);
        drawShapes(clockHand, pos_clockH, nor_clockH, ind_clockH, clockHand[0].mesh.indices.size(), minuteHandModel);
        //        setMaterial(0, 0, 0, 0, 0);
        //        drawShapes(shadowMan, pos_shadow, nor_shadow, ind_shadow, shadowMan[0].mesh.indices.size(), shadowModel);
        
        glUniform1i(collectibleID, 1);
        drawShapes(light, pos_light, nor_light, ind_light, light[0].mesh.indices.size(), lightModel);
        glUniform1i(collectibleID, 0);
        
        // Check if we should spawn new light
        if (timeTicks > times[lightNdx + 1]) {
            lightNdx++;
            lightModel.x = lol[lightNdx].x;
            lightModel.y = lol[lightNdx].y;
            lightModel.z = lol[lightNdx].z;
            showingLight = true;
        }
        
        // Check if we moused over the collectible
        if (showingLight && didCollectLight(minH[lightNdx], maxH[lightNdx], minV[lightNdx], maxV[lightNdx])) {
            printf("yey we did it\n");
            lightModel.x = 10000; // hide light till next time
            showingLight = false;
        }
        
        

		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(quad_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		// Set our "renderedTexture" sampler to user Texture Unit 0
		glUniform1i(texID, 0);

		glUniform1f(timeID, (float)(glfwGetTime()*10.0f) );

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(
			quad_vertexPosition_modelspace, // attribute
			3,                              // size
			GL_FLOAT,                       // type
			GL_FALSE,                       // normalized?
			0,                              // stride
			(void*)0                        // array buffer offset
		);

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

		glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

        
        
        
        
        slenderModel.x = baseSlenderModel.x;
        slenderModel.y = baseSlenderModel.y;
        slenderModel.z = baseSlenderModel.z;

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
//	glDeleteBuffers(1, &vertexbuffer);
//	glDeleteBuffers(1, &uvbuffer);
//	glDeleteBuffers(1, &normalbuffer);
//	glDeleteBuffers(1, &elementbuffer);  TODO: damned if u dont
//	glDeleteProgram(programID);
//	glDeleteTextures(1, &TextureID);

	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &renderedTexture);
	glDeleteRenderbuffers(1, &depthrenderbuffer);
	glDeleteBuffers(1, &quad_vertexbuffer);


	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

