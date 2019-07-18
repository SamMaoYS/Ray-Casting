#include "point_data.h"
#include "Build/build_scene.hpp"

int main( )
{
//    // Create Window
    Window W("Water", 800, 600);
    glfwMakeContextCurrent( W.window );

    glEnable(GL_DEPTH_TEST);

    // Initialize GLEW
    W.InitializeGLEW();

    // Define the viewport dimensions
    W.DefineViewPort();
    
    Build build;
    build.AddCamera();
    
    build.SetUpWindowInteractive(W.window);
    

    // Build and compile shader program
    Shader boxShader( "resources/shaders/core.vs", "resources/shaders/core.frag" );
    Shader lightShader( "resources/shaders/light.vs", "resources/shaders/light.frag" );

    vector<int> attributeSize = {3, 3, 2};
    W.GetAttributeInfo(attributeSize);

    // Setup VAO, VBO, EBO
    GLuint boxVAO, boxVBO;
    W.SetUpBuffers(box_norm_texture, &boxVAO, &boxVBO);
    
    vector<int> attributeSize2 = {3};
    W.GetAttributeInfo(attributeSize2);
    GLuint lightVAO, lightVBO;
    W.SetUpBuffers(box, &lightVAO, &lightVBO);
    

	GLuint diffuseMap, specularMap;
    // value 1 indicates GL_RGB, value 0 indicates GL_RGBA
    W.LoadTexture(&diffuseMap, "resources/images/container2.png", 0);
    W.LoadTexture(&specularMap, "resources/images/container2_specular.png", 0);

    // Bind uniform texture value
    boxShader.Use();
    boxShader.setInt("material.diffuse", 0);
    boxShader.setInt("material.specular", 1);

    // init timing
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    
    glm::vec3 lightPos(0.0f, 1.0f, 5.0f);
    // Game loop
    while ( !glfwWindowShouldClose( W.window ) )
    {
        // Check if any events have been activiated
        glfwPollEvents( );
        
        // get per-frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        build.KeyPress(W.window, deltaTime);
        build.MouseCallBack(W.window);

        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind textures
        W.BindTexture(diffuseMap, 0);
        W.BindTexture(specularMap, 1);
        
        boxShader.Use( );
        boxShader.setVec3("light.position", build.cameraList[build.camNum]->GetCameraPos());
        boxShader.setVec3("light.direction", build.cameraList[build.camNum]->GetCameraFront());
        boxShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        boxShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        boxShader.setVec3("viewPos", build.cameraList[build.camNum]->GetCameraPos());
        
        boxShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        boxShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        boxShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        boxShader.setFloat("light.constant", 1.0f);
        boxShader.setFloat("light.linear", 0.045f);
        boxShader.setFloat("light.quadratic", 0.0075f);
        boxShader.setFloat("material.shininess", 32.0f);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(build.cameraList[build.camNum]->GetCameraZoom(), (GLfloat)W.Width / (GLfloat)W.Height, 0.1f, 100.0f);
        boxShader.setMat4("projection", projection);

        // rotate camera according to Y axis
        glm::mat4 view = build.cameraList[build.camNum]->GetCameraLookAt();
        boxShader.setMat4("view", view);

        glBindVertexArray(boxVAO);
        for (unsigned int i=0; i<10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            boxShader.setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
        
//        lightShader.Use();
//        lightShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
//
//        lightShader.setMat4("projection", projection);
//        lightShader.setMat4("view", view);
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
//        lightShader.setMat4("model", model);
//        
//        glBindVertexArray(lightVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers( W.window );
    }

    // De-allocate VAO, VBO, EBO
    W.DeleteBuffers(&boxVAO, &boxVBO);
    W.DeleteBuffers(&lightVAO, &lightVBO);

    // Terminate GLFW
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
