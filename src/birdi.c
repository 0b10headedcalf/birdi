#include "../lib/b_core.h"
#include "../include/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "../lib/b_loadShader.c"
#include <stdio.h>
#include <stdlib.h>

void frame_buffer_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}


int main(int argc, char *argv[])
{
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(800, 600, "window", NULL, NULL);
    if(window == NULL){
        fprintf(stderr,"Failed to create window!\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        fprintf(stderr, "Failed to initialized GLAD");
        return EXIT_FAILURE;
    }
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
    
    while(!glfwWindowShouldClose(window)){

        //render loop
        glClearColor(0.2f,0.2f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return EXIT_SUCCESS;
}
