#include "menu.h"
#include <../../Library/include/GLFW/glfw3.h>

Menu::Menu() {
    // Construtor vazio por enquanto
}

void Menu::renderizar() {
    // Configuração da janela principal do menu
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Menu Principal", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar);

    // Centralização dos botões
    float larguraJanela = ImGui::GetWindowSize().x;
    float alturaJanela = ImGui::GetWindowSize().y;
    float larguraBotao = 200.0f;
    float alturaBotao = 50.0f;

    // Posicionamento vertical centralizado
    float espacoEntreBotoes = 20.0f;
    float alturaTotal = 3 * alturaBotao + 2 * espacoEntreBotoes;
    float posicaoInicialY = (alturaJanela - alturaTotal) * 0.5f;

    // Botão Jogar
    ImGui::SetCursorPos(ImVec2((larguraJanela - larguraBotao) * 0.5f, posicaoInicialY));
    if (ImGui::Button("Jogar", ImVec2(larguraBotao, alturaBotao))) {
        // Aqui vai o código para iniciar o jogo
    }

    // Botão Configurações
    ImGui::SetCursorPos(ImVec2((larguraJanela - larguraBotao) * 0.5f,
        posicaoInicialY + alturaBotao + espacoEntreBotoes));
    if (ImGui::Button("Configurações", ImVec2(larguraBotao, alturaBotao))) {
        mostrarConfiguracoes = true;
    }

    // Botão Créditos
    ImGui::SetCursorPos(ImVec2((larguraJanela - larguraBotao) * 0.5f,
        posicaoInicialY + 2 * alturaBotao + 2 * espacoEntreBotoes));
    if (ImGui::Button("Créditos", ImVec2(larguraBotao, alturaBotao))) {
        mostrarCreditos = true;
		ImGui::Text("Desenvolvido por: ");
        ImGui::Text("Gabriel Duarte Marques");
        ImGui::Text("Elter Rodrigues");
        ImGui::Text("Kauanne Julia");
        ImGui::Text("João Vitor Jardim");
    }

    ImGui::End();

    // Janela de Configurações
    if (mostrarConfiguracoes) {
        ImGui::Begin("Configurações", &mostrarConfiguracoes);
        ImGui::SetWindowSize(ImVec2(400, 300));
        ImGui::SetWindowPos(ImVec2((larguraJanela - 400) * 0.5f, (alturaJanela - 300) * 0.5f));

        // Adicione aqui as configurações do jogo
        ImGui::Text("Configurações do Jogo");

        ImGui::End();
    }

    // Janela de Créditos
    if (mostrarCreditos) {
        ImGui::Begin("Créditos", &mostrarCreditos);
        ImGui::SetWindowSize(ImVec2(400, 300));
        ImGui::SetWindowPos(ImVec2((larguraJanela - 400) * 0.5f, (alturaJanela - 300) * 0.5f));

        ImGui::Text("Desenvolvido por: [Seu Nome]");
        ImGui::Text("Versão 1.0");

        ImGui::End();
    }
}