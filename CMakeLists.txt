# Versão mínima do CMake exigida para este projeto
cmake_minimum_required(VERSION 3.10)

# Nome do projeto e linguagem principal
project(Jacobi C)

# Garantindo que o CMake use as flags corretas
find_package(OpenMP REQUIRED)

# Definindo os arquivos fonte para cada versão
set(SEQUENTIAL_SOURCES
    src/jacobi_sequencial.c
    src/parser.c
)

set(PARALLEL_SOURCES
    src/jacobi_paralelo.c
    src/parser.c
)

# Criando os executáveis
add_executable(sequencial ${SEQUENTIAL_SOURCES})
add_executable(paralelo ${PARALLEL_SOURCES})

# Vinculando as bibliotecas e adicionando as flags corretas
target_link_libraries(paralelo PRIVATE OpenMP::OpenMP_C m)
target_link_libraries(sequencial PRIVATE m)

# Adicionando diretórios de cabeçalho
target_include_directories(paralelo PUBLIC include)
target_include_directories(sequencial PUBLIC include)

# Criando um alvo personalizado chamado "parallel" para executar o programa
add_custom_target(parallel
    COMMAND ./paralelo
    DEPENDS paralelo
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
    COMMENT "Executando programa paralelo"
)

# Adiciona um alvo personalizado chamado "sequential"
add_custom_target(sequential
    COMMAND sequencial
    DEPENDS sequencial
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
    COMMENT "Executando programa sequencial"
)
