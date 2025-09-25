#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec4 vNorm;

void main()
{
    vNorm = vec4(aNorm, 1.0);
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}