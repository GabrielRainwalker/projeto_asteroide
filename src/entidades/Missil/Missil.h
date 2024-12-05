#ifndef MISSIL_H
#define MISSIL_H

#include <glm/glm.hpp>

class Missil {
public:
    Missil(const glm::vec2& posicao, const glm::vec2& direcao);
    void atualizar(float deltaTime);
    void desenhar() const;
    bool estaAtivo() const;
    void desativar();
    glm::vec2 getPosicao() const;
    float getRaio() const;

private:
    glm::vec2 posicao;
    glm::vec2 direcao;
    bool ativo;
    float raio;
};

#endif // MISSIL_H