#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <glad/glad.h>
#include <string>
#include <map>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    GLuint loadTexture(const std::string& path);
    void deleteTexture(GLuint textureID);
    void deleteAllTextures();

private:
    TextureManager() {}
    std::map<std::string, GLuint> textureMap;
};

#endif