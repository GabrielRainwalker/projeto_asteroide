//
// Created by T-Gamer on 05/12/2024.
//

#include "Missil.h"

const glm::vec2 Missil::OFFSET_SPRITE_MISSIL = glm::vec2(384.0f/512.0f, 448.0f/512.0f); // Ajuste conforme posição no sprite sheet
const glm::vec2 Missil::TAMANHO_SPRITE_MISSIL = glm::vec2(32.0f/512.0f, 32.0f/512.0f);
const float Missil::TAMANHO_MISSIL = 16.0f;

Missil::Missil(const glm::vec2& posicaoInicial, const glm::vec2& direcao)
    : posicao(posicaoInicial)
    , direcao(glm::normalize(direcao))
    , velocidade(500.0f)
    , ativo(true)
{
}

void Missil::atualizar(float deltaTime) {
    posicao += direcao * velocidade * deltaTime;

    // Desativar míssil se sair da tela
    if (posicao.x < -TAMANHO_MISSIL || posicao.x > 800 + TAMANHO_MISSIL ||
        posicao.y < -TAMANHO_MISSIL || posicao.y > 600 + TAMANHO_MISSIL) {
        ativo = false;
        }
}

void Missil::desenhar() {
    if (!ativo) return;

    GerenciadorTexturas::desenharSprite(
        "nave.png", // usando o mesmo sprite sheet da nave
        posicao,
        glm::vec2(TAMANHO_MISSIL),
        OFFSET_SPRITE_MISSIL,
        TAMANHO_SPRITE_MISSIL,
        atan2(direcao.y, direcao.x)
    );
}
