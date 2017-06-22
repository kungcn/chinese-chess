//
// Created by hao on 4/22/17.
//

#ifndef CG_PROJECT_MODEL_H
#define CG_PROJECT_MODEL_H

#include "Header.h"
#include "Shader.h"
#include "Mesh.h"

class Model
{
public:
    /*  成员函数   */
    Model(GLchar* path);
    void Draw(Shader &shader);
private:
    /*  模型数据  */
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;

    /*  私有成员函数   */
    void loadModel(const string &path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string &typeName);
};


#endif //CG_PROJECT_OBJECT_H
