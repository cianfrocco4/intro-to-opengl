#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include <HelloTriangle.h>
#include <Shaders.h>
#include <Textures.h>
#include <Transformations.h>
#include <CoordinateSystems.h>

#include <tcShader.h>

int main()
{
    /** Create triangle */
    // HelloTriangle::drawTriangle();
    // HelloTriangle::drawRectangle();
    // HelloTriangle::drawTwoTriangles();
    // HelloTriangle::drawTwoTrianglesDiffVaoVbos();
    // HelloTriangle::drawTwoTrianglesDiffPrograms();

    /** Shaders */
    // Shaders::drawTriangleWithChangingUniform();
    // Shaders::drawTriangleWithColorVertAttrs();
    // Shaders::drawTriangleUsingShaderClass();
    // Shaders::drawUpsideDownTriangle();
    // Shaders::drawTriangleUniformOffset();
    // Shaders::drawTriangleColorByPosition();

    /** Textures */
    // Textures::drawRectWithTexture();

    /** Transformations */
    // Transformations::drawRectWithTransformation();

    /** Coordinate Systems */
    CoordinateSystems::drawRect3D();

    return 0;
}