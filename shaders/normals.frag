#version 330 core
in vec4 vNorm;
out vec4 FragColor;

void main()
{
    float r = (vNorm.x + 1)/2;
    float g = (vNorm.y + 1)/2;
    float b = (vNorm.z + 1)/2;
    FragColor = vec4(r, g, b, 1.0);
}