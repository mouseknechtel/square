#version 410
in vec3 vp;
uniform mat4 matrix; // our matrix


//gl_Position = matrix * vec4(vertex_position, 1.0);
void main () {
    gl_Position =  matrix *   vec4 (vp, 1.0);
    

}
