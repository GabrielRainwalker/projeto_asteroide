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
}

void GameManager::startGame() {
    isPlaying = true;
    isPaused = false;
    score = 0;

    playerShip = std::make_unique<Ship>(janela);
    playerShip->init();

    starSystem.init();
    spawnAsteroids(5);
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
    if (isPlaying) {
        float currentTime = glfwGetTime(); // Certifique-se de que glfwGetTime() é chamado após glfwInit()
        starSystem.update(deltaTime, currentTime);

        playerShip->update(deltaTime);

        for (auto& asteroid : asteroids) {
            asteroid->update(deltaTime);
        }

        CollisionManager::checkProjectileAsteroidCollisions(
            playerShip->getProjectiles(), asteroids, score);

        if (CollisionManager::checkShipAsteroidCollisions(
            playerShip.get(), asteroids)) {
            isPlaying = false;
            std::cout << "Fim de Jogo!" << std::endl;
            }
    }
}



void GameManager::render() {
    if (isPlaying) {
        starSystem.render();
        playerShip->render();

        for (const auto& asteroid : asteroids) {
            asteroid->render();
        }

        // Chame o renderHUD após renderizar os elementos do jogo
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

    // Define a posição e o tamanho da janela HUD
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Always);

    // Cria uma janela sem decoração para o HUD
    ImGui::Begin("HUD", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
                                    ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

    ImGui::Text("Pontuação: %d", score);

    ImGui::End();
}