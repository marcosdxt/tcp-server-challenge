# Define o mínimo necessário da versão do CMake
cmake_minimum_required(VERSION 3.10)

# Define o nome do projeto
project(qstServer)

# Adiciona o executável do servidor
add_executable(qstServer 
src/main.cpp
src/server/server.cpp
)

target_include_directories(
    qstServer PRIVATE src/server
)

# Especifica que o servidor precisa ser linkado com as bibliotecas de rede
target_link_libraries(qstServer PRIVATE -lpthread -lrt)

# Configuração para gerar os arquivos no diretório build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Opção de compilação para habilitar/desabilitar depuração (pode ser definida pelo usuário)
option(DEBUG "Enable debug build" OFF)
# Adiciona opções de compilação para depuração (incluindo informações de depuração) se DEBUG_BUILD estiver ativado
if(DEBUG)
    target_compile_options(qstServer PRIVATE -g)
    set_target_properties(qstServer PROPERTIES
        COMPILE_FLAGS "-O0"  # Desativa otimizações para melhorar a experiência de depuração
    )
    message(STATUS "Build with debug option")
endif()

add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Mensagem indicando o diretório de construção
message(STATUS "Binaries at build/ ${CMAKE_BINARY_DIR}")
