#include "asset-loader.hpp"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "assimp/include/assimp/postprocess.h"
#include "elgine.hpp"
#include "opengl.hpp"
#include "stb_image.hpp"
#include "vertex.hpp"

std::vector<TextureData> AssetLoader::Textures;

const char* AssetLoader::ASSET_PATH = "assets/";

Texture AssetLoader::HasTexture(const char* path) {
    for (auto& tex : Textures)
        if (tex.path == path) return tex.id;

    return 0;
}

void AssetLoader::LoadMesh(const char* path, Mesh* outMesh) {
    std::string p;
    p += ASSET_PATH;
    p += path;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(p.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR:ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    // std::cout << scene->mNumMeshes << std::endl;

    std::vector<aiMesh*> meshes;
    aiMesh* mesh = scene->mMeshes[0];

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Extract vertex data
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vx;

        const aiVector3D& pos = mesh->mVertices[i];
        vx.position           = {pos.x, pos.y, pos.z};

        if (mesh->HasNormals()) {
            const aiVector3D& normal = mesh->mNormals[i];
            vx.normal                = {normal.x, normal.y, normal.z};
        }

        if (mesh->HasVertexColors(i)) {
            const aiColor4D* color = mesh->mColors[i];
            vx.color               = {color->r, color->g, color->b, color->a};
        }

        if (mesh->HasTextureCoords(0)) {
            const aiVector3D& uv = mesh->mTextureCoords[0][i];
            vx.uv                = {uv.x, uv.y};
        }

        vertices.push_back(vx);
    }

    // Extract index data
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    outMesh->SetMesh(vertices, indices);
}

Texture AssetLoader::LoadTexture(const char* path) {
    Texture texture;
    int width, height, bpp;
    std::string asset_path;

    if ((texture = HasTexture(path)) != 0) {
        Textures[texture - 1].dependents++;
        return texture;
    }

    asset_path += ASSET_PATH;
    asset_path += path;
    stbi_set_flip_vertically_on_load(1);
    const unsigned char* buffer = stbi_load(asset_path.c_str(), &width, &height, &bpp, 4);

    if (!buffer) std::cout << "Failed to load texture " << path << std::endl;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum err = glGetError();
    if (err) std::cout << "Failed to generate texture, ERR: " << err << std::endl;

    stbi_image_free((void*)buffer);

    TextureData data = TextureData(texture, width, height, bpp, path);
    Textures.insert(Textures.begin() + texture - 1, data);

    return texture;
}

void AssetLoader::UnloadTexture(const Texture texture) {
    if (Textures.size() <= texture - 1) return;
    Textures[texture - 1].dependents--;
    if (Textures[texture - 1].dependents == 0) glDeleteTextures(1, &texture);
}
