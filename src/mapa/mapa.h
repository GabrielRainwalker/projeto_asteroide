#pragma once
#include <../../Library/include/glad/glad.h>
#include <../../Library/include/GLFW/glfw3.h>
#include <../../Library/include/glm/glm.hpp>
#include <vector>


class Mapa {
public:
    GLuint VAO, VBO;
    GLuint estrelaVAO, estrelaVBO;
    struct Estrela {
        glm::vec3 posicao;
        float brilho;
    };

    std::vector<Estrela> estrelas;
    int larguraGrid;
    int alturaGrid;
    float tamanhoTile;
    glm::vec3 corGrid;

    void inicializarEstrelas(int quantidade);
    void desenharEstrelas();
    void desenharGrid();

public:
    Mapa(int largura = 20, int altura = 20, float tamTile = 1.0f);
    ~Mapa() = default;

    void renderizar();
    void atualizar(float deltaTime);

    // Métodos de acesso
    bool dentroDoMapa(float x, float y) const;
    glm::vec2 getPosicaoTile(float x, float y) const;
    float getTamanhoTile() const { return tamanhoTile; }
};