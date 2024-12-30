#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 ViewProjection;
uniform mat4 Model;
out vec3 fragColor;

void main()
{
    gl_Position = ViewProjection * Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    fragColor = aColor;
}