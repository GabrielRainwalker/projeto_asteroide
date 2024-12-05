#include "Mapa.h"
#include <GLFW/glfw3.h>

const float Mapa::TILE_WIDTH = 64.0f;
const float Mapa::TILE_HEIGHT = 32.0f;

Mapa::Mapa(int largura, int altura, int numEstrelas)
    : largura(largura), altura(altura), efeitoEstrelas(numEstrelas) {
}

void Mapa::desenhar() {
    // Fundo preto
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenhar estrelas
    efeitoEstrelas.desenhar();
}