
// C++ headers
#include <iostream>

// GLAD headers
// NOTE: need to include glad *before* glfw since glfw needs OpenGL included first
#include <glad/glad.h>

// GLFW headers
#include <GLFW/glfw3.h>

/**
 * The resize window callback
 */
void 
framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * Process input on the window
 */
void 
processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        // Test to show color clearing on frame we want to close on
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSetWindowShouldClose(window, true);
    }
}

/**
 * The main function.
 */
int 
main(int, char**)
{
    std::cout << "Entering main" << std::endl;

    glfwInit();

    /*
     * Docs for GLFW window hints:
     *     - https://www.glfw.org/docs/latest/window.html#window_hints
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // NOTE: needed for MacOS X
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    // Specify window size to render
    // NOTE: this can be smaller than the size of the window specified above
    glViewport(0, 0, 800, 600);

    /*
     * NOTE:
     * Behind the scenes OpenGL uses the data specified via glViewport to transform 
     * the 2D coordinates it processed to coordinates on your screen. For example, 
     * a processed point of location (-0.5,0.5) would (as its final transformation) 
     * be mapped to (200,450) in screen coordinates. Note that processed coordinates 
     * in OpenGL are between -1 and 1 so we effectively map from the range (-1 to 1) 
     * to (0, 800) and (0, 600).
     */

    // Register the callback functions after we've created the window and before the
    // render loop is initiated.
    // Register the window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Start the render loop
    // Every iteration of the render loop is referred to as a "frame"
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands here
        // ...

        // check and call events and swap the buffers
        /* 
         * NOTE: Using "double buffer"
         * The glfwSwapBuffers will swap the color buffer (a large 2D buffer that contains 
         * color values for each pixel in GLFW's window) that is used to render to during 
         * this render iteration and show it as output to the screen
         */
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    std::cout << "Exiting main" << std::endl;
  
    return 0;
}
