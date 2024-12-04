#include "mapa.h"
#include <random>
#include <../../Library/include/glad/glad.h>
#include <../../Library/include/glm/gtc/matrix_transform.hpp>
#include <../../Library/include/glm/glm.hpp>
#include <../../Library/include/GLFW/glfw3.h>
#include <vector>

const int QUANTIDADE_ESTRELAS = 100;
const float TAMANHO_PONTO_ESTRELA = 2.0f;
const glm::vec3 COR_GRID = glm::vec3(0.0f, 0.5f, 0.0f);
const glm::vec4 COR_FUNDO = glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);

Mapa::Mapa(int largura, int altura, float tamTile)
    : larguraGrid(largura), alturaGrid(altura), tamanhoTile(tamTile) {
    corGrid = COR_GRID;
    inicializarEstrelas(QUANTIDADE_ESTRELAS);
    inicializarBuffers();
}

void Mapa::inicializarBuffers() {
    std::vector<float> vertices;
    int numLinhasHorizontais = alturaGrid + 1;
    int numLinhasVerticais = larguraGrid + 1;
    vertices.reserve((numLinhasHorizontais + numLinhasVerticais) * 6); // 6 valores por linha

    // Linhas horizontais
    for (int i = 0; i <= alturaGrid; i++) {
        float pos = i * tamanhoTile;
        vertices.insert(vertices.end(), {
            0.0f, 0.0f, pos,
            larguraGrid * tamanhoTile, 0.0f, pos
            });
    }

    // Linhas verticais
    for (int i = 0; i <= larguraGrid; i++) {
        float pos = i * tamanhoTile;
        vertices.insert(vertices.end(), {
            pos, 0.0f, 0.0f,
            pos, 0.0f, alturaGrid * tamanhoTile
            });
    }

    // Gerar e configurar os buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    if (VAO == 0 || VBO == 0) {
        // Tratamento de erro
        return;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Mapa::inicializarEstrelas(int quantidade) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(-20.0f, 20.0f);
    std::uniform_real_distribution<float> disY(5.0f, 15.0f);
    std::uniform_real_distribution<float> disZ(-20.0f, 20.0f);
    std::uniform_real_distribution<float> disBrilho(0.5f, 1.0f);

    estrelas.clear();
    estrelas.reserve(quantidade); // Reservar espaço para as estrelas

    for (int i = 0; i < quantidade; i++) {
        Estrela estrela;
        estrela.posicao = glm::vec3(disX(gen), disY(gen), disZ(gen));
        estrela.brilho = disBrilho(gen);
        estrelas.push_back(estrela);
    }

    std::vector<float> estrelasData;
    estrelasData.reserve(quantidade * 3); // Reservar espaço para os dados das estrelas

    for (const auto& estrela : estrelas) {
        estrelasData.insert(estrelasData.end(), { estrela.posicao.x, estrela.posicao.y, estrela.posicao.z });
    }

    glGenVertexArrays(1, &estrelaVAO);
    glGenBuffers(1, &estrelaVBO);

    if (estrelaVAO == 0 || estrelaVBO == 0) {
        // Tratar erro de geração de buffers
        return;
    }

    glBindVertexArray(estrelaVAO);
    glBindBuffer(GL_ARRAY_BUFFER, estrelaVBO);
    glBufferData(GL_ARRAY_BUFFER, estrelasData.size() * sizeof(float), estrelasData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Mapa::renderizar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(COR_FUNDO.r, COR_FUNDO.g, COR_FUNDO.b, COR_FUNDO.a);

    // Desenhar estrelas
    glBindVertexArray(estrelaVAO);
    glPointSize(TAMANHO_PONTO_ESTRELA);
    glDrawArrays(GL_POINTS, 0, estrelas.size());

    // Desenhar grid
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, (larguraGrid + 1) * 4);
}

void Mapa::atualizar(float deltaTime) {
    for (auto& estrela : estrelas) {
        estrela.brilho = 0.5f + (sin(glfwGetTime() * 2.0f + estrela.posicao.x) + 1.0f) * 0.25f;
    }
}

Mapa::~Mapa() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &estrelaVAO);
    glDeleteBuffers(1, &estrelaVBO);
}
