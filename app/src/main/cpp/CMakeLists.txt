cmake_minimum_required(VERSION 3.22.1)

project("drawapp")

add_library(
        drawapp  # Tên lib: drawapp
        SHARED
        native-lib.cpp
        DrawingEngine.cpp)

find_library(
        log-lib
        log)

target_link_libraries(
        drawapp
        ${log-lib}
        android
        EGL
        GLESv2)