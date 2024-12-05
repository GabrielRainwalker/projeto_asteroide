//
// Created by T-Gamer on 05/12/2024.
//

#include "Controles.h"

Controles::Controles(GLFWwindow* window, Nave* nave)
    : window(window),
      nave(nave),
      atirando(false),
      velocidadeMovimento(300.0f) {
    // Capturar o mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Controles::processarEntradas(float deltaTime) {
    // Movimento da nave
    glm::vec2 direcao(0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        direcao.y -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        direcao.y += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        direcao.x -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        direcao.x += 1.0f;

    // Normalizar o vetor de direção
    if (glm::length(direcao) > 0.0f) {
        direcao = glm::normalize(direcao);
    }

    // Atualizar posição da nave
    nave->mover(direcao * velocidadeMovimento * deltaTime);

    // Processar mouse para rotação e tiro
    processarMouse();
}

void Controles::processarMouse() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Calcular ângulo de rotação baseado na posição do mouse
    glm::vec2 posicaoNave = nave->getPosicao();
    glm::vec2 direcaoMouse(xpos - posicaoNave.x, ypos - posicaoNave.y);
    float angulo = atan2(direcaoMouse.y, direcaoMouse.x);

    // Atualizar rotação da nave
    nave->setRotacao(angulo);

    // Verificar tiro
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !atirando) {
        nave->atirar();
        atirando = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        atirando = false;
    }
}