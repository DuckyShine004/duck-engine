cmake_minimum_required(VERSION 3.10)
project(quaternion VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/fmt")
endif()

file(GLOB_RECURSE QUATERNION_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

find_package(PkgConfig REQUIRED)

find_package(fmt REQUIRED)
find_package(assimp REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(quaternion ${QUATERNION_SOURCES})

target_include_directories(quaternion
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(quaternion
    PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(quaternion
    PRIVATE
    fmt
    glfw
    assimp
)

target_link_libraries(quaternion
    PRIVATE
    fmt::fmt
)
