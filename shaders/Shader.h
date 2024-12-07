//
// Created by T-Gamer on 06/12/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader {
public:
    // Construtor que lê e cria o shader a partir dos caminhos dos arquivos
    Shader(const char* vertexPath, const char* fragmentPath);

    // Ativa o shader
    void use();

    // Funções utilitárias para definir uniformes
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);

    void setMat2(const std::string& name, const glm::mat2& mat);
    void setMat3(const std::string& name, const glm::mat3& mat);
    void setMat4(const std::string& name, const glm::mat4& mat);

    // ID do programa do shader
    unsigned int ID;

    ~Shader();

private:
    // Função para verificar erros de compilação/linkagem
    void checkCompileErrors(unsigned int shader, const std::string& type);

    // Cache para locais dos uniformes
    std::unordered_map<std::string, int> uniformLocationCache;

    int getUniformLocation(const std::string& name);
};

#endif