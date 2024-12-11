#ifndef NAVE_H
#define NAVE_H

#include <vector>
#include "Colisoes.h"

class Nave {
public:
    Nave();
    void draw();
    void update();
    void keyboard(unsigned char key);
    void shoot();

    int getNumBullets() const;
    bool isBulletActive(int index) const;
    void deactivateBullet(int index);

    BoundingBox getBoundingBox() const;
    BoundingBox getBulletBoundingBox(int index) const;

private:
    float posX;
    float posY;
    std::vector<float> bulletX;
    std::vector<float> bulletY;
    std::vector<bool> bulletActive;
};

#endif
