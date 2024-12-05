cmake_minimum_required(VERSION 3.20)
project(projeto_asteroide)

set(CMAKE_CXX_STANDARD 17)

# Adicione todos os diretórios de includes
include_directories(
        ${PROJECT_SOURCE_DIR}/Library/include
        ${PROJECT_SOURCE_DIR}/Library/include/glad
        ${PROJECT_SOURCE_DIR}/Library/include/GLFW
        ${PROJECT_SOURCE_DIR}/Library/include/glm
        ${PROJECT_SOURCE_DIR}/Library/include/irrKlang
        ${PROJECT_SOURCE_DIR}/Library/include/KHR
        ${PROJECT_SOURCE_DIR}/Library/include/stb
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/Imgui
)

# Adicione todos os arquivos fonte
file(GLOB_RECURSE SOURCES
        "src/*.cpp"
        "src/*.h"
        "Imgui/*.cpp"
        "Imgui/*.h"
        "main.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES}
        shaders/Shader.cpp
        src/recursos/GerenciadorAsteroides.cpp
        src/recursos/GerenciadorAsteroides.h)

# Adicione as bibliotecas
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_SOURCE_DIR}/Library/lib/glfw3.lib
        ${PROJECT_SOURCE_DIR}/Library/lib/irrKlang.lib
        opengl32
        -lopengl32  # Biblioteca OpenGL
        -lm         # Biblioteca matemática
        -lkernel32
        -luser32
        -lgdi32
        -lwinspool
        -lshell32
        -lole32
        -loleaut32
        -luuid
        -lcomdlg32
        -ladvapi32
)

# Defina macros de compatibilidade
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)