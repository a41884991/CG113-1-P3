#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Mesh.h"
#include "ShaderProgram/ShaderProgram.h"

class Model
{
public:
    /*  函数   */
    Model(const char *path);
    void Render(ShaderProgram *program);

private:
    /*  模型数据  */
    std::vector<Mesh> meshes;
    std::vector<Texture> texture_loaded;
    std::string directory;
    /*  函数   */
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                              std::string typeName);
};
