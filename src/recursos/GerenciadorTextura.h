#pragma once
#include <../../Library/include/glad/glad.h>
#include <string>
#include <map>
#include <memory>

class GerenciadorTextura {
private:
    static GerenciadorTextura* instance;
    std::map<std::string, GLuint> texturas;

    // Construtor privado (Singleton)
    GerenciadorTextura() = default;

public:
    static GerenciadorTextura* getInstance();
    ~GerenciadorTextura();

    // Previne cópia do singleton
    GerenciadorTextura(const GerenciadorTextura&) = delete;
    GerenciadorTextura& operator=(const GerenciadorTextura&) = delete;

    // Métodos principais
    GLuint carregarTextura(const std::string& nome, const std::string& caminhoArquivo);
    GLuint getTextura(const std::string& nome);
    void removerTextura(const std::string& nome);
    void limparTexturas();
    bool existeTextura(const std::string& nome) const;
};