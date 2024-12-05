#ifndef GERENCIADORTEXTURAS_H
#define GERENCIADORTEXTURAS_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <../shaders/Shader.h>

class GerenciadorTexturas {
public:
    static void inicializar();
    static GLuint carregarTextura(const std::string& caminho);
    static void liberarTexturas();
    static void desenharSprite(const std::string& nomeTextura,  // Altere aqui
                              const glm::vec2& posicao,
                              const glm::vec2& tamanho,
                              const glm::vec2& offset,
                              const glm::vec2& tamanhoSprite,
                              float rotacao);

private:
    static std::map<std::string, GLuint> texturas;
    static GLuint quadVAO;
    static Shader* shader;
    static glm::mat4 projecao;
};

#endif //GERENCIADORTEXTURAS_H