//
// Created by T-Gamer on 05/12/2024.
//

#ifndef CONTROLES_H
#define CONTROLES_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "entidades/nave/Nave.h"

class Controles {
public:
    Controles(GLFWwindow* window, Nave* nave);
    void processarEntradas(float deltaTime);
    void processarMouse();

private:
    GLFWwindow* window;
    Nave* nave;
    bool atirando;
    glm::vec2 ultimaPosicaoMouse;
    float velocidadeMovimento;
};

#endif //CONTROLES_H
