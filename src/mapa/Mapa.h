#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <glm/glm.hpp>
#include "../entidades/estrelas/Estrelas.h"

class Mapa {
public:
    Mapa(int largura, int altura, int numEstrelas);
    void desenhar();

private:
    int largura;
    int altura;
    EfeitoEstrelas efeitoEstrelas;
    static const float TILE_WIDTH;
    static const float TILE_HEIGHT;
};

#endif //MAPA_H