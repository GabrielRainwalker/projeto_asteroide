#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Nave.h"
#include "Asteroide.h"
#include "Estrelas.h"

class GameManager {
private:
    Nave nave;
    Asteroide asteroides;
    Estrelas estrelas;

public:
    void init();
    void update();
    void render();
    void handleInput(unsigned char key);
    void handleMouse(int button, int state, int x, int y);
    void checkCollisions();
    void drawScore();
    void drawGameOver();
};

#endif