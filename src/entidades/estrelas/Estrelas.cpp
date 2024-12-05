//
// Created by T-Gamer on 05/12/2024.
//

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Estrelas.h"
#include <random>

EfeitoEstrelas::EfeitoEstrelas(int quantidade) {
    shader = new Shader(ESTRELA_VERTEX_SHADER, ESTRELA_FRAGMENT_SHADER);
    inicializarGL();

    // Criar estrelas iniciais
    for (int i = 0; i < quantidade; i++) {
        criarEstrela();
    }
}

void EfeitoEstrelas::inicializarGL() {
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void EfeitoEstrelas::criarEstrela() {
    Estrela estrela;
    estrela.posicao.x = static_cast<float>(rand()) / RAND_MAX * 800.0f;
    estrela.posicao.y = static_cast<float>(rand()) / RAND_MAX * 600.0f;
    estrela.brilho = static_cast<float>(rand()) / RAND_MAX * 0.5f + 0.5f;
    estrela.velocidade = static_cast<float>(rand()) / RAND_MAX * 50.0f + 25.0f;
    estrela.tamanho = static_cast<float>(rand()) / RAND_MAX * 2.0f + 1.0f;
    estrela.cor = gerarCorAleatoria();

    estrelas.push_back(estrela);
}

glm::vec3 EfeitoEstrelas::gerarCorAleatoria() {
    // Cores mais claras para as estrelas
    float r = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f;
    float g = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f;
    float b = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f;
    return glm::vec3(r, g, b);
}

void EfeitoEstrelas::atualizar(float deltaTime) {
    for (auto& estrela : estrelas) {
        estrela.posicao.y += estrela.velocidade * deltaTime;

        // Efeito de piscar
        estrela.brilho = 0.5f + sin(glfwGetTime() * 2.0f) * 0.2f;

        // Reposicionar estrela quando sair da tela
        if (estrela.posicao.y > 600.0f) {
            estrela.posicao.y = 0.0f;
            estrela.posicao.x = static_cast<float>(rand()) / RAND_MAX * 800.0f;
        }
    }
}

void EfeitoEstrelas::desenhar() {
    shader->usar();
    glBindVertexArray(VAO);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    shader->setMat4("projection", projection);

    for (const auto& estrela : estrelas) {
        shader->setVec2("posicao", estrela.posicao);
        shader->setFloat("tamanho", estrela.tamanho);
        shader->setFloat("brilho", estrela.brilho);
        shader->setVec3("corEstrela", estrela.cor);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }

    glBindVertexArray(0);
}