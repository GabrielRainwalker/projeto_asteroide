#include "Game.h"

Game* Game::instance = nullptr;

Game::Game() : score(0), gameOver(false) {
    instance = this;
}

void Game::init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Jogo Nave Espacial");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    estrelas.init();
    asteroides.init();

    glutDisplayFunc(Game::displayCallback);
    glutKeyboardFunc(Game::keyboardCallback);
    glutMouseFunc(Game::mouseCallback);
    glutTimerFunc(16, Game::timerCallback, 0);
}

void Game::run() {
    glutMainLoop();
}

void Game::displayCallback() {
    if (instance)
        instance->display();
}

void Game::keyboardCallback(unsigned char key, int x, int y) {
    if (instance)
        instance->keyboard(key, x, y);
}

void Game::timerCallback(int value) {
    if (instance)
        instance->timer(value);
}

void Game::mouseCallback(int button, int state, int x, int y) {
    if (instance)
        instance->mouse(button, state, x, y);
}

void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);

    estrelas.draw();
    drawScore();

    if (!gameOver) {
        nave.draw();
        asteroides.draw();
    } else {
        drawGameOver();
    }

    glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y) {
    if (!gameOver) {
        nave.keyboard(key);
    }
    glutPostRedisplay();
}

void Game::timer(int value) {
    if (!gameOver) {
        nave.update();
        asteroides.update();
        estrelas.update();
        checkCollisions();
    }
    glutPostRedisplay();
    glutTimerFunc(16, Game::timerCallback, 0);
}

void Game::mouse(int button, int state, int x, int y) {
    if (!gameOver && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        nave.shoot();
    }
}

void Game::drawScore() {
    glColor3f(1.0, 0, 0);
    glRasterPos2f(-90, 90);
    std::string texto = "Pontos: " + std::to_string(score);
    for (char c : texto) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void Game::drawGameOver() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(-30.0f, 0.0f);
    const char* message = "FIM DE JOGO!!!";
    for (const char* c = message; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void Game::checkCollisions() {
    // Verifica colisão entre a nave e os asteroides
    for (int i = 0; i < NUM_ASTEROID; i++) {
        if (asteroides.isActive(i)) {
            if (checkCollision(nave.getBoundingBox(), asteroides.getBoundingBox(i))) {
                gameOver = true;
            }
        }
    }

    // Verifica colisão entre os tiros e os asteroides
    for (int j = 0; j < nave.getNumBullets(); j++) {
        for (int i = 0; i < NUM_ASTEROID; i++) {
            if (asteroides.isActive(i) && nave.isBulletActive(j)) {
                if (checkCollision(nave.getBulletBoundingBox(j), asteroides.getBoundingBox(i))) {
                    asteroides.deactivate(i);
                    nave.deactivateBullet(j);
                    score += 10;
                }
            }
        }
    }
}
