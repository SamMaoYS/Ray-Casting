//
//  window.cpp
//  Water
//
//  Created by sam on 2019-06-28.
//  Copyright © 2019 sam. All rights reserved.
//

#include "window.h"

Window:: Window(string name, GLuint width, GLuint height) {
    // Init GLFW
    glfwInit( );
    
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    this->Width = width;
    this->Height = height;
    this->window = glfwCreateWindow(this->Width, this->Height, name.c_str(), nullptr, nullptr);
}

int Window:: DefineViewPort() {
    if ( nullptr == this->window )
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwGetFramebufferSize( this->window, &this->screenWidth, &this->screenWidth );
    glViewport( 0, 0, this->screenWidth, this->screenWidth );
    
    return EXIT_SUCCESS;
}

int Window:: InitializeGLEW() {
    if ( GLEW_OK != glewInit( ) )
    {
        cout << "Failed to initialize GLEW" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void Window:: SetUpBuffers(vector<GLfloat> vertices) {
    GLfloat ver[vertices.size()];
    memcpy(ver, &vertices[0], sizeof(GLfloat)*vertices.size());
    
    glGenVertexArrays( 1, &this->VAO );
    glBindVertexArray( this->VAO );
    
    glGenBuffers( 1, &this->VBO );
    glBindBuffer( GL_ARRAY_BUFFER, this->VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW );
    
    for (int i=0; i<this->attriNum; i++) {
        glVertexAttribPointer(i, this->attriSize[i], GL_FLOAT, GL_FALSE, this->attriSetSize * sizeof(GLfloat), (GLvoid*)(this->attriOffset[i] * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
    }

    // Unbind VAO
    glBindVertexArray( 0 );
}

void Window:: SetUpBuffers(vector<GLfloat> vertices, vector<GLuint> indices) {
    GLfloat ver[vertices.size()];
    memcpy(ver, &vertices[0], sizeof(GLfloat)*vertices.size());
    GLuint ind[indices.size()];
    memcpy(ind, &indices[0], sizeof(GLuint)*indices.size());
    
    glGenVertexArrays( 1, &this->VAO );
    glBindVertexArray( this->VAO );
    
    glGenBuffers( 1, &this->VBO );
    glBindBuffer( GL_ARRAY_BUFFER, this->VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(ver), ver, GL_STATIC_DRAW );
    
    glGenBuffers( 1, &this->EBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW );
    
    for (int i=0; i<this->attriNum; i++) {
        glVertexAttribPointer(i, this->attriSize[i], GL_FLOAT, GL_FALSE, this->attriSetSize * sizeof(GLfloat), (GLvoid*)(this->attriOffset[i] * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
    }
    
    // Unbind VAO
    glBindVertexArray( 0 );
}

void Window:: GetAttributeInfo(vector<int> asize) {
    this->attriNum = (int) asize.size();
    this->attriSize = asize;
    this->attriSetSize = 0;
    for (int i=0; i<this->attriNum; i++) {
        this->attriSetSize += asize[i];
        if (i != 0) {
            this->attriOffset.push_back(asize[i-1] + this->attriOffset[i-1]);
        }
        else{
            this->attriOffset.push_back(0);
        }
    }
}

void Window:: LoadTexture(GLuint *texture, string path, int alpha) {
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Load texture
    GLint width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte *image = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (image)
    {
        if (alpha == 1) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        cout << "ERROR::Failed to load texture" << endl;
    }
    stbi_image_free(image);
}

void Window:: BindTexture(GLuint texture, int index) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Window:: DeleteBuffers() {
    // Properly de-allocate all resources
    glDeleteVertexArrays( 1, &this->VAO );
    glDeleteBuffers( 1, &this->VBO );
    glDeleteBuffers( 1, &this->EBO );
}

