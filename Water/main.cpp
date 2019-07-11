#include "point_data.h"

using namespace std;

glm::vec3 MoveCamera(GLFWwindow *window, GLfloat deltaTime, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);

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
    
    // since we don't change projection
    // move out of the while
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)W.Width / (GLfloat)W.Height, 0.1f, 100.0f);
    core_shader.setMat4("projection", projection);
    
    // set up camera axis
    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
    
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
        
        cam_pos = MoveCamera(W.window, deltaTime, cam_pos, cam_front, cam_up);
        
        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Bind textures
        W.BindTexture(texture1, 0);
        W.BindTexture(texture2, 1);
        
        core_shader.Use( );
        
        // rotate camera according to Y axis
        glm::mat4 view = glm::mat4(1.0f);
        view  = glm::lookAt(cam_pos, cam_front + cam_pos, cam_up);
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

glm::vec3 MoveCamera(GLFWwindow *window, GLfloat deltaTime, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
    GLfloat camSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camPos += camSpeed * camFront;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camPos -= camSpeed * camFront;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camPos += glm::normalize(glm::cross(camFront, camUp)) * camSpeed;
    }
    
    return camPos;
}
