cmake_minimum_required(VERSION 2.6.0)
project(a2 C)
include_directories(include)

add_executable(q1
        q1.c
        common.h
        common.c
        list.h
        list.c
)

add_executable(q2
        q2.c
        common.h
        common.c
        list.h
        list.c
)