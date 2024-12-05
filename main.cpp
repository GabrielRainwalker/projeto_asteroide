#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "src/controles/Controles.h"
#include "src/entidades/nave/Nave.h"

int main() {
    // Inicializa GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Configuração da janela GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Cria janela
    GLFWwindow* janela = glfwCreateWindow(800, 600, "Teste Asteroides", NULL, NULL);
    if (!janela) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(janela);

    // Inicializa GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    // Define viewport
    glViewport(0, 0, 800, 600);

    // Loop principal
    while (!glfwWindowShouldClose(janela)) {
        // Limpa o buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Troca os buffers
        glfwSwapBuffers(janela);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}