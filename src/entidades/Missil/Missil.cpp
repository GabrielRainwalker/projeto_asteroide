#include "Missil.h"
#include "recursos/GerenciadorTexturas.h"

Missil::Missil(const glm::vec2& posicao, const glm::vec2& direcao)
    : posicao(posicao), direcao(direcao), ativo(true), raio(5.0f) {
}

void Missil::atualizar(float deltaTime) {
    posicao += direcao * deltaTime * 500.0f; // Velocidade do míssil
}

void Missil::desenhar() const {
    GerenciadorTexturas::desenharSprite(GerenciadorTexturas::carregarTextura("assets/nave.png"), posicao, glm::vec2(10.0f, 10.0f), glm::vec2(64.0f/512.0f, 0.0f), glm::vec2(32.0f/512.0f, 32.0f/512.0f), 0.0f);
}

bool Missil::estaAtivo() const {
    return ativo;
}

void Missil::desativar() {
    ativo = false;
}

glm::vec2 Missil::getPosicao() const {
    return posicao;
}

float Missil::getRaio() const {
    return raio;
}