#ifndef COLORS_H
#define COLORS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include <tsVertexObject.h>
#include <tcShader.h>

namespace Colors
{

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

GLFWwindow*
CreateAndSetupGlfwWindow()
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

std::shared_ptr<Shader> 
CreateShader()
{
    // build and compile our shader program
    // ------------------------------------
    // NOTE [AFC]: using "triangle" shader but will work for rect too
    const auto lcVertexShaderPath = "../shaders/6.1.coordinate-systems.vert";
    const auto lcFragmentShaderPath = "../shaders/6.1.coordinate-systems.frag";

    return std::make_shared<Shader>(lcVertexShaderPath, lcFragmentShaderPath);
}

tsVertexObject
CreateAndSetupVertexObjects()
{
    std::cout << "1.0" << std::endl;
    // Init the objects
    unsigned int lnVao, lnVbo, lnEbo;
    glGenVertexArrays(1, &lnVao);
    glGenBuffers(1, &lnVbo);
    glGenBuffers(1, &lnEbo);
    std::cout << "1.1" << std::endl;

    tsVertexObject lsVertexObject;
    lsVertexObject.mnVaoId = lnVao;
    lsVertexObject.mnVboId = lnVbo;
    lsVertexObject.mnEboId = lnEbo;
    std::cout << "1.2" << std::endl;

    // Enable depth testing 
    glEnable(GL_DEPTH_TEST);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // Cube vertices
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(lsVertexObject.mnVaoId);

    glBindBuffer(GL_ARRAY_BUFFER, lsVertexObject.mnVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // [AFC] bind the element array (aka indices)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lsVertexObject.mnEboId);
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

    return lsVertexObject;
}

std::vector<unsigned int>
CreateAndSetupTextures(std::shared_ptr<Shader> apcShader)
{
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
    apcShader->use(); 
    apcShader->setInt("texture1", 0);
    apcShader->setInt("texture2", 1);

    return std::vector<unsigned int>(texture1, texture2);
}

void
RenderLoop(
    GLFWwindow* apcWindow,
    const tsVertexObject& arsVertexObj,
    std::shared_ptr<Shader> apcShader,
    const std::vector<unsigned int>& arcTextures)
{
    static const glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    // input
    // -----
    processInput(apcWindow);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // clear the depth buffer before each render
    // iteration (otherwise the depth information of the previous frame stays in the buffer)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bind textures on corresponding texture units
    for(size_t lnTexIdx = 0; lnTexIdx < arcTextures.size(); ++lnTexIdx)
    {
        glActiveTexture(GL_TEXTURE0+lnTexIdx);
        glBindTexture(GL_TEXTURE_2D, arcTextures[lnTexIdx]);
    }

    // activate shader
    apcShader->use();
    
    // create transformations
    // glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);

    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // Rotate the cube over time
    // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Exercise 2
    // view  = glm::translate(view, glm::vec3(0.0f, -1.0f, -5.0f));
    // view = glm::rotate(view, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // retrieve the matrix uniform locations
    // unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    unsigned int viewLoc  = glGetUniformLocation(apcShader->ID, "view");
    // pass them to the shaders (3 different ways)
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    apcShader->setMat4("projection", projection);

    // render container
    glBindVertexArray(arsVertexObj.mnVaoId);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // NOTE: using glDrawArrays this time
    // Draw all 36 triangles for the cube
    // glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw 10 of the same cube at different locations within the view
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);

        // Exercise 3: only rotate the 3rd cube over time, rest static
        if(i == 3)
        {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        }
        else
        {
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle),
                glm::vec3(1.0f, 0.3f, 0.5f));
        }
        apcShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(apcWindow);
    glfwPollEvents();
}

void
CleanUp(const tsVertexObject& arsVertexObject)
{
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &arsVertexObject.mnVaoId);
    glDeleteBuffers(1, &arsVertexObject.mnVboId);
    glDeleteBuffers(1, &arsVertexObject.mnEboId);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void
drawSceneWithLight()
{
    auto* lpcWindow = CreateAndSetupGlfwWindow();
    std::cout << "1" << std::endl;
    auto lpcShader = CreateShader();
    std::cout << "2" << std::endl;
    auto lsVertexObj = CreateAndSetupVertexObjects();
    std::cout << "3" << std::endl;
    auto lcTextures = CreateAndSetupTextures(lpcShader);
    std::cout << "4" << std::endl;

    while (!glfwWindowShouldClose(lpcWindow))
    {
        RenderLoop(lpcWindow, lsVertexObj, lpcShader, lcTextures);
    }
    
    CleanUp(lsVertexObj);
}

} // end namespace Colors

#endif // COLORS_H