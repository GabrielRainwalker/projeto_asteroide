#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include <glm/glm.hpp>
#include "recursos/GerenciadorTexturas.h"

class Asteroide {
public:
    Asteroide();
    Asteroide(const glm::vec2& posicao, float velocidade);
    void desenhar();
    void atualizar(float deltaTime);
    glm::vec2 getPosicao() const;
    float getRaio() const;
    void destruir();
    bool foiDestruido() const;
    bool estaAtivo() const;
    bool verificarColisao(const glm::vec2& posicao, float raio) const;

private:
    glm::vec2 posicao;
    glm::vec2 direcao;
    float velocidade;
    float rotacao;
    float raio;
    bool destruido;
    GLuint texturaID;
};

#endif // ASTEROIDE_H