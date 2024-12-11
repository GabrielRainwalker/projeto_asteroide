#ifndef ASTEROIDE_H
#define ASTEROIDE_H

#include "Colisoes.h"
#include <glm/glm.hpp>

#define NUM_ASTEROID 20   

class Asteroide {
public:
    void init();
    void update();
    void draw();

    BoundingBox getBoundingBox(int index) const;
    bool isActive(int index) const;
    void deactivate(int index);

private:
    glm::vec2 positions[NUM_ASTEROID];
    bool active[NUM_ASTEROID];
};

#endif
