#version 330 core
out vec4 FragColor;

uniform float brightness;

void main() {
    // Calcula a distância do centro
    vec2 center = vec2(0.5);
    float dist = length(gl_PointCoord - center);

    // Cria um brilho suave
    float alpha = 1.0 - smoothstep(0.0, 0.5, dist);

    // Cor da estrela com brilho
    vec3 color = vec3(1.0, 1.0, 0.9) * brightness;
    FragColor = vec4(color, alpha);
}