#pragma once
#include "../../Imgui/imgui.h"
#include "../../Imgui/imgui_impl_glfw.h"
#include "../../Imgui/imgui_impl_opengl3.h"

class Menu {
private:
    bool mostrarConfiguracoes = false;
    bool mostrarCreditos = false;

public:
    Menu();
    void renderizar();
};