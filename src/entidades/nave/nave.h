#pragma once
#include <../../Library/include/glm/glm.hpp>

class Nave {
private:
    glm::vec2 posicao;
    glm::vec2 velocidade;
    float rotacao;
    float aceleracao;
    float velocidadeMaxima;
    float atrito;

public:
    Nave();
    void atualizar(float deltaTime);
    void renderizar();
    glm::vec2 getPosicao() const;
};