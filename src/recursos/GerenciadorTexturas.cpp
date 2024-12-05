//
// Created by T-Gamer on 04/12/2024.
//

#include "GerenciadorTexturas.h"
#include "stb_image.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <stdexcept>

void GerenciadorTexturas::inicializar() {
    // Inicializar shader
    shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");

    // Configurar projeção ortográfica
    projecao = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    // Configurar VAO/VBO para o quad
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GerenciadorTexturas::desenharSprite(GLuint texturaID,
                                        const glm::vec2& posicao,
                                        const glm::vec2& tamanho,
                                        const glm::vec2& spriteOffset,
                                        const glm::vec2& spriteSize,
                                        float rotacao) {
    shader->usar();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(posicao, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * tamanho.x, 0.5f * tamanho.y, 0.0f));
    model = glm::rotate(model, rotacao, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * tamanho.x, -0.5f * tamanho.y, 0.0f));

    model = glm::scale(model, glm::vec3(tamanho, 1.0f));

    shader->setMat4("projection", projecao);
    shader->setMat4("model", model);
    shader->setVec2("spriteOffset", spriteOffset);
    shader->setVec2("spriteSize", spriteSize);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}