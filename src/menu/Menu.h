#ifndef MENU_H
#define MENU_H

#include <imgui.h>
#include "jogo/GameManager.h"
#include <memory>
#include <string>


class Menu {
public:
    Menu(GLFWwindow* janela, GameManager* gameManager);
    ~Menu();

    void update(float deltaTime);

    void desenhar();
    void inicializar();
    bool estaAtivo() const { return !jogoIniciado; }
    float getVolume() const { return volume; }

private:
    GLFWwindow* janela;
    GameManager* gameManager;
    bool jogoIniciado = false;
    bool mostrarConfiguracoes = false;
    bool mostrarCreditos = false;
    float volume = 1.0f;
    ImFont* spaceFont;

    void desenharMenuPrincipal();
    void desenharConfiguracoes();
    void desenharCreditos();
};

#endif