//
// Created by T-Gamer on 06/12/2024.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shaders/Shader.h"

class Asteroid {
private:
    glm::vec2 position;
    glm::vec2 velocity;
    float rotation;
    float size;
    float currentFrame;
    bool isExploding;

    GLuint VAO, VBO, EBO;
    GLuint textureID;
    Shader* shader;

    const int TOTAL_FRAMES = 8;
    float frameTime;
    float animationTimer;

    void setupMesh();
    void updateAnimation(float deltaTime);

public:
    Asteroid(float x, float y, float size);
    ~Asteroid();

    void init();
    void update(float deltaTime);
    void render();
    void startExplosion();
    bool isDestroyed() const;

    // Colisão
    bool checkCollision(const glm::vec2& point) const;
    glm::vec2 getPosition() const { return position; }
    float getSize() const { return size; }
    float getRadius() const { return size * 0.5f; }
};

#endif