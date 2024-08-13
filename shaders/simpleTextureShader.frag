#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// The texture objects
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // Just use the texture
//    FragColor = texture(texture1, TexCoord);
    // Mix texture with inputted color
//    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    // Mix the two textures together
    FragColor = mix(texture(texture1, TexCoord),
        texture(texture2, TexCoord), 0.2);
}