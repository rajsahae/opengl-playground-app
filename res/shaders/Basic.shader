#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 v_Color;

uniform mat4 u_MVP;

out vec3 fragmentColor;

void main()
{
   gl_Position = u_MVP * position;
   fragmentColor = v_Color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 fragmentColor;

void main()
{
   color = vec4(fragmentColor, 1);
}
