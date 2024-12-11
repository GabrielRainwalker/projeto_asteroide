#include "Nave.h"
#include <GL/glut.h>
#include <cstddef>

Nave::Nave() : posX(0.0f), posY(-70.0f) {}

void Nave::draw() {
    glPushMatrix();
    glTranslatef(posX, posY, 0);

    // Desenhar a nave
    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.5f, 0.5f);
    glVertex2f(0.0f, 15.0f);
    glVertex2f(-10.0f, -10.0f);
    glVertex2f(10.0f, -10.0f);
    glEnd();

    // Desenhar os tiros
    glColor3f(1.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < bulletX.size(); i++) {
        if (bulletActive[i]) {
            glPushMatrix();
            glTranslatef(bulletX[i], bulletY[i], 0.0f);
            glutSolidSphere(1.0f, 20, 20);
            glPopMatrix();
        }
    }

    glPopMatrix();
}

void Nave::update() {
    // Atualiza os tiros
    for (size_t i = 0; i < bulletY.size(); i++) {
        if (bulletActive[i]) {
            bulletY[i] += 2.0f;
            if (bulletY[i] > 100.0f) {
                bulletActive[i] = false;
            }
        }
    }
}

void Nave::keyboard(unsigned char key) {
    switch (key) {
    case 'a':
    case 'A':
        posX -= 5.0f;
        break;
    case 'd':
    case 'D':
        posX += 5.0f;
        break;
    }
}

void Nave::shoot() {
    // Adiciona um novo tiro
    bulletX.push_back(0.0f);
    bulletY.push_back(15.0f);
    bulletActive.push_back(true);
}

BoundingBox Nave::getBoundingBox() const {
    return { posX, posY, 20.0f, 25.0f };
}

BoundingBox Nave::getBulletBoundingBox(int index) const {
    return { posX + bulletX[index], posY + bulletY[index], 2.0f, 2.0f };
}

bool Nave::isBulletActive(int index) const {
    return bulletActive[index];
}

void Nave::deactivateBullet(int index) {
    bulletActive[index] = false;
}

int Nave::getNumBullets() const {
    return bulletActive.size();
}
