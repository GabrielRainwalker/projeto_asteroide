#ifndef NAVE_H
#define NAVE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <recursos/GerenciadorTexturas.h>

class Nave {
public:
    Nave();
    void desenhar();
    void atualizarAnimacao(float deltaTime);

private:
    GLuint texturaID;
    GLuint VBO, VAO;
    glm::vec2 posicao;
    glm::vec2 tamanhoSprite;
    glm::vec2 coordenadasSprite;
    float tempoAcumulado; // Novo atributo
    int frameAtual; // Novo atributo
    int totalFrames; // Novo atributo
    void inicializarQuad();
};

#endif //NAVE_H