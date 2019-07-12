//
//  build_scene.cpp
//  Water
//
//  Created by sam on 2019-07-11.
//  Copyright © 2019 sam. All rights reserved.
//

#include "build_scene.hpp"

vector<Camera*> Build:: cameraList;
int Build:: camNum;

Build:: Build() {}

void Build:: SetUpWindowInteractive(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyCallBack);
    glfwSetScrollCallback(window, ScrollCallBack);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Build:: KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
    
    if (action == GLFW_PRESS && key == GLFW_KEY_E) {
        AddCamera();
        camNum = (int) cameraList.size()-1;
    }
    
    //switch camera
    if (action == GLFW_PRESS && key == GLFW_KEY_R && cameraList.size() > 1) {
        if (camNum < cameraList.size()-1) {
            camNum++;
        }
        else {
            camNum = 0;
        }
    }


    // delete current camera
    if (action == GLFW_PRESS && key == GLFW_KEY_T && cameraList.size() > 1) {
        if (cameraList.size() > 1) {
            delete cameraList[camNum];
            cameraList.erase(cameraList.begin()+camNum);
            camNum = 0;
        }
    }

}

void Build:: KeyPress(GLFWwindow *window, GLfloat deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraList[camNum]->MoveCamera(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraList[camNum]->MoveCamera(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraList[camNum]->MoveCamera(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraList[camNum]->MoveCamera(RIGHT, deltaTime);
    }
}

void Build:: MouseCallBack(GLFWwindow *window) {
    glfwGetCursorPos(window, &mouse.xPos, &mouse.yPos);

    if (mouse.firstMouse) {
        mouse.lastX = mouse.xPos;
        mouse.lastY = mouse.yPos;
        mouse.firstMouse = false;
    }

    GLfloat xOffset = mouse.xPos - mouse.lastX;
    GLfloat yOffset = mouse.yPos - mouse.lastY;

    mouse.lastX = mouse.xPos;
    mouse.lastY = mouse.yPos;

    cameraList[camNum]->RotateCamera(xOffset, yOffset);
}

void Build:: ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset) {
    cameraList[camNum]->ZoomCamera(yOffset);
}

void Build:: AddCamera() {
    Camera* cam = new Camera();
    cameraList.push_back(cam);
}
