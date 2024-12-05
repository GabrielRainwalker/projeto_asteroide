//
// Created by T-Gamer on 05/12/2024.
//

#include "Pontuacao.h"

#include <fstream>

Pontuacao::Pontuacao() :
    pontuacaoAtual(0),
    recorde(0),
    asteroidesDestruidos(0),
    novoRecorde(false)
{
    carregarRecorde();
}

void Pontuacao::adicionarPontos(int pontos) {
    pontuacaoAtual += pontos;
    if (pontuacaoAtual > recorde) {
        recorde = pontuacaoAtual;
        novoRecorde = true;
    }
}

void Pontuacao::adicionarAsteroideDestruido() {
    asteroidesDestruidos++;
    adicionarPontos(100); // 100 pontos por asteroide
}

void Pontuacao::desenhar() {
    // HUD durante o jogo
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("Pontuação", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove);

    ImGui::Text("Pontuação: %d", pontuacaoAtual);
    ImGui::Text("Asteroides Destruídos: %d", asteroidesDestruidos);
    ImGui::Text("Recorde: %d", recorde);

    if (novoRecorde) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "NOVO RECORDE!");
    }

    ImGui::End();
}

void Pontuacao::salvarRecorde() {
    std::ofstream arquivo("recorde.dat", std::ios::binary);
    if (arquivo.is_open()) {
        arquivo.write(reinterpret_cast<char*>(&recorde), sizeof(recorde));
        arquivo.close();
    }
}

void Pontuacao::carregarRecorde() {
    std::ifstream arquivo("recorde.dat", std::ios::binary);
    if (arquivo.is_open()) {
        arquivo.read(reinterpret_cast<char*>(&recorde), sizeof(recorde));
        arquivo.close();
    }
}

void Pontuacao::resetar() {
    pontuacaoAtual = 0;
    asteroidesDestruidos = 0;
    novoRecorde = false;
}