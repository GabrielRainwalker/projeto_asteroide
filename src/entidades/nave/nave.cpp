#include "nave.h"
#include <../../Library/include/GLFW/glfw3.h>

Nave::Nave() {
    posicao = glm::vec2(0.0f);
    velocidade = glm::vec2(0.0f);
    rotacao = 0.0f;
    aceleracao = 2.0f;
    velocidadeMaxima = 5.0f;
    atrito = 0.98f;
}

void Nave::atualizar(float deltaTime) {
    // Lógica de movimento da nave
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        rotacao += 180.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        rotacao -= 180.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_UP)) {
        float radianos = glm::radians(rotacao);
        glm::vec2 direcao(sin(radianos), cos(radianos));
        velocidade += direcao * aceleracao * deltaTime;
    }

    // Aplicar atrito
    velocidade *= atrito;

    // Atualizar posição
    posicao += velocidade * deltaTime;
}