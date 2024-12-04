#include "Controles.h"

Controles* Controles::instance = nullptr;

Controles* Controles::getInstance() {
    if (!instance) {
        instance = new Controles();
    }
    return instance;
}

void Controles::inicializar(GLFWwindow* window) {
    this->janela = window;
}

bool Controles::getTecla(int tecla) {
    return glfwGetKey(janela, tecla) == GLFW_PRESS;
}

bool Controles::getTeclaPressionada(int tecla) {
    bool estadoAtual = getTecla(tecla);
    bool estadoAnterior = teclasPressionadas[tecla];
    teclasPressionadas[tecla] = estadoAtual;
    return estadoAtual && !estadoAnterior;
}

bool Controles::getTeclaSolta(int tecla) {
    bool estadoAtual = getTecla(tecla);
    bool estadoAnterior = teclasPressionadas[tecla];
    teclasPressionadas[tecla] = estadoAtual;
    return !estadoAtual && estadoAnterior;
}

void Controles::getPosicaoMouse(double& x, double& y) {
    glfwGetCursorPos(janela, &x, &y);
}

bool Controles::getBotaoMouse(int botao) {
    return glfwGetMouseButton(janela, botao) == GLFW_PRESS;
}

void Controles::atualizar() {
    glfwPollEvents();
}