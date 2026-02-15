cmake_minimum_required(VERSION 3.22.1)

project("drawapp")

add_library(
        drawapp
        SHARED
        native-lib.cpp
        DrawingEngine.cpp)

find_library(log-lib log)

target_link_libraries(
        drawapp
        ${log-lib}
        android
        EGL
        GLESv2)

# THÊM DÒNG NÀY ĐỂ FIX CẢNH BÁO 16KB PAGE SIZE TRÊN ANDROID 15+
target_link_options(drawapp PRIVATE "-Wl,-z,max-page-size=16384")