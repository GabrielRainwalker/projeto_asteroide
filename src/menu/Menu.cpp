#include <../../Imgui/imgui.h>
#include <../../Imgui/imgui_impl_glfw.h>
#include <../../Imgui/imgui_impl_opengl3.h>
#include "Menu.h"
#include <iostream>
#include <math.h>

Menu::Menu(GLFWwindow* window, GameManager* gameManager) : janela(window), gameManager(gameManager) {
    inicializar();
}

Menu::~Menu() {
}

void Menu::inicializar() {
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    io.Fonts->Clear();
    spaceFont = io.Fonts->AddFontFromFileTTF("assets/space.ttf", 24.0f);
    io.Fonts->Build();

    if (spaceFont == nullptr) {
        std::cerr << "Erro ao carregar a fonte space.ttf" << std::endl;
    } else {
        std::cout << "Fonte carregada com sucesso!" << std::endl;
    }

    // Estilo do ImGui
    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.02f, 0.02f, 0.08f, 0.94f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.15f, 0.4f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.30f, 0.70f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.35f, 0.80f, 1.00f);
    style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.70f, 0.65f);

    style.WindowRounding = 12.0f;
    style.FrameRounding = 8.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.ItemSpacing = ImVec2(10.0f, 12.0f);
    style.WindowPadding = ImVec2(20.0f, 20.0f);
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
}

void Menu::desenharMenuPrincipal() {
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f,
                                  ImGui::GetIO().DisplaySize.y * 0.5f),
                           ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::SetNextWindowSize(ImVec2(400, 500));

    ImGui::Begin("Menu Principal", nullptr,
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoTitleBar);

    static float titleGlow = 0.0f;
    titleGlow = 0.5f + 0.5f * sinf(ImGui::GetTime() * 2.0f);
    ImVec4 titleColor = ImVec4(1.0f, 0.85f + titleGlow * 0.15f, 0.0f + titleGlow * 0.5f, 1.0f);

    ImGui::PushFont(spaceFont);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("JOGO ASTEROIDE").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::TextColored(titleColor, "JOGO ASTEROIDE");
    ImGui::PopFont();

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
    textWidth = ImGui::CalcTextSize("COMP. GRAFICA").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 0.7f), "COMP. GRAFICA");

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 40);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 12));
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.5f));

    float buttonWidth = 280.0f;
    float buttonHeight = 55.0f;
    float buttonX = (windowWidth - buttonWidth) * 0.5f;

    auto DrawButton = [&](const char* label) {
        ImGui::SetCursorPosX(buttonX);
        bool hovered = ImGui::IsMouseHoveringRect(
            ImGui::GetCursorScreenPos(),
            ImVec2(ImGui::GetCursorScreenPos().x + buttonWidth,
                   ImGui::GetCursorScreenPos().y + buttonHeight));

        if (hovered) {
            ImGui::PushStyleColor(ImGuiCol_Button,
                ImVec4(0.25f, 0.30f, 0.70f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text,
                ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        }

        bool clicked = ImGui::Button(label, ImVec2(buttonWidth, buttonHeight));

        if (hovered) {
            ImGui::PopStyleColor(2);
        }

        return clicked;
    };

    if (DrawButton("INICIAR JOGO")) {
        jogoIniciado = true;
        gameManager->startGame();
    }

    if (DrawButton("CONFIGURAÇÕES")) mostrarConfiguracoes = true;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);

    if (DrawButton("CRÉDITOS")) mostrarCreditos = true;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);

    if (DrawButton("SAIR")) glfwSetWindowShouldClose(janela, GLFW_TRUE);

    ImGui::SetCursorPos(ImVec2(10, ImGui::GetWindowSize().y - 25));
    ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.7f, 0.6f), "v1.0");

    ImGui::PopStyleVar(2);
    ImGui::End();
}

void Menu::desenharConfiguracoes() {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f,
                                  ImGui::GetIO().DisplaySize.y * 0.5f),
                           ImGuiCond_Always, ImVec2(0.5f, 0.5f));

    ImGui::SetNextWindowSize(ImVec2(600, 600));

    ImGui::Begin("CONFIGURAÇÕES", &mostrarConfiguracoes,
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoCollapse);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize("CONFIGURAÇÕES").x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::TextColored(ImVec4(1.0f, 0.85f, 0.0f, 1.0f), "CONFIGURAÇÕES");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::BeginChild("Controles", ImVec2(0, 400), true);

    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "CONTROLES DA NAVE");
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 0.9f));
    ImGui::BulletText("W - Andar para frente");
    ImGui::BulletText("S - Andar para trás");
    ImGui::BulletText("A - Girar à esquerda");
    ImGui::BulletText("D - Girar à direita");
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "AÇÕES DE COMBATE");
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.9f, 0.9f, 0.9f, 0.9f));
    ImGui::BulletText("Mouse Esquerdo - Atirar");
    ImGui::BulletText("ESC - Pausar");
    ImGui::PopStyleColor();

    ImGui::EndChild();

    float buttonWidth = 200.0f;
    ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
    if (ImGui::Button("VOLTAR", ImVec2(buttonWidth, 45))) {
        mostrarConfiguracoes = false;
    }

    ImGui::End();
}

void Menu::desenharCreditos() {
    ImGui::SetNextWindowPos(ImVec2(350, 250), ImGuiCond_FirstUseEver);
    ImGui::Begin("Créditos", &mostrarCreditos,
        ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Desenvolvido por:");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "Gabriel Duarte Marques");
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "Elter Rodrigues");
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "Kauanne Julia");
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), "João Vitor Jardim");

    ImGui::Spacing();
    ImGui::Separator();
    if (ImGui::Button("Voltar", ImVec2(120, 30))) {
        mostrarCreditos = false;
    }

    ImGui::End();
}

void Menu::update(float deltaTime) {
    if (jogoIniciado) {
        gameManager->update(deltaTime);
    }
}

void Menu::desenhar() {
    if (jogoIniciado) {
        gameManager->render();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        ImGui::Begin("HUD", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBackground);
        ImGui::End();
    } else {
        desenharMenuPrincipal();
    }

    if (mostrarConfiguracoes) {
        desenharConfiguracoes();
    }

    if (mostrarCreditos) {
        desenharCreditos();
    }
}