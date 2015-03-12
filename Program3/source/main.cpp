// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include "glm/glm.hpp"
using namespace glm;

#include <common/shader.hpp>

int width, height;
#define NUM_POINTS 40

void window_resized(GLFWwindow* window, int width_, int height_) {
    printf("Width: %d, Height: %d\n", width, height);
    width = width_;
    height = height_;
    glViewport(0, 0, width, height);
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
    width = 800;
    height = 800;
    window = glfwCreateWindow( width, height, "Program 2A - fun with points", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    glfwSetWindowSizeCallback(window, window_resized);
    
    // Dark blue background
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    
    // Get a handle for our buffers
    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint vertexColorID = glGetAttribLocation(programID, "vertexColor");
    GLuint winScaleID = glGetUniformLocation(programID, "uWinScale");
    GLuint winCenterID = glGetUniformLocation(programID, "uWinCenter");
    GLuint timeID = glGetUniformLocation(programID, "uTime");
    GLuint targetDistID = glGetUniformLocation(programID, "uTargetDist");
    GLuint circleScaleID = glGetUniformLocation(programID, "uCircleScale");
    
    static GLfloat g_point_buffer_data[NUM_POINTS * 2 + 18];
    
    srand((unsigned int)time(NULL));
    g_point_buffer_data[0] = -0.0f;
    g_point_buffer_data[1] = -0.0f;
    
    g_point_buffer_data[2] = -0.2f;
    g_point_buffer_data[3] = -0.2f;
    
    g_point_buffer_data[4] =  0.0f;
    g_point_buffer_data[5] = -0.2f;
    
    g_point_buffer_data[6] =  0.2f;
    g_point_buffer_data[7] = -0.2f;
    
    g_point_buffer_data[8] =  0.2f;
    g_point_buffer_data[9] =  0.0f;
    
    g_point_buffer_data[10] =  0.2f;
    g_point_buffer_data[11] =  0.2f;
    
    g_point_buffer_data[12] =  0.0f;
    g_point_buffer_data[13] =  0.2f;
    
    g_point_buffer_data[14] = -0.2f;
    g_point_buffer_data[15] =  0.2f;
    
    g_point_buffer_data[16] = -0.2f;
    g_point_buffer_data[17] =  0.0f;
    
    for (int i = 18; i < NUM_POINTS * 2 + 18; i++) {
        float newPointCoord = (float)rand()/(float)(RAND_MAX/2.0) - 1;
        g_point_buffer_data[i] = newPointCoord;
    }
    
    static const GLfloat g_color_buffer_data[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_point_buffer_data), g_point_buffer_data, GL_STATIC_DRAW);
    
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    
    /** WHAT TIIIIME IS IT? */
    float l_time = 0;
    /** How many seconds until the points reach their destination */
    const float targetTime = 2;
    
    do{
        
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Use our shader
        glUseProgram(programID);
        
        // Tell the shader how to scale the vertices to account for the window size
        if (width > height) {
            glUniform2f(winScaleID, height / (float) width, 1);
        }
        else {
            glUniform2f(winScaleID, 1, width / (float) height);
        }
        glUniform2f(winCenterID, (float) width/2, (float) height/2);
        glUniform1f(targetDistID, 0.3f);
        glUniform1f(circleScaleID, fminf(width, height));
        
        // Tell the shader what time it is
        glUniform1f(timeID, l_time / targetTime);
        if (l_time + 0.01 < targetTime) {
            l_time += 0.01;
        }
        else {
            l_time = targetTime;
        }
        
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(vertexPosition_modelspaceID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              vertexPosition_modelspaceID, // The attribute we want to configure
                              2,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(vertexColorID);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                              vertexColorID,               // The attribute we want to configure
                              3,                           // size
                              GL_FLOAT,                    // type
                              GL_FALSE,                    // normalized?
                              0,                           // stride
                              (void*)0                     // array buffer offset
                              );
        
        // Draw the point !
        glDrawArrays(GL_POINTS, 0, NUM_POINTS * 2);
        
        glDisableVertexAttribArray(vertexPosition_modelspaceID);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    
    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

