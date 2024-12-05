//
// Created by T-Gamer on 05/12/2024.
//

#include "entidades/asteroides/Asteroide.h"
#include "entidades/Missil/Missil.h"
#include <random>

class GerenciadorAsteroides {
public:
    void atualizar(float deltaTime);
    void desenhar();
    void criarAsteroide();
    void verificarColisoes(const std::vector<Missil>& misseis);
    int getPontuacao() const { return pontuacao; }

private:
    std::vector<Asteroide> asteroides;
    float tempoProximoAsteroide;
    int pontuacao;
    static const float INTERVALO_SPAWN;
};
