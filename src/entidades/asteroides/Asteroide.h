//
// Created by T-Gamer on 05/12/2024.
//

#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include <glm/glm.hpp>
#include "recursos/GerenciadorTexturas.h"

class Asteroide {
public:
    Asteroide(const glm::vec2& posicao, float tamanho);
    void atualizar(float deltaTime);
    void desenhar();
    bool estaAtivo() const { return ativo; }
    bool verificarColisao(const glm::vec2& ponto, float raio) const;
    int getPontos() const { return pontos; }
    bool foiDestruido() const { return destruido; }
    void destruir() { destruido = true; }
    glm::vec2 getPosicao() const { return posicao; }
    float getRaio() const { return tamanho / 2.0f; }

private:
    glm::vec2 posicao;
    glm::vec2 direcao;
    float rotacao;
    float velocidadeRotacao;
    float velocidade;
    float tamanho;
    bool ativo;
    static const glm::vec2 OFFSET_SPRITE_ASTEROIDE;
    static const glm::vec2 TAMANHO_SPRITE_ASTEROIDE;
    bool destruido;
    int pontos;
};


#endif //ASTEROIDE_H
