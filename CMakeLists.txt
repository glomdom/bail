cmake_minimum_required(VERSION 3.20)
project("bail")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "raylib static" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "raylib examples" FORCE)
add_subdirectory(vendor/raylib)

file(GLOB_RECURSE SOURCES src/*.cpp src/systems/*.cpp src/ecs/*.cpp)

add_executable(bail ${SOURCES})
target_link_libraries(bail PRIVATE raylib)
target_include_directories(bail PUBLIC src/)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/bin")
install(TARGETS bail
    RUNTIME DESTINATION .
)