#include "Asteroide.h"

Asteroide::Asteroide()
    : posicao(0.0f, 0.0f), direcao(0.0f, 0.0f), velocidade(0.0f), rotacao(0.0f), raio(20.0f), destruido(false) {
    texturaID = GerenciadorTexturas::carregarTextura("assets/asteroide.png");
}

Asteroide::Asteroide(const glm::vec2& posicao, float velocidade)
    : posicao(posicao), direcao(0.0f, 0.0f), velocidade(velocidade), rotacao(0.0f), raio(20.0f), destruido(false) {
    texturaID = GerenciadorTexturas::carregarTextura("assets/asteroide.png");
}

void Asteroide::desenhar() {
    GerenciadorTexturas::desenharSprite(texturaID, posicao, glm::vec2(40.0f, 40.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), rotacao);
}

void Asteroide::atualizar(float deltaTime) {
    posicao += direcao * velocidade * deltaTime;
}

glm::vec2 Asteroide::getPosicao() const {
    return posicao;
}

float Asteroide::getRaio() const {
    return raio;
}

void Asteroide::destruir() {
    destruido = true;
}

bool Asteroide::foiDestruido() const {
    return destruido;
}

bool Asteroide::estaAtivo() const {
    return !destruido;
}

bool Asteroide::verificarColisao(const glm::vec2& posicao, float raio) const {
    float distancia = glm::length(this->posicao - posicao);
    return distancia < (this->raio + raio);
}