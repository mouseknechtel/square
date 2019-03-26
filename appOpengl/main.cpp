//
//  main.cpp
//  appOpengl
//
//  Created by Maiquel Knechtel on 25/02/19.
//  Copyright © 2019 Maiquel Knechtel. All rights reserved.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

// glm::translate, glm::rotate, glm::scale, glm::perspective
float speed = 1.0f; // move at 1 unit per second
float last_position = 0.0f;






void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Cursor Position at (" << xpos << " : " << ypos << std::endl;
    }
}

/* copy a shader from a plain text file into a character array */
bool parse_file_into_str (
                           char* file_name, char* shader_str, int max_len
                          ) {
    FILE* file = fopen (file_name , "r");
    int current_len = 0;
    char line[2048];
    
    shader_str[0] = '\0'; /* reset string */
    if (!file) {
        return false;
    }
    strcpy (line, ""); /* remember to clean up before using for first time! */
    while (!feof (file)) {
        if (NULL != fgets (line, 2048, file)) {
            current_len += strlen (line); /* +1 for \n at end */
            if (current_len >= max_len) {
              
            }
            strcat (shader_str, line);
        }
    }
    if (EOF == fclose (file)) { /* probably unnecesssary validation */
        return false;
    }
    return true;
}
int main () {

    
    glm::mat4 matrix(1.0);
//    GLfloat matrix[] = {
//        1.0f, 0.0f, 0.0f, 0.0f, // first column
//        0.0f, 1.0f, 0.0f, 0.0f, // second column
//        0.0f, 0.0f, 1.0f, 0.0f, // third column
//        0.20f, 0.20f, 0.0f, 1.0f // fourth column
//    };
//
    
    const GLchar* p;
    
    GLFWwindow* window = NULL;
    const GLubyte* renderer;
    const GLubyte* version;
    GLuint vao;
    GLuint vbo;
    
    
    /* geometry to use. these are 3 xyz points (9 floats total) to make a triangle
     */
    /* OTHER STUFF GOES HERE NEXT */
    GLfloat points[] = {
        0.0f,    0.5f,    0.0f,
        0.5f, -0.5f,    0.0f,
        -0.5f, -0.5f,    0.0f
    };
    
    int params = -1;
    /* these are the strings of code for the shaders
     the vertex shader positions each vertex point */
    char vertex_shader[1024 * 256];
    char fragment_shader[1024*256];
    
    /* GL shader objects for vertex and fragment shader [components] */
    GLuint vs, fs;
    /* GL shader programme object [combined, to link] */
    GLuint shader_programme;
    
    

    
    
    
    /* start GL context and O/S window using the GLFW helper library */
    if (!glfwInit ()) {
        fprintf (stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    /* change to 3.2 if on Apple OS X */
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow (
                               640, 480, "Hello Triangle", NULL, NULL
                               );
    if (!window) {
        fprintf (stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent (window);
    /* start GLEW extension handler */
    glewExperimental = GL_TRUE;
    glewInit ();
    
    /* get version info */
    renderer = glGetString (GL_RENDERER); /* get renderer string */
    version = glGetString (GL_VERSION); /* version as a string */
    printf ("Renderer: %s\n", renderer);
    printf ("OpenGL version supported %s\n", version);
    
    /* tell GL to only draw onto a pixel if the shape is closer to the viewer */
    glEnable (GL_DEPTH_TEST); /* enable depth-testing */
    glDepthFunc (GL_LESS);/*depth-testing interprets a smaller value as "closer"*/
    
    /* a vertex buffer object (VBO) is created here. this stores an array of data
     on the graphics adapter's memory. in our case - the vertex points */
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (GLfloat), points, GL_STATIC_DRAW);
    
    /* the vertex array object (VAO) is a little descriptor that defines which
     data from vertex buffer objects should be used as input variables to vertex
     shaders. in our case - use our only VBO, and say 'every three floats is a
     variable' */
    
    
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glEnableVertexAttribArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    /* here we copy the shader strings into GL shaders, and compile them. we then
     create an executable shader 'program' and attach both of the compiled shaders.
     we link this, which matches the outputs of the vertex shader to the inputs of
     the fragment shader, etc. and it is then ready to use */
  
  

    fs = glCreateShader (GL_FRAGMENT_SHADER);
        assert (parse_file_into_str ("/Users/maiquelknechtel/Desktop/code/appOpengl/appOpengl/vs.glsl", vertex_shader, 1024 * 256));
    
    assert(parse_file_into_str("/Users/maiquelknechtel/Desktop/code/appOpengl/appOpengl/fs.glsl",fragment_shader, 1024* 256));
    
    //vertex
    
   
    
    

    
    vs = glCreateShader (GL_VERTEX_SHADER);
    p = (const GLchar*)vertex_shader;
    glShaderSource (vs, 1, &p, NULL);
    glCompileShader (vs);
    
    
    
    
    p = (const GLchar*)fragment_shader;
    glShaderSource (fs, 1, &p, NULL);
    glCompileShader (fs);
    
    
    /* check for compile errors */
    glGetShaderiv (fs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params) {
        fprintf (stderr, "ERROR: GL shader index %i did not compile\n", fs);
        
        return 1; /* or exit or something */
    }
    
    
    shader_programme = glCreateProgram ();
    glAttachShader (shader_programme, fs);
    glAttachShader (shader_programme, vs);
    glLinkProgram (shader_programme);
    
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    
    
    while (!glfwWindowShouldClose (window)) {
        /* wipe the drawing surface clear */
        
        
        
        
        static double previous_seconds = glfwGetTime ();
        double current_seconds = glfwGetTime ();
        double elapsed_seconds = current_seconds - previous_seconds;
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        int matrix_location = glGetUniformLocation (shader_programme, "matrix");
        glUseProgram (shader_programme);
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
        glUseProgram (shader_programme);
        
        
        
        
        
        
        glBindVertexArray (vao);
        /* draw points 0-3 from the currently bound VAO with current in-use shader*/
        glDrawArrays (GL_TRIANGLES, 0, 3);
        /* update other events like input handling */
        glfwPollEvents ();
        /* put the stuff we've been drawing onto the display */
        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose (window, 1);
        }
        
        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_D)) {
            
            
       //     matrix[12] =matrix[12] +0.01;
            
            
              glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
            //
            // Note: this call is related to the most recently 'used' shader programme
        }
        
        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_A)) {
            
            
         //   matrix[12] =matrix[12] -0.01;
            
            
           glm::mat4 test = glm::rotate(glm::mat4(1.0f), 3.14f,  glm::vec3(-1.0f, 0.0f, 0.0f));
            
//            glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
//
//            glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0));
//            //glm::mat4 test = glm::rotate(matrix, glm::radians(0.20), glm::vec3(1, 1, 1));
//           // matrix = matrix* test;
//            //glm::mat4 matrix=  glm::glOrtho(0.0f,800.0f,600.0f,0.0f,-1.0f,1.0);
//            //
//            // Note: this call is related to the most recently 'used' shader programme
//            View = glm::rotate(View,1.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
//            View = glm::rotate(View, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//            glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//
         
            matrix=matrix*test;
              glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
          
        }
        
        
        //  glUniformMatrix4fv (matrix_location, 1, GL_FALSE, matrix);
        glfwSwapBuffers (window);
    }
    
    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}
