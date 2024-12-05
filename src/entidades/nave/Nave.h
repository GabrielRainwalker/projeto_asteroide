#ifndef NAVE_H
#define NAVE_H

#include <glm/glm.hpp>
#include <vector>
#include "recursos/GerenciadorTexturas.h"
#include "entidades/Missil/Missil.h"

class Nave {
public:
    Nave(GerenciadorTexturas* gerenciadorTexturas);
    void desenhar();
    void atualizar(float deltaTime);
    void desenharMisseis();
    void mover(const glm::vec2& direcao);
    glm::vec2 getPosicao() const;
    void setRotacao(float angulo);
    void atirar();

private:
    glm::vec2 posicao;
    glm::vec2 offset;
    glm::vec2 escala;
    float rotacao;
    GerenciadorTexturas* gerenciadorTexturas;
    GLuint texturaID;
    std::vector<Missil> misseis;
    static const float TAMANHO_NAVE;
    static const glm::vec2 OFFSET_SPRITE_NAVE;
    static const glm::vec2 TAMANHO_SPRITE_NAVE;
};

#endif // NAVE_H