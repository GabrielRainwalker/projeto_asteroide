#pragma once
#include <../../Library/include/GLFW/glfw3.h>
#include <map>

class Controles {
private:
    static Controles* instance;
    GLFWwindow* janela;
    std::map<int, bool> teclasPressionadas;

    Controles() = default;

public:
    static Controles* getInstance();
    void inicializar(GLFWwindow* window);

    // M�todos de verifica��o
    bool getTecla(int tecla);
    bool getTeclaPressionada(int tecla);
    bool getTeclaSolta(int tecla);

    // M�todos do mouse
    void getPosicaoMouse(double& x, double& y);
    bool getBotaoMouse(int botao);

    void atualizar();
};
