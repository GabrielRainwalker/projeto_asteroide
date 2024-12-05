#define GLM_FORCE_PURE

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "entidades/nave/Nave.h"
#include "controles/Controles.h"
#include "recursos/GerenciadorAsteroides.h"
#include "audio/Audio.h"
#include "entidades/estrelas/Estrelas.h"
#include "menu/Menu.h"
#include "jogo/Jogo.h"
#include "jogo/Pontuacao.h"
#include "mapa/Mapa.h"

const unsigned int LARGURA_JANELA = 800;
const unsigned int ALTURA_JANELA = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(LARGURA_JANELA, ALTURA_JANELA, "Asteroides", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    GerenciadorTexturas::inicializar();

    GerenciadorTexturas gerenciadorTexturas;
    Nave nave(&gerenciadorTexturas);
    Controles controles(window, &nave);
    float lastFrame = 0.0f;

    GLuint texturaNave = GerenciadorTexturas::carregarTextura("assets/nave.png");
    GerenciadorAsteroides gerenciadorAsteroides;
    GerenciadorAudio audio;
    GerenciadorJogo gerenciadorJogo;
    Mapa mapa(20, 20, 150); // 20x20 tiles, 150 estrelas

    audio.tocarMusicaFundo();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        nave.atualizar(deltaTime);
        gerenciadorAsteroides.atualizar(deltaTime);
        gerenciadorJogo.atualizar(deltaTime);

        gerenciadorJogo.verificarColisoes();

        glClear(GL_COLOR_BUFFER_BIT);

        mapa.desenhar();
        gerenciadorAsteroides.desenhar();
        nave.desenhar();
        nave.desenharMisseis();
        gerenciadorJogo.desenhar();
        gerenciadorJogo.desenharPontuacao();

        if (gerenciadorJogo.isJogoFinalizado()) {
            gerenciadorJogo.mostrarTelaFinal();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gerenciadorJogo.getPontuacao().salvarRecorde();
    GerenciadorTexturas::liberarTexturas();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}