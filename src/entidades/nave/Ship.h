#ifndef SHIP_H
#define SHIP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../shaders/Shader.h"
#include "entidades/Missil/Projectile.h"
#include <memory>
#include <vector>
#include <GLFW/glfw3.h>

class Ship {
public:
    Ship(GLFWwindow* window);
    ~Ship();

    void init();
    void update(float deltaTime);
    void render();
    void shoot();

    std::vector<std::unique_ptr<Projectile>>& getProjectiles() { return projectiles; }
    glm::vec2 getPosition() const { return position; }
    float getRotation() const { return rotation; }
    float getRadius() const { return 20.0f; }

private:
    GLFWwindow* window;
    glm::vec2 position;
    glm::vec2 velocity;
    float rotation;
    float speed;

    GLuint VAO, VBO, EBO;
    GLuint textureID;
    Shader* shader;
    std::vector<std::unique_ptr<Projectile>> projectiles;


    void setupMesh();
    void handleInput(float deltaTime);
    void updateProjectiles(float deltaTime);
};

#endif