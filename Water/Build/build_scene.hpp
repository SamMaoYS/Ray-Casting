//
//  build_scene.hpp
//  Water
//
//  Created by sam on 2019-07-11.
//  Copyright © 2019 sam. All rights reserved.
//

#ifndef build_scene_hpp
#define build_scene_hpp
#include "../Camera/camera.hpp"
#include "../Mouse/mouse.hpp"
#include <vector>

using namespace std;

class Build {
public:
    Build();
    ~Build() {}
    
    static vector<Camera*> cameraList;
    static int camNum;
    static void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset);
    
    void SetUpWindowInteractive(GLFWwindow* window);
    void KeyPress(GLFWwindow *window, GLfloat delta);
    void MouseCallBack(GLFWwindow *window);
    static void AddCamera();
    //void AddCamera(Camera cam);


private:
    Mouse mouse;
    Camera camera;
};

#endif /* build_scene_hpp */
