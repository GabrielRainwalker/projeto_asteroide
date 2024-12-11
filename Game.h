#ifndef GAME_H
#define GAME_H

#include <GL/glut.h>
#include <string>
#include "Nave.h"
#include "Asteroide.h"
#include "Estrelas.h"
#include "Colisoes.h"

#define NUM_ASTEROID 20


class Game {
public:
    Game();
    void init(int argc, char** argv);
    void run();

    static void displayCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void timerCallback(int value);
    static void mouseCallback(int button, int state, int x, int y);

private:
    static Game* instance;
    Nave nave;
    Asteroide asteroides;
    Estrelas estrelas;

    int score;
    bool gameOver;

    void display();
    void keyboard(unsigned char key, int x, int y);
    void timer(int value);
    void mouse(int button, int state, int x, int y);

    void drawScore();
    void drawGameOver();
    void checkCollisions();
};

#endif
