#pragma once
#include <../../Library/include/glm/glm.hpp>

class Asteroide {
private:
    glm::vec2 posicao;
    glm::vec2 velocidade;
    float rotacao;
    float velocidadeRotacao;
    float tamanho;

public:
    Asteroide();
    void atualizar(float deltaTime);
    void renderizar();
    bool verificarColisao(const glm::vec2& outraPosicao);
};