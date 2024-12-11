//
// Created by T-Gamer on 06/12/2024.
//

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../shaders/Shader.h"

class Projectile {
private:
    glm::vec2 position;
    glm::vec2 velocity;
    float lifeTime;
    float maxLifeTime;
    bool active;
    bool exploding;

    float currentFrame;
    float frameTime;
    int totalFrames;

    GLuint VAO, VBO, EBO;
    GLuint textureID;
    Shader* shader;

    void setupMesh();
    void updateAnimation(float deltaTime);

public:
    Projectile(const glm::vec2& pos, const glm::vec2& vel);
    ~Projectile();

    void init();
    void update(float deltaTime);
    void render();
    void startExplosion();

    bool isActive() const { return active; }
    bool isExploding() const { return exploding; }
    glm::vec2 getPosition() const { return position; }
    float getRadius() const { return 5.0f; }
};

#endif
