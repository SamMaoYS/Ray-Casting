#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 lightColor;

void main()
{
    vec4 mixColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3);
    FragColor = mixColor * lightColor;
}
