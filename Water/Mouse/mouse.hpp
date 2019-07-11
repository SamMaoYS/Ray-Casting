//
//  mouse.hpp
//  Water
//
//  Created by sam on 2019-07-11.
//  Copyright © 2019 sam. All rights reserved.
//

#ifndef mouse_hpp
#define mouse_hpp

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mouse {
public:
    GLfloat lastX;
    GLfloat lastY;
    double xPos;
    double yPos;
    bool firstMouse;
    
    Mouse();
    
    void SetMouseMoveRange(unsigned int width, unsigned int height);
    void SetMouseMoveRangeWidth(unsigned int width);
    void SetMouseMoveRangeHeight(unsigned int height);
    
    //static void GLFWCursorPosFunc(GLFWwindow* window, double x, double y);
    
private:
    unsigned int moveRangeWidth = 800;
    unsigned int moveRangeHeight = 600;
};

#endif /* mouse_hpp */
