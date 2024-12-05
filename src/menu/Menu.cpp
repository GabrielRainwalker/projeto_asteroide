#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Menu.h"

void Menu::desenhar() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (!jogoIniciado) {
        ImGui::SetNextWindowPos(ImVec2(400, 300), ImGuiCond_FirstUseEver);
        ImGui::Begin("Menu Principal", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        if (ImGui::Button("Iniciar Jogo", ImVec2(200, 50))) {
            jogoIniciado = true;
        }

        if (ImGui::Button("Configurações", ImVec2(200, 50))) {
            mostrarConfiguracoes = true;
        }

        if (ImGui::Button("Créditos", ImVec2(200, 50))) {
            mostrarCreditos = true;
        }

        ImGui::End();
    }

    if (mostrarConfiguracoes) {
        ImGui::Begin("Configurações", &mostrarConfiguracoes);
        ImGui::Text("Controles:");
        ImGui::BulletText("W/S/A/D - Movimento da nave");
        ImGui::BulletText("Mouse Esquerdo - Atirar");
        ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);
        ImGui::End();
    }

    if (mostrarCreditos) {
        ImGui::Begin("Créditos", &mostrarCreditos);
        ImGui::Text("Desenvolvido por: ");
        ImGui::Text("Gabriel Duarte Marques");
        ImGui::Text("Elter Rodrigues");
        ImGui::Text("Kauanne Julia");
        ImGui::Text("João Vitor Jardim");
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}