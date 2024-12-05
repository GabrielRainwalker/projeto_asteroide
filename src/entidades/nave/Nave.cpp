#include "Nave.h"
#include <glfw3.h>
#include <algorithm>


const float Nave::TAMANHO_NAVE = 64.0f;
const glm::vec2 Nave::OFFSET_SPRITE_NAVE = glm::vec2(0.0f, 0.0f);
const glm::vec2 Nave::TAMANHO_SPRITE_NAVE = glm::vec2(0.125f, 0.125f);
const float Nave::TEMPO_ENTRE_TIROS = 0.2f;

void Nave::atirar() {
    float tempoAtual = glfwGetTime();
    if (tempoAtual - tempoUltimoTiro >= TEMPO_ENTRE_TIROS) {
        glm::vec2 direcaoTiro(cos(rotacao), sin(rotacao));
        misseis.emplace_back(posicao, direcaoTiro);
        tempoUltimoTiro = tempoAtual;
    }
}

void Nave::atualizarMisseis(float deltaTime) {
    for (auto& missil : misseis) {
        missil.atualizar(deltaTime);
    }

    // Remover mísseis inativos
    misseis.erase(
        std::remove_if(misseis.begin(), misseis.end(),
            [](const Missil& m) { return !m.estaAtivo(); }),
        misseis.end()
    );
}

void Nave::desenharMisseis() {
    for (auto& missil : misseis) {
        missil.desenhar();
    }
}

void Nave::desenhar() {
    GerenciadorTexturas::desenharSprite(
        texturaID,
        posicao,
        glm::vec2(TAMANHO_NAVE),
        OFFSET_SPRITE_NAVE,
        TAMANHO_SPRITE_NAVE,
        rotacao
    );
}