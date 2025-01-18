#type vertex
#version 300 es
precision highp float;
layout (location = 0) in vec3 aPos;

uniform mat4 model;       // Model transformation matrix
uniform mat4 u_view;        // View transformation matrix (camera)
uniform mat4 u_projection;  // Projection matrix

void main() {
    gl_Position = u_view * u_projection * model * vec4(aPos, 1.0);
}

#type fragment
#version 300 es
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
}
