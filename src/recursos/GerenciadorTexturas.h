#ifndef GERENCIADORTEXTURAS_H
#define GERENCIADORTEXTURAS_H

#include <string>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <../shaders/Shader.h>

class GerenciadorTexturas {
public:
    static void inicializar();
    static GLuint carregarTextura(const std::string& caminho);
    static void liberarTexturas();
    static void desenharSprite(GLuint texturaID,
                              const glm::vec2& posicao,
                              const glm::vec2& tamanho,
                              const glm::vec2& spriteOffset = glm::vec2(0.0f),
                              const glm::vec2& spriteSize = glm::vec2(1.0f),
                              float rotacao = 0.0f);

private:
    static std::map<std::string, GLuint> texturas;
    static GLuint quadVAO;
    static Shader* shader;
    static glm::mat4 projecao;
};

#endif //GERENCIADORTEXTURAS_H