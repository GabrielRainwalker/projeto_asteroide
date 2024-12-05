//
// Created by T-Gamer on 05/12/2024.
//

#ifndef MISSIL_H
#define MISSIL_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include "recursos/GerenciadorTexturas.h"

class Missil {
public:
    Missil(const glm::vec2& posicaoInicial, const glm::vec2& direcao);
    void atualizar(float deltaTime);
    void desenhar();
    bool estaAtivo() const { return ativo; }
    glm::vec2 getPosicao() const { return posicao; }

private:
    glm::vec2 posicao;
    glm::vec2 direcao;
    float velocidade;
    bool ativo;
    static const glm::vec2 OFFSET_SPRITE_MISSIL;
    static const glm::vec2 TAMANHO_SPRITE_MISSIL;
    static const float TAMANHO_MISSIL;
};


#endif //MISSIL_H
