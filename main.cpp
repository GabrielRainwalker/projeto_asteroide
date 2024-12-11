//
// Created by T-Gamer on 11/12/2024.
//
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fwd.hpp>
#include "src/menu/Menu.h"
#include "jogo/GameManager.h"
#include <iostream>

GameManager* gameManager;
void erro_callback(int erro, const char* descricao) {
    std::cerr << "Erro GLFW (" << erro << "): " << descricao << std::endl;
}
void framebuffer_size_callback(GLFWwindow* janela, int largura, int altura) {
    glViewport(0, 0, largura, altura);
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse) return;
    if (!gameManager) return;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (gameManager->getIsPlaying() && !gameManager->getIsPaused()) {
            gameManager->getPlayerShip()->shoot();
        }
    }
}
float deltaTime = 0.0f;
float lastFrame = 0.0f;
int main() {
    glfwSetErrorCallback(erro_callback);
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int windowWidth = 800;
    int windowHeight = 600;
    int xpos = (mode->width - windowWidth) / 2;
    int ypos = (mode->height - windowHeight) / 2;
    GLFWwindow* janela = glfwCreateWindow(windowWidth, windowHeight, "Jogo Asteroide", nullptr, nullptr);
    if (!janela) {
        std::cerr << "Falha ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowPos(janela, xpos, ypos);
    glfwMakeContextCurrent(janela);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        glfwDestroyWindow(janela);
        glfwTerminate();
        return -1;
    }
    glfwSetMouseButtonCallback(janela, mouseButtonCallback);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(janela, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(janela, framebuffer_size_callback);
    glfwSwapInterval(1);
    gameManager = new GameManager(janela);
    Menu menu(janela, gameManager);
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(janela)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        glfwPollEvents();
         ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glClear(GL_COLOR_BUFFER_BIT);
        menu.update(deltaTime);
        menu.desenhar();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(janela);
    }
    delete gameManager;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(janela);
    glfwTerminate();
    return 0;
}