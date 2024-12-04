#include "asteroide.h"
#include <random>

Asteroide::Asteroide() {
    // Inicialização com valores aleatórios
    float angulo = static_cast<float>(rand()) / RAND_MAX * 360.0f;
    float velocidadeInicial = 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.2f;

    velocidade.x = cos(glm::radians(angulo)) * velocidadeInicial;
    velocidade.y = sin(glm::radians(angulo)) * velocidadeInicial;

    velocidadeRotacao = -45.0f + static_cast<float>(rand()) / RAND_MAX * 90.0f;
    tamanho = 0.5f + static_cast<float>(rand()) / RAND_MAX * 1.0f;
}

void Asteroide::atualizar(float deltaTime) {
    rotacao += velocidadeRotacao * deltaTime;
    posicao += velocidade * deltaTime;

    // Wraparound na tela
    if (posicao.x > 800.0f) posicao.x = 0.0f;
    if (posicao.x < 0.0f) posicao.x = 800.0f;
    if (posicao.y > 600.0f) posicao.y = 0.0f;
    if (posicao.y < 0.0f) posicao.y = 600.0f;
}