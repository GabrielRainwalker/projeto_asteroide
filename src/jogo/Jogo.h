#ifndef JOGO_H
#define JOGO_H

#include "entidades/asteroides/Asteroide.h"
#include "entidades/Missil/Missil.h"
#include "jogo/Pontuacao.h"
#include <vector>

class GerenciadorJogo {
public:
    GerenciadorJogo();
    void atualizar(float deltaTime);
    void desenhar();
    void verificarColisoes();
    int getPontuacao() const { return pontuacao; }
    void mostrarTelaFinal();

private:
    std::vector<Asteroide> asteroides;
    std::vector<Missil>* misseis;
    int pontuacao;
    float tempoProximoAsteroide;

    Pontuacao pontuacao;
    bool jogoFinalizado;

    void criarNovoAsteroide();
    void atualizarPontuacao();
    void desenharPontuacao();
};

#endif //JOGO_H