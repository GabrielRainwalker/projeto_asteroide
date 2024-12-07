#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
    glfwSetMouseButtonCallback(janela, mouseButtonCallback);
    Menu menu(janela, gameManager);
    float lastTime = glfwGetTime();


    while (!glfwWindowShouldClose(janela)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();

        // Atualização do jogo e do menu
        gameManager->update(deltaTime);
        menu.update(deltaTime);

        // Início do frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Construção da interface do ImGui
        menu.desenhar();

        // Limpar o buffer de cor ANTES da renderização
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderização do jogo
        gameManager->render();
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Renderização do ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(janela);
    }

    delete gameManager;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();while (!glfwWindowShouldClose(janela)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();

        // Atualização do jogo e do menu
        gameManager->update(deltaTime);
        menu.update(deltaTime);

        // Início do frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Construção da interface do ImGui
        menu.desenhar();

        // Limpar o buffer de cor ANTES da renderização
        glClear(GL_COLOR_BUFFER_BIT);

        // Renderização do jogo
        gameManager->render();

        // Renderização do ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(janela);
    }

    glfwDestroyWindow(janela);
    glfwTerminate();

    return 0;
}