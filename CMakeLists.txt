cmake_minimum_required(VERSION 3.20.2)
project(LL_1_)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

include_directories(.)

add_executable(LL_1_
        Analyse.cpp
        Analyse.h
        First.cpp
        First.h
        Follow.cpp
        Follow.h
        Grammar.cpp
        Grammar.h
        main.cpp
        Table.cpp
        Table.h)
