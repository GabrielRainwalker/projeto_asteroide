#ifndef NAVE_H
#define NAVE_H

#include <glm/glm.hpp>
#include <recursos/GerenciadorTexturas.h>
#include <entidades/Missil/Missil.h>
#include <vector>

class Nave {
public:
    Nave(GerenciadorTexturas* gerenciador);
    void mover(const glm::vec2& direcao);
    void setRotacao(float angulo);
    void atirar();
    void atualizar(float deltaTime);
    void desenhar();
    glm::vec2 getPosicao() const;

    void atualizarMisseis(float deltaTime);
    void desenharMisseis();

private:
    glm::vec2 posicao;
    glm::vec2 velocidade;
    float rotacao;
    GLuint texturaID;
    static const float TAMANHO_NAVE;
    static const glm::vec2 OFFSET_SPRITE_NAVE;
    static const glm::vec2 TAMANHO_SPRITE_NAVE;

    std::vector<Missil> misseis;
    float tempoUltimoTiro;
    static const float TEMPO_ENTRE_TIROS;
};


#endif //NAVE_H