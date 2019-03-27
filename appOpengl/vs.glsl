#version 410
in vec3 vp;
uniform mat4 matrix; // our matrix
uniform mat4 model;

//gl_Position = matrix * vec4(vertex_position, 1.0);
void main () {
    gl_Position = model * matrix * vec4 (vp, 1.0);
    

}
