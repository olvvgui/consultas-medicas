cmake_minimum_required(VERSION 3.24)
project(consultas-medicas C)

set(CMAKE_C_STANDARD 99)

add_executable(consultas-medicas
        source/consultas.c
        source/bibliotecas/funcoes.c
)