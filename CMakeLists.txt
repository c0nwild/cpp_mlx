cmake_minimum_required(VERSION 3.26)

project(MLXCAM)
set(CMAKE_CXX_STANDARD 20)

add_executable(mlxcam)

target_sources(mlxcam
PUBLIC
    main.cpp 
    i2c_wrapper.cpp
    mlx90640.cpp
)
