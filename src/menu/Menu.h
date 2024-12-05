#ifndef MENU_H
#define MENU_H

class Menu {
public:
    Menu();
    void desenhar();
    void desenha();
    void renderizar();
    bool estaAtivo() const { return !jogoIniciado; }

private:
    bool jogoIniciado = false;
    bool mostrarConfiguracoes = false;
    bool mostrarCreditos = false;
    float volume = 1.0f;
};

#endif //MENU_H