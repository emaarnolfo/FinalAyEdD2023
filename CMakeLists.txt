cmake_minimum_required(VERSION 3.24)
project(FinalAyEdD2023)

set(CMAKE_CXX_STANDARD 17)

add_executable(FinalAyEdD2023 main.cpp headers/Administrador.h headers/Arista.h headers/Router.h headers/Color.h sources/Administrador.cpp sources/Arista.cpp sources/Router.cpp)
