cmake_minimum_required(VERSION 3.10)
project(quaternion VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE QUATERNION_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

find_package(PkgConfig REQUIRED)
find_package(fmt REQUIRED)
# find_package(OpenAL REQUIRED)
find_package(assimp REQUIRED)
find_package(glfw3 3.3 REQUIRED)

pkg_check_modules(OPENAL REQUIRED openal)
pkg_check_modules(SNDFILE REQUIRED sndfile)

add_executable(quaternion ${QUATERNION_SOURCES})

target_compile_definitions(quaternion PRIVATE GLFW_INCLUDE_NONE)

target_include_directories(quaternion PRIVATE
    ${OPENAL_INCLUDE_DIRS}
    ${SNDFILE_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

find_library(OPENAL_FRAMEWORK OpenAL)

target_link_libraries(quaternion PRIVATE
    glfw
    fmt::fmt
    assimp::assimp
    ${OPENAL_LDFLAGS}
    ${SNDFILE_LDFLAGS}
)
