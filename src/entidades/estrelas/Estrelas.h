//
// Created by T-Gamer on 05/12/2024.
//

#ifndef ESTRELAS_H
#define ESTRELAS_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../shaders/Shader.h"

struct Estrela {
    glm::vec2 posicao;
    float brilho;
    float velocidade;
    float tamanho;
    glm::vec3 cor;
};

class EfeitoEstrelas {
public:
    EfeitoEstrelas(int quantidade);
    ~EfeitoEstrelas();

    void atualizar(float deltaTime);
    void desenhar();

private:
    std::vector<Estrela> estrelas;
    Shader* shader;
    GLuint VAO, VBO;

    void inicializarGL();
    void criarEstrela();
    glm::vec3 gerarCorAleatoria();
};


#endif //ESTRELAS_H
