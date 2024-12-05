cmake_minimum_required(VERSION 3.20)
project(projeto_asteroide)

set(CMAKE_CXX_STANDARD 17)

# Diretórios do projeto
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Library")
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/Imgui")

# Arquivos fonte
set(SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${SRC_DIR}/menu/Menu.cpp
        ${SRC_DIR}/entidades/nave/Nave.cpp
        ${SRC_DIR}/recursos/GerenciadorTexturas.cpp
        src/recursos/GerenciadorTexturas.h
        src/entidades/nave/Nave.h
        src/menu/Menu.h
        src/controles/Controles.cpp
        src/controles/Controles.h
        src/entidades/Missil/Missil.cpp
        src/entidades/Missil/Missil.h
        src/audio/Audio.cpp
        src/audio/Audio.h
        src/mapa/Mapa.cpp
        src/mapa/Mapa.h
        src/jogo/Jogo.cpp
        src/jogo/Jogo.h
        shaders/Shader.h
        src/entidades/asteroides/Asteroide.cpp
        src/entidades/asteroides/Asteroide.h
        src/recursos/GerenciadorAsteroides.cpp
        src/entidades/estrelas/Estrelas.cpp
        src/entidades/estrelas/Estrelas.h
        src/entidades/colisao/Colisao.cpp
        src/entidades/colisao/Colisao.h
        src/jogo/Pontuacao.cpp
        src/jogo/Pontuacao.h
)

# Arquivos do ImGui
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

# Cria o executável
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCES})

# Inclui diretórios de headers
target_include_directories(${PROJECT_NAME} PRIVATE
        ${LIBRARY_DIR}/include
        ${LIBRARY_DIR}/include/glad
        ${LIBRARY_DIR}/include/GLFW
        ${LIBRARY_DIR}/include/glm
        ${LIBRARY_DIR}/include/irrKlang
        ${LIBRARY_DIR}/include/KHR
        ${LIBRARY_DIR}/include/stb
        ${SRC_DIR}
        ${IMGUI_DIR}
)

# Vincula bibliotecas
target_link_directories(${PROJECT_NAME} PRIVATE
        ${LIBRARY_DIR}/lib
)

target_link_libraries(${PROJECT_NAME}
        glfw3
        opengl32
        irrklang
)