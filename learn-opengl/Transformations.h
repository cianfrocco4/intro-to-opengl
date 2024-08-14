#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// #include <filesystem.h>
// #include <shader_s.h>

#include <iostream>

namespace Transformations
{

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

float grTexMixVal = 0.5f;

GLFWwindow*
initAndCreateGlfwWindow()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return window;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void
setupVertexObjects(
    const unsigned int VAO, 
    const unsigned int VBO, 
    const unsigned int EBO)
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // [AFC] bind the element array (aka indices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const unsigned int lnVertexBufferWidth = 5;

    // position attribute
    const int lnPosAttrBufferWidth = 3;
    glVertexAttribPointer(
        0, 
        lnPosAttrBufferWidth, 
        GL_FLOAT, GL_FALSE, 
        lnVertexBufferWidth * sizeof(float), 
        (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    const unsigned int lnTexAttrBufferWidth = 2;
    glVertexAttribPointer(
        1, 
        lnTexAttrBufferWidth, 
        GL_FLOAT, GL_FALSE, 
        lnVertexBufferWidth * sizeof(float),  
        (void*)((lnPosAttrBufferWidth) * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);
}

void
renderLoop(
    GLFWwindow* window,
    const unsigned int VAO,
    Shader ourShader,
    const unsigned int texture1,
    const unsigned int texture2)
{
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 transform2 = glm::mat4(1.0f);
    // transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    // transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Exercise 1
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

    // Exercise 2
    // transform to top left corner
    transform2 = glm::translate(transform2, glm::vec3(-0.5f, 0.5f, 0.0f));
    // Scale with time using sin function
    // NOTE: sin will invert texture when negative
    transform2 = glm::scale(
        transform2, 
        glm::vec3(
            glm::abs(glm::sin((float)glfwGetTime())), 
            glm::abs(glm::sin((float)glfwGetTime())),
            0.0f));

    // get matrix's uniform location and set matrix
    ourShader.use();
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    // render container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Exercise 2
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void
cleanUp(
    const unsigned int VAO, 
    const unsigned int VBO, 
    const unsigned int EBO)
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void
drawRectWithTransformation()
{
    // Flip the image because:
    //      OpenGL expects the 0.0 coordinate on the y-axis to be on the 
    //      bottom side of the image, but images usually have 0.0 at the 
    //      top of the y-axis.
    stbi_set_flip_vertically_on_load(true);

    auto* window = initAndCreateGlfwWindow();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // build and compile our shader program
    // ------------------------------------
    // NOTE [AFC]: using "triangle" shader but will work for rect too
    const auto lcVertexShaderPath = "../shaders/5.1-transform.vert";
    const auto lcFragmentShaderPath = "../shaders/5.1-transform.frag";

    Shader ourShader(
        lcVertexShaderPath, 
        lcFragmentShaderPath); // you can name your shader files however you like

    // [AFC] Create and init vertex objects
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    setupVertexObjects(VBO, VAO, EBO);

    // [AFC] Create and init texture(s)
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);

    // For only 1 texture-unit, this will be the default usually, however sometimes it is 
    // necessary to manually set it initally.
    // openGL supports a minimum of 15 texture-units, sometimes more
    glActiveTexture(GL_TEXTURE0); // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/container.jpg", &width, &height,
    &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, data);

        // [AFC] the default mipmap is 0, glGenerateMipMap will auto-generate
        // the remaining.
        glGenerateMipmap(GL_TEXTURE_2D);

        // Make sure to free the data after the texture is created
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // load and generate the texture
    glActiveTexture(GL_TEXTURE1); // activate texture unit first
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("../resources/awesomeface.png", &width, &height,
        &nrChannels, 0);
    if (data)
    {
        // NOTE: png's are RGBA format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, data);

        // [AFC] the default mipmap is 0, glGenerateMipMap will auto-generate
        // the remaining.
        glGenerateMipmap(GL_TEXTURE_2D);

        // Make sure to free the data after the texture is created
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); 
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        renderLoop(window, VAO, ourShader, texture1, texture2);
    }

    cleanUp(VAO, VBO, EBO);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

} // end namespace Transformations

#endif // TRANSFORMATIONS_H