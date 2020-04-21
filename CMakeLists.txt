cmake_minimum_required(VERSION 3.15)
project(OSMZ)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OSMZ
        gthr.c
        gthr.h
        gtswtch.S
        main.c
        Makefile)
