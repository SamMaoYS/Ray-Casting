//
//  camera.cpp
//  Water
//
//  Created by sam on 2019-07-10.
//  Copyright © 2019 sam. All rights reserved.
//

#include "camera.hpp"

Camera:: Camera() {
    // Initialize Camera
    this->camPos = glm::vec3(0.0f, 0.0f, 3.0f);
    this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->worldUp = this->camUp;
    this->camPitch = PITCH;
    this->camYaw = YAW;
    this->moveSpeed = SPEED;
    this->mouseSensitivity = SENSITIVITY;
    this->camZoom = ZOOM;
    this->UpdateCameraVectors();
}
Camera:: Camera(glm::vec3 pos, glm::vec3 up, GLfloat pitch, GLfloat yaw) {
    // default setup
    this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->moveSpeed = SPEED;
    this->mouseSensitivity = SENSITIVITY;
    this->camZoom = ZOOM;

    this->camPos = pos;
    this->camUp= up;
    this->worldUp = this->camUp;
    this->camPitch = pitch;
    this->camYaw = yaw;
    this->UpdateCameraVectors();
}

glm::mat4 Camera::  GetCameraLookAt() {
    return glm::lookAt(this->camPos, this->camPos + this->camFront, this->camUp);
}

void Camera::  MoveCamera(MoveDirection dir, GLfloat deltaTime) {
    GLfloat velocity = this->moveSpeed * deltaTime;
    if (dir == FORWARD) {
        this->camPos += this->camFront * velocity;
    }
    if (dir == BACKWARD) {
        this->camPos -= this->camFront * velocity;
    }
    if (dir == LEFT) {
        this->camPos -= this->camRight * velocity;
    }
    if (dir == RIGHT) {
        this->camPos += this->camRight * velocity;
    }
}

void Camera::  RotateCamera(GLfloat xOffset, GLfloat yOffset) {
    xOffset *= this->mouseSensitivity;
    yOffset *= this->mouseSensitivity;
    
    this->camPitch -= yOffset;
    this->camYaw += xOffset;
    
    if (this->camPitch > 89.0f) {
        this->camPitch = 89.0f;
    }
    if (this->camPitch < -89.0f) {
        this->camPitch = -89.0f;
    }
    
    UpdateCameraVectors();
}

void Camera::  ZoomCamera(GLfloat scroll) {
    if (this->camZoom >= 44.1f && this->camZoom <= 45.9f) {
        this->camZoom -= 0.1f*scroll;
    }
    if (this->camZoom <= 44.1f) {
        this->camZoom = 44.1f;
    }
    if (this->camZoom >= 45.9f) {
        this->camZoom = 45.9f;
    }
}

void Camera::  SetCameraPos(glm::vec3 pos) {
    this->camPos = pos;
}

void Camera::  SetCameraFront(glm::vec3 front) {
    this->camFront = front;
}
void Camera::  SetCameraUP(glm::vec3 up) {
    this->camUp = up;
}

void Camera::  SetCameraYaw(GLfloat yaw) {
    this->camYaw = yaw;
    UpdateCameraVectors();
}

void Camera::  SetCameraPitch(GLfloat pitch) {
    this->camPitch = pitch;
    UpdateCameraVectors();
}

void Camera::  SetMoveSpeed(GLfloat speed) {
    this->moveSpeed = speed;
}

void Camera::  SetMouseSensitivity(GLfloat sensitivity) {
    this->mouseSensitivity = sensitivity;
}

void Camera::  SetCameraZoom(GLfloat zoom) {
    this->camZoom = zoom;
}

glm::vec3 Camera::  GetCameraPos() {
    return this->camPos;
}

glm::vec3 Camera::  GetCameraFront() {
    return this->camFront;
}

glm::vec3 Camera::  GetCameraUP() {
    return this->camUp;
}

glm::vec3 Camera::  GetCameraRight() {
    return this->camRight;
}

GLfloat Camera::  GetCameraYaw() {
    return this->camYaw;
}

GLfloat Camera::  GetCameraPitch() {
    return this->camPitch;
}

GLfloat Camera::  GetMoveSpeed() {
    return this->moveSpeed;
}

GLfloat Camera::  GetMouseSensitivity() {
    return this->mouseSensitivity;
}

GLfloat Camera::  GetCameraZoom() {
    return this->camZoom;
}

void Camera:: UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->camPitch)) * cos(glm::radians(this->camYaw));
    front.y = sin(glm::radians(this->camPitch));
    front.z = cos(glm::radians(this->camPitch)) * sin(glm::radians(this->camYaw));
    this->camFront = glm::normalize(front);
    this->camRight = glm::normalize(glm::cross(this->camFront, this->worldUp));
    this->camUp = glm::normalize(glm::cross(this->camRight, this->camFront));
}
