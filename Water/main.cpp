#include "point_data.h"
#include "Camera/camera.hpp"
#include "Mouse/mouse.hpp"

using namespace std;

void KeyPressCallBack(GLFWwindow *window, GLfloat deltaTime);
void MouseCallBack(GLFWwindow *window);
void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset);

Camera camera;
Mouse mouse;

int main( )
{
    // Create Window
    Window W("Water", 800, 600);
    glfwMakeContextCurrent( W.window );
    
    glEnable(GL_DEPTH_TEST);
    
    // Initialize GLEW
    W.InitializeGLEW();
    
    // Define the viewport dimensions
    W.DefineViewPort();
    
    glfwSetScrollCallback(W.window, ScrollCallBack);
    glfwSetInputMode(W.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Build and compile shader program
    Shader core_shader( "resources/shaders/core.vs", "resources/shaders/core.frag" );

    vector<int> attributeSize = {3, 2};
    W.GetAttributeInfo(attributeSize);

    // Setup VAO, VBO, EBO
    W.SetUpBuffers(vertices);
    
    GLuint texture1, texture2;
    // value 1 indicates GL_RGB, value 0 indicates GL_RGBA
    W.LoadTexture(&texture1, "resources/images/container.jpg", 1);
    W.LoadTexture(&texture2, "resources/images/awesomeface.png", 0);

	// Bind uniform texture value
    core_shader.Use();
    core_shader.setInt("texture1", 0);
    core_shader.setInt("texture2", 1);
    
    // init timing
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    
    // Game loop
    while ( !glfwWindowShouldClose( W.window ) )
    {
        // get per-frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        KeyPressCallBack(W.window, deltaTime);
        MouseCallBack(W.window);
        
        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Bind textures
        W.BindTexture(texture1, 0);
        W.BindTexture(texture2, 1);
        
        core_shader.Use( );
        
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(camera.GetCameraZoom(), (GLfloat)W.Width / (GLfloat)W.Height, 0.1f, 100.0f);
        core_shader.setMat4("projection", projection);
        
        // rotate camera according to Y axis
        glm::mat4 view = camera.GetCameraLookAt();
        core_shader.setMat4("view", view);
        
        // Draw the triangle
        glBindVertexArray(W.VAO);
        for (unsigned int i=0; i<10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            core_shader.setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers( W.window );
        // Check if any events have been activiated
        glfwPollEvents( );
    }
    
    // De-allocate VAO, VBO, EBO
    W.DeleteBuffers();
    
    // Terminate GLFW
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}

void KeyPressCallBack(GLFWwindow *window, GLfloat deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.MoveCamera(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.MoveCamera(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.MoveCamera(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.MoveCamera(RIGHT, deltaTime);
    }
    
    //reset camera
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera = Camera();
    }
}

void MouseCallBack(GLFWwindow *window) {
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
    
    camera.RotateCamera(xOffset, yOffset);
}
void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset) {
    camera.ZoomCamera(yOffset);
}
