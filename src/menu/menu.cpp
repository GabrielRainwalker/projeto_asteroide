#include "menu.h"
#include <../../Library/include/GLFW/glfw3.h>

Menu::Menu() {
    // Construtor vazio por enquanto
}

void Menu::renderizar() {
    // Configura��o da janela principal do menu
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Menu Principal", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar);

    // Centraliza��o dos bot�es
    float larguraJanela = ImGui::GetWindowSize().x;
    float alturaJanela = ImGui::GetWindowSize().y;
    float larguraBotao = 200.0f;
    float alturaBotao = 50.0f;

    // Posicionamento vertical centralizado
    float espacoEntreBotoes = 20.0f;
    float alturaTotal = 3 * alturaBotao + 2 * espacoEntreBotoes;
    float posicaoInicialY = (alturaJanela - alturaTotal) * 0.5f;

    // Bot�o Jogar
    ImGui::SetCursorPos(ImVec2((larguraJanela - larguraBotao) * 0.5f, posicaoInicialY));
    if (ImGui::Button("Jogar", ImVec2(larguraBotao, alturaBotao))) {
        // Aqui vai o c�digo para iniciar o jogo
    }

    // Bot�o Configura��es
    ImGui::SetCursorPos(ImVec2((larguraJanela - larguraBotao) * 0.5f,
        posicaoInicialY + alturaBotao + espacoEntreBotoes));
    if (ImGui::Button("Configura��es", ImVec2(larguraBotao, alturaBotao))) {
        mostrarConfiguracoes = true;
    }

    // Bot�o Cr�ditos
    ImGui::SetCursorPos(ImVec2((larguraJanela - larguraBotao) * 0.5f,
        posicaoInicialY + 2 * alturaBotao + 2 * espacoEntreBotoes));
    if (ImGui::Button("Cr�ditos", ImVec2(larguraBotao, alturaBotao))) {
        mostrarCreditos = true;
		ImGui::Text("Desenvolvido por: ");
        ImGui::Text("Gabriel Duarte Marques");
        ImGui::Text("Elter Rodrigues");
        ImGui::Text("Kauanne Julia");
        ImGui::Text("Jo�o Vitor Jardim");
    }

    ImGui::End();

    // Janela de Configura��es
    if (mostrarConfiguracoes) {
        ImGui::Begin("Configura��es", &mostrarConfiguracoes);
        ImGui::SetWindowSize(ImVec2(400, 300));
        ImGui::SetWindowPos(ImVec2((larguraJanela - 400) * 0.5f, (alturaJanela - 300) * 0.5f));

        // Adicione aqui as configura��es do jogo
        ImGui::Text("Configura��es do Jogo");

        ImGui::End();
    }

    // Janela de Cr�ditos
    if (mostrarCreditos) {
        ImGui::Begin("Cr�ditos", &mostrarCreditos);
        ImGui::SetWindowSize(ImVec2(400, 300));
        ImGui::SetWindowPos(ImVec2((larguraJanela - 400) * 0.5f, (alturaJanela - 300) * 0.5f));

        ImGui::Text("Desenvolvido por: [Seu Nome]");
        ImGui::Text("Vers�o 1.0");

        ImGui::End();
    }
}