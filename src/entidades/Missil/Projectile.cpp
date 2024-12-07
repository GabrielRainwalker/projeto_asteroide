//
// Created by T-Gamer on 06/12/2024.
//

#include "Projectile.h"
#include "recursos/TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>

Projectile::Projectile(const glm::vec2& pos, const glm::vec2& vel)
    : position(pos)
    , velocity(vel)
    , lifeTime(0.0f)
    , maxLifeTime(2.0f)
    , active(true)
    , exploding(false)
    , currentFrame(0.0f)
    , frameTime(0.05f)  // 20 frames por segundo
    , totalFrames(6)    // Número de frames na animação de explosão
{
    init();
}

Projectile::~Projectile() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete shader;
}

void Projectile::init() {
    shader = new Shader("../shaders/sprite.vert", "../shaders/sprite.frag");
    textureID = TextureManager::getInstance().loadTexture("../assets/nave.png");
    setupMesh();
}

void Projectile::setupMesh() {
    float vertices[] = {
        // Posições    // Coordenadas de textura
        -5.0f, -5.0f,  0.0f, 0.0f,
         5.0f, -5.0f,  0.166f, 0.0f,
         5.0f,  5.0f,  0.166f, 1.0f,
        -5.0f,  5.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Projectile::updateAnimation(float deltaTime) {
    if (exploding) {
        currentFrame += deltaTime / frameTime;

        if (currentFrame >= totalFrames) {
            active = false;
            return;
        }

        // Atualiza as coordenadas de textura
        float texOffset = (currentFrame / totalFrames);
        float vertices[] = {
            -5.0f, -5.0f,  texOffset, 0.0f,
             5.0f, -5.0f,  texOffset + 0.166f, 0.0f,
             5.0f,  5.0f,  texOffset + 0.166f, 1.0f,
            -5.0f,  5.0f,  texOffset, 1.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    }
}

void Projectile::update(float deltaTime) {
    if (!active) return;

    if (!exploding) {
        position += velocity * deltaTime;
        lifeTime += deltaTime;

        // Verifica limites da tela
        if (position.x < -10 || position.x > 810 ||
            position.y < -10 || position.y > 610) {
            startExplosion();
        }

        if (lifeTime >= maxLifeTime) {
            startExplosion();
        }
    }

    updateAnimation(deltaTime);
}

void Projectile::startExplosion() {
    exploding = true;
    currentFrame = 0.0f;
    velocity = glm::vec2(0.0f);
}

void Projectile::render() {
    if (!active) return;

    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    shader->setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}