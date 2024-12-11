#include "Estrelas.h"
#include <GL/glut.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>

void Estrelas::init() {
    srand(time(NULL));
    for (int i = 0; i < NUM_STARS; i++) {
        positions[i].x = (rand() % 200 - 100);
        positions[i].y = (rand() % 200 - 100);
    }
    rotationAngle = 0.0f;
}

void Estrelas::update() {
    rotationAngle += 0.001f;
}

void Estrelas::draw() {
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    for (int i = 0; i < NUM_STARS; i++) {
        float xRot = positions[i].x * cos(rotationAngle) - positions[i].y * sin(rotationAngle);
        float yRot = positions[i].x * sin(rotationAngle) + positions[i].y * cos(rotationAngle);
        glVertex2f(xRot, yRot);
    }
    glEnd();
}
