cmake_minimum_required(VERSION 3.29)
project(yuyue_manage)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_STANDARD 20)

add_executable(yuyue_manage main.cpp
        identity.h
        student.h
        student.cpp
        teacher.h
        teacher.cpp
        manager.h
        manager.cpp
        globalFile.h
        computerRoom.h
        computerRoom.cpp
        orderFile.h
        orderFile.cpp)
