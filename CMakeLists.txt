# Versão mínima do CMake exigida para este projeto
cmake_minimum_required(VERSION 3.10)

# Nome do projeto e linguagem principal
project(Jacobi C)

# Garantindo que o CMake use as flags corretas
find_package(OpenMP REQUIRED)

# Definindo o nome do executável
set(PARALELO_NOME paralelo)
set(SEQUENCIAL_NOME sequencial)

# Citando os arquivos fonte de forma organizada
set(SEQUENTIAL_SOURCES
  src/jacobi_sequencial.c
  )
  add_executable(sequencial ${SEQUENTIAL_SOURCES})

# Citando os arquivos fonte de forma organizada
set(PARALLEL_SOURCES
  src/jacobi_paralelo.c
)
add_executable(paralelo ${PARALLEL_SOURCES})

# Vinculando as bibliotecas e adicionando as flags corretas
target_link_libraries(paralelo PRIVATE OpenMP::OpenMP_C m)

# Criando um alvo personalizado chamado "parallel" para executar o programa
add_custom_target(parallel
  # Usamos um bloco 'if/else' explícito dentro do shell para maior clareza.
  COMMAND sh -c 'test -n "$$ARGS" && ./paralelo $$ARGS || ./paralelo 4 static 1'
  DEPENDS paralelo
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  VERBATIM
  COMMENT "Executando com: threads=$${NUM_THREADS}, schedule=$${SCHEDULE}, chunk=$${CHUNK_SIZE}"
)

# Adiciona um alvo personalizado chamado "sequential"
# Este alvo depende do executável Jacobi
# O comando a ser executado é simplesmente o nosso programa
add_custom_target(sequential
  COMMAND sequencial
  DEPENDS sequencial
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Informa o CMake para procurar por arquivos de cabeçalho .h
# no diretório 'include'
target_include_directories(paralelo PUBLIC include)
target_include_directories(sequencial PUBLIC include)
