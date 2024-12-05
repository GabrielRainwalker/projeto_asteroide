#include "Colisao.h"
#include "entidades/Missil/Missil.h"
#include "entidades/asteroides/Asteroide.h"

bool GerenciadorColisoes::verificarColisao(const Missil& missil, const Asteroide& asteroide) {
    return verificarColisaoCircular(
        missil.getPosicao(), missil.getRaio(),
        asteroide.getPosicao(), asteroide.getRaio()
    );
}

bool GerenciadorColisoes::verificarColisaoCircular(const glm::vec2& pos1, float raio1, const glm::vec2& pos2, float raio2) {
    float distancia = glm::length(pos1 - pos2);
    return distancia < (raio1 + raio2);
}