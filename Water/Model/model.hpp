//
//  model.hpp
//  Water
//
//  Created by sam on 2019-07-18.
//  Copyright © 2019 sam. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../StbImage/stb_image.h"
#include "../Mesh/mesh.hpp"
#include "../Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
    /*  Model Data */
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    
    // constructor, expects a filepath to a 3D model.
    Model(string const &path, bool gamma = false);
    
    // draws the model, and thus all its meshes
    void Draw(Shader shader);
    
private:
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif /* model_hpp */
