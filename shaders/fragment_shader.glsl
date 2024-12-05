#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D imagem;
uniform vec2 spriteOffset;
uniform vec2 spriteSize;

void main() {
    vec2 coordsFinais = spriteOffset + (TexCoords * spriteSize);
    FragColor = texture(imagem, coordsFinais);
}