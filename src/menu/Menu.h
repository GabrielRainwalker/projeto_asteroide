//
// Created by T-Gamer on 04/12/2024.
//

#ifndef MENU_H
#define MENU_H

class Menu {
public:
    Menu();
    void renderizar();
    bool estaAtivo() const { return !jogoIniciado; }

private:
    bool jogoIniciado = false;
    bool mostrarConfiguracoes = false;
    bool mostrarCreditos = false;
    float volume = 1.0f;
};

#endif //MENU_H
