cmake_minimum_required(VERSION 3.27)
project(trabalho_ed__ C)

set(CMAKE_C_STANDARD 99)

add_executable(trabalho_ed__ main.c
        alunos.c
        filme.c
        filme.h
        aluno.h
        top3.c)
