//
//  window.h
//  Water
//
//  Created by sam on 2019-06-28.
//  Copyright © 2019 sam. All rights reserved.
//

#ifndef window_h
#define window_h

#include <iostream>
#include <math.h>
#include <vector>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "../StbImage/stb_image.h"

using namespace std;

class Window {
public:
    GLFWwindow* window;
    GLuint Width;
    GLuint Height;
    
    Window () {}
    Window (string name, GLuint width, GLuint height);
    ~Window () {}
    
    int DefineViewPort();
    int InitializeGLEW();
    void SetUpBuffers(GLuint *VAO, GLuint *VBO);
    void SetUpBuffers(vector<GLfloat> vertices, GLuint *VAO, GLuint *VBO);
    void SetUpBuffers(vector<GLfloat> vertices, vector<GLuint> indices, GLuint *VAO, GLuint *VBO, GLuint *EBO);
    void GetAttributeInfo(vector<int> asize);
    void LoadTexture(GLuint *texture, string path, int alpha);
    void BindTexture(GLuint texture, int index);
    void DeleteBuffers(GLuint *VAO);
    void DeleteBuffers(GLuint *VAO, GLuint *VBO);
    void DeleteBuffers(GLuint *VAO, GLuint *VBO, GLuint *EBO);
    
    //static void GLFWFrameBufferSizeFunc(GLFWwindow *window, int width, int height);
    
private:
    int screenWidth;
    int screenHeight;
    int attriNum;
    int attriSetSize;
    vector<int> attriSize;
    vector<int> attriOffset;
};


#endif /* window_h */
