cmake_minimum_required(VERSION 3.20)
project(projeto_asteroide)

set(CMAKE_CXX_STANDARD 17)

# Adicionar flags específicas para MinGW
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Diretórios de include
include_directories(
        ${PROJECT_SOURCE_DIR}/Library/include
        ${PROJECT_SOURCE_DIR}/Library/include/glad
        ${PROJECT_SOURCE_DIR}/Library/include/GLFW
        ${PROJECT_SOURCE_DIR}/Library/include/glm
        ${PROJECT_SOURCE_DIR}/Library/include/KHR
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/Imgui
)

# Encontrar arquivos Imgui
file(GLOB IMGUI_SOURCES
        "${PROJECT_SOURCE_DIR}/Imgui/*.cpp"
)

# Copiar a pasta assets para o diretório de build
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Lista de fontes principal
set(SOURCES
        main.cpp
        glad.c
        src/menu/Menu.cpp
        src/menu/Menu.h
        src/jogo/GameManager.cpp
        src/jogo/GameManager.h
        src/recursos/TextureManager.cpp
        src/recursos/TextureManager.h
        src/entidades/nave/Ship.cpp
        src/entidades/nave/Ship.h
        src/entidades/asteroides/Asteroid.cpp
        src/entidades/asteroides/Asteroid.h
        src/entidades/Missil/Projectile.cpp
        src/entidades/Missil/Projectile.h
        src/entidades/colisao/CollisionManager.cpp
        src/entidades/colisao/CollisionManager.h
        src/entidades/estrelas/StarSystem.cpp
        src/entidades/estrelas/StarSystem.h
        shaders/Shader.cpp
        shaders/Shader.h
        src/recursos/stb_image.cpp
        src/recursos/stb_image.h
)

# Adicionar executável
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${IMGUI_SOURCES}
)

# Configuração das bibliotecas
if(WIN32)
    target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Library/lib)

    target_link_libraries(${PROJECT_NAME}
            ${PROJECT_SOURCE_DIR}/Library/lib/libglfw3.a
            opengl32
            gdi32
            user32
            kernel32
    )

    # Adicionar flags de link específicas
    set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "-static"
    )
endif()

# Definições de compatibilidade
add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
        -D_SCL_SECURE_NO_WARNINGS
)