cmake_minimum_required(VERSION 3.20)
project("bail")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "raylib static" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "raylib examples" FORCE)
add_subdirectory(vendor/raylib)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/JoltPhysics/Build)

file(GLOB_RECURSE SOURCES src/*.cpp src/systems/*.cpp src/ecs/*.cpp)

add_executable(bail ${SOURCES})
target_link_libraries(bail PRIVATE raylib fmt)
target_include_directories(bail PUBLIC src/)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist/bin")
install(TARGETS bail
    RUNTIME DESTINATION .
)
