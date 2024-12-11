//
// Created by T-Gamer on 06/12/2024.
//

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "GameManager.h"
#include <algorithm>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "entidades/asteroides/Asteroid.h"
#include "entidades/colisao/CollisionManager.h"
#include "entidades/Missil/Projectile.h"
#include "entidades/estrelas/StarSystem.h"
#include "recursos/TextureManager.h"

GameManager::GameManager(GLFWwindow* window) :
    janela(window),
    isPlaying(false),
    isPaused(false),
    score(0) {
    playerShip = std::make_unique<Ship>(window);
    if (playerShip) {
        playerShip->init();
    }

}

void GameManager::startGame() {
    std::cout << "Iniciando jogo..." << std::endl;

    isPlaying = true;
    isPaused = false;
    score = 0;

    if (!playerShip) {
        std::cout << "Criando nova nave..." << std::endl;
        playerShip = std::make_unique<Ship>(janela);
    }

    std::cout << "Inicializando nave..." << std::endl;
    playerShip->init();

    std::cout << "Inicializando sistema de estrelas..." << std::endl;
    starSystem.init();

    std::cout << "Criando asteroides..." << std::endl;
    spawnAsteroids(5);

    std::cout << "Jogo iniciado com sucesso!" << std::endl;
}

void GameManager::pauseGame() {
    isPaused = true;
}

void GameManager::resumeGame() {
    isPaused = false;
}

void GameManager::endGame() {
    isPlaying = false;
    playerShip.reset();
}

bool GameManager::checkCircleCollision(const glm::vec2& pos1, float radius1,
                                     const glm::vec2& pos2, float radius2) {
    float distance = glm::length(pos1 - pos2);
    return distance < (radius1 + radius2);
}

void GameManager::update(float deltaTime) {
    if (!isPlaying) return;

    if (!playerShip) {
        std::cerr << "Erro: playerShip é nullptr" << std::endl;
        return;
    }

    float currentTime = glfwGetTime();
    starSystem.update(deltaTime, currentTime);

    playerShip->update(deltaTime);

    for (auto& asteroid : asteroids) {
        asteroid->update(deltaTime);
    }

    if (CollisionManager::checkShipAsteroidCollisions(playerShip.get(), asteroids)) {
        std::cout << "Colisao detectada" << std::endl;
        isPlaying = false;
        std::cout << "Fim de Jogo" << std::endl;
    }
}

void GameManager::render() {
    if (!isPlaying) return;
    glClear(GL_COLOR_BUFFER_BIT);
    starSystem.render();

    if (isPlaying) {
        starSystem.render();
        playerShip->render();

        for (const auto& asteroid : asteroids) {
            asteroid->render();
        }

        renderHUD();
    }
}

void GameManager::spawnAsteroids(int count) {
    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(rand() % 800);
        float y = static_cast<float>(rand() % 600);
        float size = 50.0f;

        auto asteroid = std::make_unique<Asteroid>(x, y, size);
        asteroid->init();
        asteroids.push_back(std::move(asteroid));
    }
}
void GameManager::renderHUD() {

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Always);

    ImGui::Begin("HUD", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
                                    ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

    ImGui::Text("Score: %d", score);

    ImGui::End();
}