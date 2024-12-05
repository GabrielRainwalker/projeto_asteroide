#include "Nave.h"

Nave::Nave() {
    // Carregar a textura do sprite sheet
    texturaID = GerenciadorTexturas::carregarTextura("recursos/nave.png");

    // Defina o tamanho de cada sprite no sheet (ajuste conforme necessário)
    tamanhoSprite = glm::vec2(64, 64); // Exemplo: 64x64 pixels por sprite
    coordenadasSprite = glm::vec2(0, 0); // Comece no primeiro sprite

    // Inicialize variáveis de animação
    tempoAcumulado = 0.0f;
    frameAtual = 0;
    totalFrames = 8; // Ajuste conforme o número de frames no sprite sheet

    // Inicialize o quad
    inicializarQuad();
}

void Nave::inicializarQuad() {
    float vertices[] = {
        // Posições        // Coordenadas de textura
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    GLuint EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Nave::desenhar() {
    glBindTexture(GL_TEXTURE_2D, texturaID);

    // Calcular coordenadas de textura para o sprite atual
    float texX = coordenadasSprite.x / 512.0f; // Largura total do sprite sheet (ajuste conforme necessário)
    float texY = coordenadasSprite.y / 512.0f; // Altura total do sprite sheet (ajuste conforme necessário)
    float texWidth = tamanhoSprite.x / 512.0f;
    float texHeight = tamanhoSprite.y / 512.0f;

    // Atualizar as coordenadas de textura no shader (assumindo que você tenha um shader configurado)
    // glUniform2f(glGetUniformLocation(shaderProgram, "texOffset"), texX, texY);
    // glUniform2f(glGetUniformLocation(shaderProgram, "texSize"), texWidth, texHeight);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}