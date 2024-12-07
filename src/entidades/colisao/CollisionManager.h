//
// Created by T-Gamer on 06/12/2024.
//

// CollisionManager.h
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "entidades/nave/Ship.h"
#include "entidades/asteroides/Asteroid.h"
#include "entidades/Missil/Projectile.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class CollisionManager {
public:
    static bool checkCircleCollision(const glm::vec2& pos1, float radius1,
                                   const glm::vec2& pos2, float radius2);

    static void checkProjectileAsteroidCollisions(std::vector<std::unique_ptr<Projectile>>& projectiles,
                                                  std::vector<std::unique_ptr<Asteroid>>& asteroids,
                                                  int& score);

    static bool checkShipAsteroidCollisions(
        const Ship* ship,
        const std::vector<std::unique_ptr<Asteroid>>& asteroids);
};

#endif