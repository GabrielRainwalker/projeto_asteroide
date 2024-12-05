//
// Created by T-Gamer on 05/12/2024.
//

#include <imgui.h>
#include "jogo/Jogo.h"
#include "../entidades/colisao/Colisao.h"

void GerenciadorJogo::verificarColisoes() {
    for (auto& asteroide : asteroides) {
        if (asteroide.foiDestruido()) continue;

        for (auto& missil : *misseis) {
            if (!missil.estaAtivo()) continue;

            if (GerenciadorColisoes::verificarColisao(missil, asteroide)) {
                asteroide.destruir();
                missil.desativar();
                pontuacao.adicionarAsteroideDestruido();
                criarEfeitoExplosao(asteroide.getPosicao());
            }
            }
        }
    }
}

void GerenciadorJogo::desenharPontuacao() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("Pontuação", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove);

    ImGui::Text("Pontos: %d", pontuacao);
    ImGui::End();
}
void GerenciadorJogo::mostrarTelaFinal() {
    if (!jogoFinalizado) return;

    ImGui::SetNextWindowPos(ImVec2(400, 300), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("Fim de Jogo", nullptr,
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoMove);

    ImGui::Text("GAME OVER");
    ImGui::Separator();
    ImGui::Text("Pontuação Final: %d", pontuacao.getPontuacaoAtual());
    ImGui::Text("Asteroides Destruídos: %d", pontuacao.getAsteroidesDestruidos());

    if (pontuacao.isNovoRecorde()) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f),
            "PARABÉNS! NOVO RECORDE!");
    }

    if (ImGui::Button("Jogar Novamente")) {
        reiniciarJogo();
    }

    if (ImGui::Button("Menu Principal")) {
        voltarParaMenu();
    }

    ImGui::End();
}