//
// Created by T-Gamer on 05/12/2024.
//

#ifndef PONTUACAO_H
#define PONTUACAO_H

#include <imgui.h>
#include <string>

class Pontuacao {
public:
    int getPontuacaoAtual() const;
    int getAsteroidesDestruidos() const;
    bool isNovoRecorde() const;
    Pontuacao();
    void adicionarPontos(int pontos);
    void adicionarAsteroideDestruido();
    void desenhar();
    void salvarRecorde();
    void carregarRecorde();
    void resetar();

private:
    int pontuacaoAtual;
    int asteroidesDestruidos;
    bool novoRecorde;
    int recorde;
};

#endif //PONTUACAO_H
