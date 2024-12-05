#include "GerenciadorTexturas.h"
#include "stb_image.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <stdexcept>

Shader* GerenciadorTexturas::shader = nullptr;
glm::mat4 GerenciadorTexturas::projecao;
GLuint GerenciadorTexturas::quadVAO = 0;
std::unordered_map<std::string, GLuint> GerenciadorTexturas::texturas;

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

GLuint GerenciadorTexturas::carregarTextura(const std::string& caminho) {
    if (texturas.find(caminho) != texturas.end()) {
        return texturas[caminho];
    }

    GLuint texturaID;
    glGenTextures(1, &texturaID);

    int largura, altura, canais;
    unsigned char* dados = stbi_load(caminho.c_str(), &largura, &altura, &canais, 0);
    if (dados) {
        GLenum formato = (canais == 4) ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, texturaID);
        glTexImage2D(GL_TEXTURE_2D, 0, formato, largura, altura, 0, formato, GL_UNSIGNED_BYTE, dados);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(dados);
        texturas[caminho] = texturaID;
    } else {
        stbi_image_free(dados);
        throw std::runtime_error("Falha ao carregar textura: " + caminho);
    }

    return texturaID;
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

void GerenciadorTexturas::liberarTexturas() {
    for (auto& par : texturas) {
        glDeleteTextures(1, &par.second);
    }
    texturas.clear();
}