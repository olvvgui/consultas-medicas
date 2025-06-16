cmake_minimum_required(VERSION 3.24)
project(consultas-medicas C)
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
set(CMAKE_C_STANDARD 99)

add_executable(consultas-medicas
        source/src/main.c
        source/src/funcs/agendar.c
        source/src/funcs/buscar.c
        source/src/funcs/cadastrar.c
        source/src/funcs/cancelar.c
        source/src/funcs/medOUdia.c
        source/src/funcs/reagendar.c
        source/lib/tools/consultas.c
        source/lib/tools/menu.c
        source/lib/tools/paciente.c
        source/lib/tools/utilitarios.c
)