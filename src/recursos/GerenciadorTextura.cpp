#include "GerenciadorTextura.h"
#include <iostream>
#include "../../Library/include/stb/stb_image.h"

GerenciadorTextura* GerenciadorTextura::instance = nullptr;

GerenciadorTextura* GerenciadorTextura::getInstance() {
    if (instance == nullptr) {
        instance = new GerenciadorTextura();
    }
    return instance;
}

GerenciadorTextura::~GerenciadorTextura() {
    limparTexturas();
}

GLuint GerenciadorTextura::carregarTextura(const std::string& nome, const std::string& caminhoArquivo) {
    // Verifica se a textura já existe
    if (existeTextura(nome)) {
        return texturas[nome];
    }

    // Carrega a imagem
    int largura, altura, canais;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* dados = stbi_load(caminhoArquivo.c_str(), &largura, &altura, &canais, 0);

    if (!dados) {
        std::cout << "Falha ao carregar textura: " << caminhoArquivo << std::endl;
        return 0;
    }

    // Determina o formato baseado nos canais
    GLenum formato;
    if (canais == 4)
        formato = GL_RGBA;
    else if (canais == 3)
        formato = GL_RGB;
    else {
        std::cout << "Formato de textura não suportado" << std::endl;
        stbi_image_free(dados);
        return 0;
    }

    // Cria a textura OpenGL
    GLuint texturaID;
    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    // Configura parâmetros da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carrega os dados da textura
    glTexImage2D(GL_TEXTURE_2D, 0, formato, largura, altura, 0, formato, GL_UNSIGNED_BYTE, dados);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Libera a memória
    stbi_image_free(dados);

    // Armazena a textura no map
    texturas[nome] = texturaID;

    return texturaID;
}

GLuint GerenciadorTextura::getTextura(const std::string& nome) {
    if (existeTextura(nome)) {
        return texturas[nome];
    }
    return 0;
}

void GerenciadorTextura::removerTextura(const std::string& nome) {
    if (existeTextura(nome)) {
        glDeleteTextures(1, &texturas[nome]);
        texturas.erase(nome);
    }
}

void TextureManager::limparTexturas() {
    for (auto& textura : texturas) {
        glDeleteTextures(1, &textura.second);
    }
    texturas.clear();
}

bool TextureManager::existeTextura(const std::string& nome) const {
    return texturas.find(nome) != texturas.end();
}