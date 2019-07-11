//
//  mouse.cpp
//  Water
//
//  Created by sam on 2019-07-11.
//  Copyright © 2019 sam. All rights reserved.
//

#include "mouse.hpp"

Mouse:: Mouse() {
    // set mouse pos at center of window
    lastX = this->moveRangeWidth / 2.0f;
    lastY = this->moveRangeHeight / 2.0f;
    xPos = this->moveRangeWidth / 2.0f;
    yPos = this->moveRangeHeight / 2.0f;
}


void Mouse:: SetMouseMoveRange(unsigned int width, unsigned int height) {
    this->moveRangeWidth = width;
    this->moveRangeHeight = height;
}

void Mouse:: SetMouseMoveRangeWidth(unsigned int width) {
    this->moveRangeWidth = width;
}

void Mouse:: SetMouseMoveRangeHeight(unsigned int height) {
    this->moveRangeHeight = height;
}

//void Mouse:: GLFWCursorPosFunc(GLFWwindow* window, double x, double y) {
//    xPos = x;
//    yPos = y;
//}
