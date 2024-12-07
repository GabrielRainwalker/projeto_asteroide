#include "recursos/TextureManager.h"
#include "Ship.h"
#include <algorithm>



Ship::Ship(GLFWwindow* window) :
    window(window),
    position(400.0f, 300.0f),
    velocity(0.0f),
    rotation(0.0f),
    speed(200.0f) {
}

Ship::~Ship() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete shader;
}

void Ship::init() {
    shader = new Shader("../shaders/sprite.vert", "../shaders/sprite.frag");

    textureID = TextureManager::getInstance().loadTexture("assets/nave.png");

    setupMesh();
}

void Ship::setupMesh() {
    float vertices[] = {
        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
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

void Ship::handleInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        rotation += 180.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        rotation -= 180.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        float radians = glm::radians(rotation);
        velocity.x = -sin(radians) * speed;
        velocity.y = cos(radians) * speed;
    } else {
        velocity *= 0.98f;
    }
}

void Ship::shoot() {
    float radians = glm::radians(rotation);
    glm::vec2 direction = glm::vec2(-sin(radians), cos(radians));
    glm::vec2 projectilePosition = position + direction * 20.0f;
    glm::vec2 projectileVelocity = direction * 500.0f;

    projectiles.push_back(std::make_unique<Projectile>(projectilePosition, projectileVelocity));
}

void Ship::update(float deltaTime) {
    handleInput(deltaTime);
    position += velocity * deltaTime;

    updateProjectiles(deltaTime);
}

void Ship::updateProjectiles(float deltaTime) {
    for (auto& projectile : projectiles) {
        projectile->update(deltaTime);
    }

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                     [](const std::unique_ptr<Projectile>& p) { return !p->isActive(); }),
                      projectiles.end());
}

void Ship::render() {
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    shader->setMat4("model", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for (auto& projectile : projectiles) {
        projectile->render();
    }
}