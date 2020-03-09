cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(a1 C)

include_directories(include)

add_executable(a1
    a1.c
    lib.c
    list.c
    lib.h
    list.h
)

