#ifndef ESTRELAS_H
#define ESTRELAS_H

#include <glm/glm.hpp>

#define NUM_STARS 100  

class Estrelas {
public:
    void init();
    void update();
    void draw();

private:
    glm::vec2 positions[NUM_STARS];
    float rotationAngle;
};

#endif
