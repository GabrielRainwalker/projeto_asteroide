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

// GerenciadorAsteroides.cpp
const float GerenciadorAsteroides::INTERVALO_SPAWN = 2.0f;

void GerenciadorAsteroides::criarAsteroide() {
    // Criar asteroide em uma posição aleatória fora da tela
    float angulo = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    glm::vec2 posicao(
        400.0f + cos(angulo) * 500.0f,
        300.0f + sin(angulo) * 500.0f
    );

    asteroides.emplace_back(posicao, 64.0f);
}

void GerenciadorAsteroides::verificarColisoes(const std::vector<Missil>& misseis) {
    for (auto& asteroide : asteroides) {
        if (!asteroide.estaAtivo()) continue;

        for (const auto& missil : misseis) {
            if (!missil.estaAtivo()) continue;

            if (asteroide.verificarColisao(missil.getPosicao(), 8.0f)) {
                asteroide.destruir();
                pontuacao++;
                break;
            }
        }
    }
}
