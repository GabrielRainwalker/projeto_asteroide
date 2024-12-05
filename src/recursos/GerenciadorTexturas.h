//
// Created by T-Gamer on 04/12/2024.
//
#ifndef GERENCIADORTEXTURAS_H
#define GERENCIADORTEXTURAS_H

#include <string>
#include <map>
#include <glad/glad.h>

class GerenciadorTexturas {
public:
    static GLuint carregarTextura(const std::string& caminho);
    static void liberarTexturas();

private:
    static std::map<std::string, GLuint> texturas;
};

#endif //GERENCIADORTEXTURAS_H
