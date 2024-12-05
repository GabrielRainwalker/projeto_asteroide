#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "entidades/nave/Nave.h"
#include "controles/Controles.h"
#include "recursos/GerenciadorAsteroides.cpp"
#include "audio/Audio.h"
#include "entidades/estrelas/Estrelas.h"
#include "menu/Menu.h"
#include "jogo/Jogo.h"


const unsigned int LARGURA_JANELA = 800;
const unsigned int ALTURA_JANELA = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Inicialização do GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Configurar GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Criar janela
    GLFWwindow* window = glfwCreateWindow(LARGURA_JANELA, ALTURA_JANELA, "Asteroides", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // Configurar OpenGL
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Inicializar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Inicializar sistema de renderização
    GerenciadorTexturas::inicializar();

    // Iniciar Controles
    GerenciadorTexturas gerenciadorTexturas;
    Nave nave(&gerenciadorTexturas);
    Controles controles(window, &nave);
    float lastFrame = 0.0f;

    // Carregar textura da nave
    GLuint texturaNave = GerenciadorTexturas::carregarTextura("assets/nave.png");
    GerenciadorAsteroides gerenciadorAsteroides;
    GerenciadorAudio audio;
    GerenciadorJogo gerenciadorJogo;
    EfeitoEstrelas estrelas(150);

    // Iniciar música de fundo
    audio.tocarMusicaFundo();

    // No loop principal
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Novo frame ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Controles
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Atualizar
        estrelas.atualizar(deltaTime);
        nave.atualizar(deltaTime);
        gerenciadorAsteroides.atualizar(deltaTime);
        gerenciadorJogo.atualizar(deltaTime);

        // Verificar colisões
        gerenciadorJogo.verificarColisoes();

        // Renderizar
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderizar na ordem correta
        estrelas.desenhar();
        gerenciadorAsteroides.desenhar();
        nave.desenhar();
        nave.desenharMisseis();
        gerenciadorJogo.desenhar();
        gerenciadorJogo.desenharPontuacao();

        if (gerenciadorJogo.isJogoFinalizado()) {
            gerenciadorJogo.mostrarTelaFinal();
        }

        // Renderizar ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Trocar buffers
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
}