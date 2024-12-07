//
// Created by T-Gamer on 06/12/2024.
//

#include "Asteroid.h"
#include "recursos/TextureManager.h"

Asteroid::Asteroid(float x, float y, float s)
    : position(x, y), size(s), isExploding(false) {
    // Inicialize o shader, textura e configure a mesh
    shader = new Shader("../shaders/sprite.vert", "../shaders/sprite.frag");
    textureID = TextureManager::getInstance().loadTexture("assets/asteroide.png");
    setupMesh();

    // Defina uma velocidade aleatória
    float angle = rand() % 360;
    float speed = 100.0f;
    velocity = glm::vec2(cos(glm::radians(angle)), sin(glm::radians(angle))) * speed;
}

Asteroid::~Asteroid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete shader;
}

void Asteroid::init() {
    shader = new Shader("../shaders/sprite.vert", "../shaders/sprite.frag");
    textureID = TextureManager::getInstance().loadTexture("assets/asteroide.png");
    setupMesh();
}

void Asteroid::setupMesh() {
    float vertices[] = {
        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.125f, 0.0f,
         0.5f,  0.5f,  0.125f, 1.0f,
        -0.5f,  0.5f,  0.0f, 1.0f
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

void Asteroid::updateAnimation(float deltaTime) {
    if (isExploding) {
        animationTimer += deltaTime;
        if (animationTimer >= frameTime) {
            animationTimer = 0;
            currentFrame++;

            // Atualiza as coordenadas de textura
            float texOffset = currentFrame / static_cast<float>(TOTAL_FRAMES);
            float vertices[] = {
                -0.5f, -0.5f,  texOffset, 0.0f,
                 0.5f, -0.5f,  texOffset + 0.125f, 0.0f,
                 0.5f,  0.5f,  texOffset + 0.125f, 1.0f,
                -0.5f,  0.5f,  texOffset, 1.0f
            };

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        }
    }
}

void Asteroid::update(float deltaTime) {
    if (!isExploding) {
        position += velocity * deltaTime;
        rotation += 45.0f * deltaTime;

        // Wrap around screen
        if (position.x < -50) position.x = 850;
        if (position.x > 850) position.x = -50;
        if (position.y < -50) position.y = 650;
        if (position.y > 650) position.y = -50;
    }

    updateAnimation(deltaTime);
}

void Asteroid::render() {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(size));

    shader->setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Asteroid::startExplosion() {
    isExploding = true;
    currentFrame = 0;
    velocity = glm::vec2(0.0f);
}

bool Asteroid::isDestroyed() const {
    return isExploding && currentFrame >= TOTAL_FRAMES;
}

bool Asteroid::checkCollision(const glm::vec2& point) const {
    if (isExploding) return false;

    float distance = glm::length(point - position);
    return distance < size * 0.4f;
}