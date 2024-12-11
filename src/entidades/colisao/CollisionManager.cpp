//
// Created by T-Gamer on 06/12/2024.
//

#include "CollisionManager.h"


bool CollisionManager::checkCircleCollision(const glm::vec2& pos1, float radius1,
                                            const glm::vec2& pos2, float radius2) {
    float distance = glm::length(pos1 - pos2);
    return distance < (radius1 + radius2);
}

void CollisionManager::checkProjectileAsteroidCollisions(
    std::vector<std::unique_ptr<Projectile>>& projectiles,
    std::vector<std::unique_ptr<Asteroid>>& asteroids,
    int& score) {

    for (auto& projectile : projectiles) {
        if (!projectile->isActive()) continue;

        for (auto& asteroid : asteroids) {
            if (asteroid->isDestroyed()) continue;

            if (checkCircleCollision(projectile->getPosition(), projectile->getRadius(),
                                     asteroid->getPosition(), asteroid->getSize() * 0.5f)) {
                projectile->startExplosion();
                asteroid->startExplosion();
                score += 10;
                break;
                                     }
        }
    }
}

bool CollisionManager::checkShipAsteroidCollisions(
    const Ship* ship,
    const std::vector<std::unique_ptr<Asteroid>>& asteroids) {

    if (!ship) return false;

    const float SAFE_START_TIME = 2.0f;
    static float gameStartTime = glfwGetTime();

    if (glfwGetTime() - gameStartTime < SAFE_START_TIME) {
        return false;
    }

    for (const auto& asteroid : asteroids) {
        if (!asteroid || asteroid->isDestroyed()) continue;

        float distance = glm::length(ship->getPosition() - asteroid->getPosition());
        float minDistance = ship->getRadius() + asteroid->getRadius() * 0.8f;

        if (distance < minDistance) {
            return true;
        }
    }
    return false;
}