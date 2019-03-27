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
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4

// glm::translate, glm::rotate, glm::scale, glm::perspective
float speed = 1.0f; // move at 1 unit per second
float last_position = 0.0f;
GLuint shader_programme;



glm::mat4 model = glm::mat4(1.0f);
glm::mat4 matrix(1.0);
glm::mat4 myScalingMatrix(1.0);
double value = 0.9008;
float t1     = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        model = glm::translate(model,glm::vec3(0,0,0)); //position = 0,0,0
        
        
        model = glm::rotate(model,glm::radians(t1)/180,glm::vec3(0,0,1));//rotation z = 0.0
        
        myScalingMatrix= glm::scale(myScalingMatrix,glm::vec3(value,value,value));
        matrix=myScalingMatrix*matrix*model;
        
   
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {t1=t1+0.5;
      //  model = glm::translate(model,glm::vec3(0,0,0)); //position = 0,0,0
        
        
        model = glm::rotate(model,glm::radians(t1)/180,glm::vec3(0,0,1));//rotation z = 0.0
        
      //  myScalingMatrix= glm::scale(myScalingMatrix,glm::vec3(1/value,1/value,1/value));
        matrix=matrix*model;
//        matrix=myScalingMatrix*matrix*model;
        
    }
    
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        model = glm::translate(model,glm::vec3(0,0,0)); //position = 0,0,0
        
        
        model = glm::rotate(model,glm::radians(t1)/180,glm::vec3(0,0,1));//rotation z = 0.0
        
        myScalingMatrix= glm::scale(myScalingMatrix,glm::vec3(1/value,1/value,1/value));
        matrix=myScalingMatrix*matrix*model;
        
        
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        //https://open.gl/content/code/c4_transformation.txt
       // model = glm::translate(model,glm::vec3(0.20,0,0)); //position = 0,0,0
        printf("%d,  %d, %d \n",matrix[0].x,matrix[0].y,matrix[0].z);
        matrix = glm::translate(matrix,glm::vec3(0.2,0,0)); //position = 0,0,0
        printf("%d,  %d, %d \n",matrix[0].x,matrix[0].y,matrix[0].z);
      //  matrix=matrix*model;
        
        
    }
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        //https://open.gl/content/code/c4_transformation.txt
        // model = glm::translate(model,glm::vec3(0.20,0,0)); //position = 0,0,0
        printf("%d,  %d, %d \n",matrix[0].x,matrix[0].y,matrix[0].z);
        matrix = glm::translate(matrix,glm::vec3(0.0,-0.2,0)); //position = 0,0,0
        printf("%d,  %d, %d \n",matrix[0].x,matrix[0].y,matrix[0].z);
        //  matrix=matrix*model;
        
        
    }
}


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
    
    auto t_start = std::chrono::high_resolution_clock::now();
t1 = t1+0.01;
    
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
        
        -0.5f,  0.5f, 1.0f, 0.0f,  // Top-left
        0.5f,  0.5f, 0.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, // Bottom-right
        -0.5f, 0.5f, 0.0f, 1.0f // Bottom-left
    };
    
//    GLfloat points[] = {
//        0.0f,    0.5f,    0.0f,
//        0.5f, -0.5f,    0.0f,
//        -0.5f, -0.5f,    0.0f
//    };
//
   
    int params = -1;
    /* these are the strings of code for the shaders
     the vertex shader positions each vertex point */
    char vertex_shader[1024 * 256];
    char fragment_shader[1024*256];
    
    /* GL shader objects for vertex and fragment shader [components] */
    GLuint vs, fs;
    /* GL shader programme object [combined, to link] */
    
    

    
    
    
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
                               600, 600, "Hello Triangle", NULL, NULL
                               );
    
  //      glViewport( 0, 0, 800, 600 );
    
      glfwSetKeyCallback(window, key_callback);
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
    
    //antesglBufferData (GL_ARRAY_BUFFER, 12 * sizeof (GLfloat), points, GL_STATIC_DRAW);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
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
    
    glBindFragDataLocation(shader_programme, 0, "outColor");
    glLinkProgram (shader_programme);
    
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    
    
    while (!glfwWindowShouldClose (window)) {
        /* wipe the drawing surface clear */
        
        
        
        
        static double previous_seconds = glfwGetTime ();
        double current_seconds = glfwGetTime ();
        double elapsed_seconds = current_seconds - previous_seconds;
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
      //  int matrix_location = glGetUniformLocation (shader_programme, "matrix");
        //glUseProgram (shader_programme);
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
        glUseProgram (shader_programme);
        
        
        
        
        
        
        glBindVertexArray (vao);
        /* draw points 0-3 from the currently bound VAO with current in-use shader*/
        //antes
        glDrawArrays (GL_TRIANGLES, 0, 6);
        
        // Draw a rectangle from the 2 triangles using 6 indices
        
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /* update other events like input handling */
        glfwPollEvents ();
        /* put the stuff we've been drawing onto the display */
        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose (window, 1);
        }
        
      //  glm::mat4 model = glm::mat4(1.0f);
        
     
        
        t1=t1+0.001;
       
     
      
       //model = glm::translate(model,glm::vec3(1,1,1)); //position = 0,0,0
        
       //aqui descomentar

        model = glm::rotate(model,glm::radians(t1)/180,glm::vec3(0,0,0.2));//rotation z = 0.0
        
        
        
       glUniformMatrix4fv(glGetUniformLocation(shader_programme, "model"), 1, GL_FALSE, glm::value_ptr(model));
        
        
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
        glUseProgram (shader_programme);
      
        
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        //  glUniformMatrix4fv (matrix_location, 1, GL_FALSE, matrix);
        glfwSwapBuffers (window);
    }
    
    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}
