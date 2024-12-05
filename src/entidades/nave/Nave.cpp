#include "Nave.h"
#include <algorithm>

const float Nave::TAMANHO_NAVE = 50.0f;
const glm::vec2 Nave::OFFSET_SPRITE_NAVE = glm::vec2(0.0f, 0.0f); // Ajuste conforme posição no sprite sheet
const glm::vec2 Nave::TAMANHO_SPRITE_NAVE = glm::vec2(64.0f/512.0f, 64.0f/512.0f);

Nave::Nave(GerenciadorTexturas* gerenciadorTexturas)
    : gerenciadorTexturas(gerenciadorTexturas), posicao(400.0f, 300.0f), offset(0.0f, 0.0f), escala(1.0f, 1.0f), rotacao(0.0f) {
    texturaID = GerenciadorTexturas::carregarTextura("assets/nave.png");
}

void Nave::desenhar() {
    GerenciadorTexturas::desenharSprite(texturaID, posicao, glm::vec2(TAMANHO_NAVE, TAMANHO_NAVE), OFFSET_SPRITE_NAVE, TAMANHO_SPRITE_NAVE, rotacao);
    desenharMisseis();
}

void Nave::atualizar(float deltaTime) {
    for (auto& missil : misseis) {
        missil.atualizar(deltaTime);
    }
    misseis.erase(std::remove_if(misseis.begin(), misseis.end(), [](const Missil& missil) { return !missil.estaAtivo(); }), misseis.end());
}

void Nave::desenharMisseis() {
    for (const auto& missil : misseis) {
        missil.desenhar();
    }
}

void Nave::mover(const glm::vec2& direcao) {
    posicao += direcao;
}

glm::vec2 Nave::getPosicao() const {
    return posicao;
}

void Nave::setRotacao(float angulo) {
    rotacao = angulo;
}

void Nave::atirar() {
    glm::vec2 direcao = glm::vec2(cos(rotacao), sin(rotacao));
    misseis.emplace_back(posicao, direcao);
}