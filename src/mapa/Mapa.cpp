//
// Created by T-Gamer on 05/12/2024.
//

#include "Mapa.h"
#include <vec2.hpp>


void Mapa::desenhar() {
    // Renderização isométrica
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            float isoX = (x - y) * TILE_WIDTH / 2;
            float isoY = (x + y) * TILE_HEIGHT / 2;

            gerenciadorTexturas->desenharTile(
                "tileset",
                glm::vec2(isoX, isoY),
                glm::vec2(TILE_WIDTH, TILE_HEIGHT)
            );
        }
    }
}