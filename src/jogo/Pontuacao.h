//
// Created by T-Gamer on 05/12/2024.
//

#ifndef PONTUACAO_H
#define PONTUACAO_H

#include <imgui.h>
#include <string>

class Pontuacao {
public:
    Pontuacao();
    void adicionarPontos(int pontos);
    void adicionarAsteroideDestruido();
    void desenhar();
    void salvarRecorde();
    void carregarRecorde();
    void resetar();

private:
    int pontuacaoAtual;
    int recorde;
    int asteroidesDestruidos;
    bool novoRecorde;
};

#endif //PONTUACAO_H
