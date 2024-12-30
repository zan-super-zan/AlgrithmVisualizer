#version 330 core
out vec4 FragColor;


in vec3 fragColor;
void main()
{
    FragColor = vec4(fragColor.xyz, 1.0f);
}