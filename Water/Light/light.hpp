//
//  light.hpp
//  Water
//
//  Created by sam on 2019-07-18.
//  Copyright © 2019 sam. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shader.hpp"
#include "../Build/build_scene.hpp"
#include "../point_data.hpp"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Light {
public:
    Light () {}
    void boxLight(Shader shader, Build build) {
        shader.Use( );
        shader.setVec3("viewPos", build.cameraList[build.camNum]->GetCameraPos());
        shader.setFloat("material.shininess", 64.0f);
        
        shader.setInt("dirLightNum", 1);
        shader.setVec3("dirLight[0].direction", -0.2f, -1.0f, -0.3f);
        shader.setVec3("dirLight[0].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("dirLight[0].diffuse", 0.4f, 0.4f, 0.4f);
        shader.setVec3("dirLight[0].specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        shader.setInt("pointLightNum", 4);
        shader.setVec3("pointLights[0].position", pointLightPositions[0]);
        shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[0].constant", 1.0f);
        shader.setFloat("pointLights[0].linear", 0.09);
        shader.setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        shader.setVec3("pointLights[1].position", pointLightPositions[1]);
        shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[1].constant", 1.0f);
        shader.setFloat("pointLights[1].linear", 0.09);
        shader.setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        shader.setVec3("pointLights[2].position", pointLightPositions[2]);
        shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[2].constant", 1.0f);
        shader.setFloat("pointLights[2].linear", 0.09);
        shader.setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        shader.setVec3("pointLights[3].position", pointLightPositions[3]);
        shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        shader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("pointLights[3].constant", 1.0f);
        shader.setFloat("pointLights[3].linear", 0.09);
        shader.setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        shader.setInt("spotLightNum", 2);
        shader.setVec3("spotLight[0].position", build.cameraList[build.camNum]->GetCameraPos());
        shader.setVec3("spotLight[0].direction", build.cameraList[build.camNum]->GetCameraFront());
        shader.setVec3("spotLight[0].ambient", 0.0f, 0.0f, 0.0f);
        shader.setVec3("spotLight[0].diffuse", 1.0f, 1.0f, 1.0f);
        shader.setVec3("spotLight[0].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("spotLight[0].constant", 1.0f);
        shader.setFloat("spotLight[0].linear", 0.09);
        shader.setFloat("spotLight[0].quadratic", 0.032);
        shader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(12.5f)));
        shader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(15.0f)));
        
        shader.setVec3("spotLight[1].position", glm::vec3(0.0f, 3.0f, 0.0f));
        shader.setVec3("spotLight[1].direction", glm::vec3(0.0f, -1.0f, 0.0f));
        shader.setVec3("spotLight[1].ambient", 0.0f, 0.0f, 0.0f);
        shader.setVec3("spotLight[1].diffuse", 1.0f, 1.0f, 1.0f);
        shader.setVec3("spotLight[1].specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("spotLight[1].constant", 1.0f);
        shader.setFloat("spotLight[1].linear", 0.045);
        shader.setFloat("spotLight[1].quadratic", 0.0075);
        shader.setFloat("spotLight[1].cutOff", glm::cos(glm::radians(12.5f)));
        shader.setFloat("spotLight[1].outerCutOff", glm::cos(glm::radians(15.0f)));
    }
    
    void modelLight(Shader shader, Build build, int shininess) {
        shader.Use();
        shader.setVec3("viewPos", build.cameraList[build.camNum]->GetCameraPos());
        shader.setVec3("light.position", glm::vec3(0.0f, 0.0f, 0.3f));
        shader.setVec3("light.ambient", glm::vec3(0.05f, 0.05f, 0.5f));
        shader.setVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setVec3("light.position", glm::vec3(1.0f, 1.0f, 1.0f));
    }
    
};


#endif /* light_hpp */
