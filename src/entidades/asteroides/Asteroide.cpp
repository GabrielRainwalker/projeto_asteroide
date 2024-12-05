#include "Asteroide.h"
#include <random>

const glm::vec2 Asteroide::OFFSET_SPRITE_ASTEROIDE = glm::vec2(384.0f/512.0f, 384.0f/512.0f); // Ajuste conforme sprite sheet
const glm::vec2 Asteroide::TAMANHO_SPRITE_ASTEROIDE = glm::vec2(64.0f/512.0f, 64.0f/512.0f);

Asteroide::Asteroide(const glm::vec2& posicao, float tamanho)
    : posicao(posicao)
    , tamanho(tamanho)
    , ativo(true)
{
    // Inicializar com direção e velocidade aleatórias
    float angulo = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    direcao = glm::vec2(cos(angulo), sin(angulo));
    velocidade = 100.0f + static_cast<float>(rand()) / RAND_MAX * 100.0f;
    velocidadeRotacao = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f;
    rotacao = 0.0f;
}

void Asteroide::atualizar(float deltaTime) {
    if (!ativo) return;

    posicao += direcao * velocidade * deltaTime;
    rotacao += velocidadeRotacao * deltaTime;

    // Wrap around na tela
    if (posicao.x < -tamanho) posicao.x = 800 + tamanho;
    if (posicao.x > 800 + tamanho) posicao.x = -tamanho;
    if (posicao.y < -tamanho) posicao.y = 600 + tamanho;
    if (posicao.y > 600 + tamanho) posicao.y = -tamanho;
}

void Asteroide::desenhar() {
    if (!ativo) return;

    GerenciadorTexturas::desenharSprite(
        "asteroide", // usando o mesmo sprite sheet
        posicao,
        glm::vec2(tamanho),
        OFFSET_SPRITE_ASTEROIDE,
        TAMANHO_SPRITE_ASTEROIDE,
        rotacao
    );
}

bool Asteroide::verificarColisao(const glm::vec2& ponto, float raio) const {
    if (!ativo) return false;

    float distancia = glm::length(ponto - posicao);
    return distancia < (tamanho/2 + raio);
}