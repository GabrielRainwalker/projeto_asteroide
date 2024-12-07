//
// Created by T-Gamer on 06/12/2024.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "entidades/nave/Ship.h"
#include "entidades/asteroides/Asteroid.h"
#include "entidades/colisao/CollisionManager.h"
#include "entidades/estrelas/StarSystem.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

class GameManager {
private:
    GLFWwindow* janela;
    bool isPlaying;
    bool isPaused;
    int score;
    std::unique_ptr<Ship> playerShip;
    std::vector<std::unique_ptr<Asteroid>> asteroids;
    void checkCollisions();
    bool checkCircleCollision(const glm::vec2& pos1, float radius1, const glm::vec2& pos2, float radius2);
    StarSystem starSystem;
    void spawnAsteroids(int count);
    void handleCollisions();
    void renderHUD();

public:
    GameManager(GLFWwindow* janela);
    ~GameManager() = default;

    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();

    void update(float deltaTime);
    void render();

    bool getIsPlaying() const { return isPlaying; }
    bool getIsPaused() const { return isPaused; }
    int getScore() const { return score; }

    Ship* getPlayerShip() const { return playerShip.get(); }
};


#endif
