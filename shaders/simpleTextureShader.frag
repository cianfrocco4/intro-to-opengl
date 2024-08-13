#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// Exercise 4
uniform float arTexMix;

// The texture objects
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // Just use the texture
//    FragColor = texture(texture1, TexCoord);

    // Mix texture with inputted color
//    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);

    // linearly interpolate between both textures (80% container, 20% awesomeface)
//    FragColor = mix(texture(texture1, TexCoord),
//        texture(texture2, TexCoord), 0.2);

    // Exercise 1
    // [AFC] To reflect over the y-axis: (-x, y)
//    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.x, TexCoord.y)), 0.2);

    // Exercise 4
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = mix(texture(texture1, TexCoord),
        texture(texture2, TexCoord), arTexMix);
}