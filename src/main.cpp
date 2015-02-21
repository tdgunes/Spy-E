//
//  main.cpp
//  Agile
//
//  Created by Deniz Sokmen on 10/02/15.
//  Copyright (c) 2015 CS476. All rights reserved.
//

#include <iostream>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Include Shader, Controls
#include "shader.hpp"
#include "controls.hpp"

// Include Cube, Scene
#include "Scene.h"
#include "Cube.h"

int main( void )
{
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    
    
    
    // create opengl 3.3 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    

    
    window = glfwCreateWindow( 1024, 768, "Photic Zone", NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );

    
    
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(120.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
                                       glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
                                       glm::vec3(0,0,0), // and looks at the origin
                                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                       );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

    


    Scene *scene = new Scene();
    

   
    for (int i=0; i<20; i++) {
        for (int j=0; j<20; j++) {
            for (int k=0; k<20; k++) {

                Cube *cube = new Cube(Point {-30.0f+i*2, -10.0f+j*2, 0.0f+k*2}, 10.0f);
                scene->add(cube);
            }

        }

    }
    
   

    
    
    


    

    
    
    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.014f,  0.184f,  0.576f,
        0.982f,  0.099f,  0.879f,
        0.014f,  0.184f,  0.576f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.014f,  0.184f,  0.576f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.014f,  0.184f,  0.576f,
        0.982f,  0.099f,  0.879f,
        0.014f,  0.184f,  0.576f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.982f,  0.099f,  0.879f,
        0.014f,  0.184f,  0.576f,
    };
    

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    //Load here
    
    scene->load();
    
    do{
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Use our shader
        glUseProgram(programID);
        
        
        
        // Compute the MVP matrix from keyboard and mouse input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        

        

        
        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                              1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                              3,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );


        //TODO: Render here
        // Draw the triangle !

        scene->render();
        
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader

    //TODO: unload here
    scene->unload();
    
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}
