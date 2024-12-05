//
// Created by T-Gamer on 05/12/2024.
//

#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include "recursos/GerenciadorTexturas.h"

class Mapa {
public:
    Mapa();
    void desenhar();
private:
    std::vector<std::vector<int>> grid;
    GerenciadorTexturas* gerenciadorTexturas;
};

Mapa::Mapa() : gerenciadorTexturas(nullptr) {
    // Inicialização do grid ou outras variáveis
}

#endif //MAPA_H
