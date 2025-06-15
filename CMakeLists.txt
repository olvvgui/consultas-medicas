cmake_minimum_required(VERSION 3.24)
project(consultas-medicas C)
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
set(CMAKE_C_STANDARD 99)

add_executable(consultas-medicas
        source/consultas.c
        source/bibliotecas/funcoes.c
        source/bibliotecas/funcoes.h
)