//
// Created by T-Gamer on 05/12/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void usar();
    void setMat4(const std::string &name, const glm::mat4 &mat);
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setInt(const std::string &name, int value);

private:
    GLuint ID;
    void checarErrosCompilacao(GLuint shader, std::string type);
};

const char* ESTRELA_VERTEX_SHADER = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;

    uniform mat4 projection;
    uniform vec2 posicao;
    uniform float tamanho;

    void main() {
        vec4 pos = projection * vec4(aPos * tamanho + posicao, 0.0, 1.0);
        gl_Position = pos;
    }
)";

const char* ESTRELA_FRAGMENT_SHADER = R"(
    #version 330 core
    out vec4 FragColor;

    uniform float brilho;
    uniform vec3 corEstrela;

    void main() {
        FragColor = vec4(corEstrela * brilho, 1.0);
    }
)";

#endif //SHADER_H
