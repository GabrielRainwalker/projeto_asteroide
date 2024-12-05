//
// Created by T-Gamer on 05/12/2024.
//

#ifndef COLISAO_H
#define COLISAO_H

#include <glm/glm.hpp>
#include "entidades/Missil/Missil.h"
#include "entidades/asteroides/Asteroide.h"

class GerenciadorColisoes {
public:
    static bool verificarColisao(const Missil& missil, const Asteroide& asteroide);
    static bool verificarColisaoCircular(const glm::vec2& pos1, float raio1,
                                       const glm::vec2& pos2, float raio2);
};


#endif //COLISAO_H
