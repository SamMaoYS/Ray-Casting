//
//  camera.hpp
//  Water
//
//  Created by sam on 2019-07-10.
//  Copyright © 2019 sam. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum MoveDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const GLfloat PITCH       =  0.0f;
const GLfloat YAW         = -90.0f;
const GLfloat SPEED       =  2.5f;
const GLfloat SENSITIVITY =  0.1f;
const GLfloat ZOOM        =  45.0f;
const glm::vec3 CAMFRONT  =  glm::vec3(0.0f, 0.0f, -1.0f);

class Camera {
public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 up, GLfloat pitch, GLfloat yaw);
    // TO DO: delete camera
    ~Camera() {}
    
    glm::mat4 GetCameraLookAt();
    void MoveCamera(MoveDirection dir, GLfloat deltaTime);
    void RotateCamera(GLfloat xOffset, GLfloat yOffset);
    void ZoomCamera(GLfloat scroll);
    
    void SetCameraPos(glm::vec3 pos);
    void SetCameraFront(glm::vec3 front);
    void SetCameraUP(glm::vec3 up);
    void SetCameraYaw(GLfloat yaw);
    void SetCameraPitch(GLfloat pitch);
    void SetMoveSpeed(GLfloat speed);
    void SetMouseSensitivity(GLfloat sensitivity);
    void SetCameraZoom(GLfloat zoom);
    
    glm::vec3 GetCameraPos();
    glm::vec3 GetCameraFront();
    glm::vec3 GetCameraUP();
    glm::vec3 GetCameraRight();
    GLfloat GetCameraYaw();
    GLfloat GetCameraPitch();
    GLfloat GetMoveSpeed();
    GLfloat GetMouseSensitivity();
    GLfloat GetCameraZoom();
    
private:
    glm::vec3 camPos;
    glm::vec3 camFront;
    glm::vec3 camUp;
    glm::vec3 camRight;
    glm::vec3 worldUp;
    // Euler Angles
    GLfloat camPitch;
    GLfloat camYaw;
    // Move options
    GLfloat moveSpeed;
    GLfloat mouseSensitivity;
    GLfloat camZoom;
    
    void UpdateCameraVectors();
};

#endif /* camera_hpp */
