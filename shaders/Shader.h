#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>

extern const char* ESTRELA_VERTEX_SHADER;
extern const char* ESTRELA_FRAGMENT_SHADER;

class Shader {
public:
    Shader(const char* vertexSource, const char* fragmentSource);
    void usar();
    void setMat4(const std::string& name, const glm::mat4& mat);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setFloat(const std::string& name, float value);
    void setVec3(const std::string& name, const glm::vec3& value);

private:
    unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // SHADER_H