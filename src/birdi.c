#include "../lib/b_core.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (!glfwInit()){
        //init failed
        fprintf(stderr,"%s", "GLFW context was unable to initialize!");
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Window", NULL, NULL);

    if (!window){
        glfwTerminate();
        fprintf(stderr,"%s","GLFW: failed to create window");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)){
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        // const float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
