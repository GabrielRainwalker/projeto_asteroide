#include "Asteroide.h"
#include <GL/glut.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>

void Asteroide::init() {
    srand(time(NULL));
    for (int i = 0; i < NUM_ASTEROID; i++) {
        positions[i].x = (rand() % 200 - 100);
        positions[i].y = (rand() % 200 + 50);
        active[i] = true;
    }
}

void Asteroide::update() {
    for (int i = 0; i < NUM_ASTEROID; i++) {
        if (active[i]) {
            positions[i].y -= 0.15f;
            if (positions[i].y < -100.0f) {
                positions[i].x = (rand() % 200 - 100);
                positions[i].y = (rand() % 200 + 100);
            }
        }
    }
}

void Asteroide::draw() {
    for (int i = 0; i < NUM_ASTEROID; i++) {
        if (active[i]) {
            glPushMatrix();
            glTranslatef(positions[i].x, positions[i].y, 0.0f);
            glColor3f(0.8f, 0.8f, 0.8f);
            glutSolidSphere(5.0f, 20, 20);
            glPopMatrix();
        }
    }
}

BoundingBox Asteroide::getBoundingBox(int index) const {
    return { positions[index].x, positions[index].y, 10.0f, 10.0f };
}

bool Asteroide::isActive(int index) const {
    return active[index];
}

void Asteroide::deactivate(int index) {
    active[index] = false;
}
