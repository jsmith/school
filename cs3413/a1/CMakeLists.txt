cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(a1 C)

include_directories(include)

add_executable(q1
        q1.c
        lib.c
        list.c
        lib.h
        list.h
        common.c
        common.h
)

add_executable(q2
        q2.c
        lib.c
        list.c
        lib.h
        list.h
        common.c
        common.h
)

add_executable(q3
        q3.c
        lib.c
        list.c
        lib.h
        list.h
        common.c
        common.h
)

add_executable(list.test
        list.c
        list.h
        list.test.c
)

add_executable(lib.test
        lib.c
        lib.h
        lib.test.c
)
