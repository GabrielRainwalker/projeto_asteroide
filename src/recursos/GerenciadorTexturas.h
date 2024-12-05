#ifndef GERENCIADORTEXTURAS_H
#define GERENCIADORTEXTURAS_H

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <unordered_map>
#include "../shaders/Shader.h"

class GerenciadorTexturas {
public:
    static void inicializar();
    static GLuint carregarTextura(const std::string& caminho);
    static void desenharSprite(GLuint texturaID, const glm::vec2& posicao, const glm::vec2& tamanho, const glm::vec2& spriteOffset, const glm::vec2& spriteSize, float rotacao);
    static void liberarTexturas();

private:
    static Shader* shader;
    static glm::mat4 projecao;
    static GLuint quadVAO;
    static std::unordered_map<std::string, GLuint> texturas;
};

#endif // GERENCIADORTEXTURAS_H