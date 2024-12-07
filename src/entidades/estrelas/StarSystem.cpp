//
// Created by T-Gamer on 06/12/2024.
//

#include "StarSystem.h"
#include <random>
#include <ext/matrix_transform.hpp>

StarSystem::StarSystem() {
    init();
}

StarSystem::~StarSystem() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
}

void StarSystem::init() {
    shader = new Shader("../shaders/star.vert", "../shaders/star.frag");
    setupMesh();
    createStars();
}

void StarSystem::setupMesh() {
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void StarSystem::createStars() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> yDist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> sizeDist(0.001f, 0.003f);
    std::uniform_real_distribution<float> brightDist(0.5f, 1.0f);
    std::uniform_real_distribution<float> pulseDist(0.5f, 2.0f);
    std::uniform_real_distribution<float> offsetDist(0.0f, 6.28f);

    stars.clear();
    for (int i = 0; i < NUM_STARS; i++) {
        Star star;
        star.position = glm::vec2(xDist(gen), yDist(gen));
        star.size = sizeDist(gen);
        star.brightness = brightDist(gen);
        star.pulseSpeed = pulseDist(gen);
        star.pulseOffset = offsetDist(gen);
        stars.push_back(star);
    }
}

void StarSystem::update(float deltaTime, float time) {
    for (auto& star : stars) {
        star.brightness = 0.5f + 0.5f * sin(time * star.pulseSpeed + star.pulseOffset);
    }
}

void StarSystem::render() {
    shader->use();
    glBindVertexArray(VAO);

    for (const auto& star : stars) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(star.position, 0.0f));
        model = glm::scale(model, glm::vec3(star.size));

        shader->setMat4("model", model);
        shader->setFloat("brightness", star.brightness);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}