cmake_minimum_required(VERSION 3.21)
project(OWBalancer C)
#project(OWBalancer1 C)

set(CMAKE_C_STANDARD 99)

add_executable(OWBalancer main.c classes_header/player.h classes_header/role.h classes_header/balance.h classes/role.c classes/player.c classes/balance.c classes_header/const.h gameBalance.c gameBalance.h classes/array.c classes_header/array.h)
