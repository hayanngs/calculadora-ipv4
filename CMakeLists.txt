cmake_minimum_required(VERSION 3.24)
project(calculadora_ip)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculadora_ip main.cpp views.cpp views.h ip_com_classe.cpp ip_com_classe.h ip_sem_classe.cpp)
