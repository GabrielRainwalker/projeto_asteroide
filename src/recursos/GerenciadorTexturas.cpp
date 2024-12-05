//
// Created by T-Gamer on 04/12/2024.
//

#include "GerenciadorTexturas.h"
#include "stb_image.h"
#include <stdexcept>

std::map<std::string, GLuint> GerenciadorTexturas::texturas;

GLuint GerenciadorTexturas::carregarTextura(const std::string& caminho) {
    if (texturas.find(caminho) != texturas.end()) {
        return texturas[caminho];
    }

    int largura, altura, canais;
    unsigned char* dados = stbi_load(caminho.c_str(), &largura, &altura, &canais, 0);
    if (!dados) {
        throw std::runtime_error("Falha ao carregar textura: " + caminho);
    }

    GLuint texturaID;
    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, dados);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(dados);

    texturas[caminho] = texturaID;
    return texturaID;
}

void GerenciadorTexturas::liberarTexturas() {
    for (auto& par : texturas) {
        glDeleteTextures(1, &par.second);
    }
    texturas.clear();
}