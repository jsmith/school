cmake_minimum_required(VERSION 2.6.0)
project(a2 C)
include_directories(include)

add_executable(q1
        q1.c
        list.c
        list.h
        common.h
        common.c
)

add_executable(q2
        q2.c
        list.c
        list.h
        cv.c
        cv.h
        common.h
        common.c
)