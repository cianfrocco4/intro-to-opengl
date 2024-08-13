#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <stb_image.h>

namespace Textures
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
        // positions      // colors         // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };

    // Exercise 2
    //  - Change the max texture coord to 2*pos-coord to result in 4 repeated textures
    // float vertices[] = {
    //     // positions      // colors         // texture coords
    //     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, // top right
    //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f // top left
    // };

    // // Exercise 3
    // float vertices[] = {
    //     // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
    //      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
    //      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
    //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
    //     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left 
    // };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // [AFC] bind the element array (aka indices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const unsigned int lnVertexBufferWidth = 8;

    // position attribute
    const int lnPosAttrBufferWidth = 3;
    glVertexAttribPointer(
        0, 
        lnPosAttrBufferWidth, 
        GL_FLOAT, GL_FALSE, 
        lnVertexBufferWidth * sizeof(float), 
        (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    const unsigned int lnColorAttrBufferWidth = 3;
    glVertexAttribPointer(
        1, 
        lnColorAttrBufferWidth, 
        GL_FLOAT, GL_FALSE, 
        lnVertexBufferWidth * sizeof(float), 
        (void*)(lnPosAttrBufferWidth * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    const unsigned int lnTexAttrBufferWidth = 2;
    glVertexAttribPointer(
        2, 
        lnTexAttrBufferWidth, 
        GL_FLOAT, GL_FALSE, 
        lnVertexBufferWidth * sizeof(float),  
        (void*)((lnPosAttrBufferWidth+lnColorAttrBufferWidth) * sizeof(float)));
    glEnableVertexAttribArray(2);

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

    // Exercise 4
    ourShader.setFloat("arTexMix", grTexMixVal);

    // render the triangle
    ourShader.use();

    // Bind the texture unit(s)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBindVertexArray(VAO);
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
drawRectWithTexture()
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
    const auto lcVertexShaderPath = "../shaders/simpleTextureShader.vert";
    const auto lcFragmentShaderPath = "../shaders/simpleTextureShader.frag";

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
    // // set the texture wrapping/filtering options (on currently bound texture)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // BEGIN Exercise 3
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // END Exercise 3

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

    // tell OpenGL to which texture unit each shader sampler belongs to by setting
    // each sampler using glUniform1i
    ourShader.use(); // don’t forget to activate the shader first!
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // manually
    ourShader.setInt("texture2", 1); // or with shader class

    // Exercise 4
    ourShader.setFloat("arTexMix", grTexMixVal);

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
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        grTexMixVal += 0.001;
        grTexMixVal = std::min(grTexMixVal, 1.0f);
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        grTexMixVal -= 0.001;
        grTexMixVal = std::max(grTexMixVal, 0.0f);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

} // end namepsace Textures

#endif // TEXTURES_H