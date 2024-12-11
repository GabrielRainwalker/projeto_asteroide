//
// Created by T-Gamer on 06/12/2024.
//

#ifndef STARSYSTEM_H
#define STARSYSTEM_H

#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include "../shaders/Shader.h"

class StarSystem {
private:
    struct Star {
        glm::vec2 position;
        float brightness;
        float pulseSpeed;
        float pulseOffset;
        float size;
    };

    std::vector<Star> stars;
    GLuint VAO, VBO;
    Shader* shader;
    const int NUM_STARS = 200;

    void setupMesh();
    void createStars();

public:
    StarSystem();
    ~StarSystem();

    void init();
    void update(float deltaTime, float time);
    void render();
};

#endif //STARSYSTEM_H
