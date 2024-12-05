#ifndef JOGO_H
#define JOGO_H

#include "entidades/asteroides/Asteroide.h"
#include "entidades/Missil/Missil.h"
#include "jogo/Pontuacao.h"
#include <vector>

class GerenciadorJogo {
public:
    GerenciadorJogo();
    void criarEfeitoExplosao(const glm::vec2& posicao);
    void reiniciarJogo();
    void voltarParaMenu();
    void atualizar(float deltaTime);
    void desenhar();
    void verificarColisoes();
    bool isJogoFinalizado() const { return jogoFinalizado; }
    void desenharPontuacao();
    Pontuacao& getPontuacao() { return pontuacao; }
    void mostrarTelaFinal();

private:
    std::vector<Asteroide> asteroides;
    std::vector<Missil>* misseis;
    float tempoProximoAsteroide;

    Pontuacao pontuacao;
    bool jogoFinalizado;

    void criarNovoAsteroide();
    void atualizarPontuacao();
};

#endif //JOGO_H