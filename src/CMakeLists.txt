cmake_minimum_required(VERSION 3.5)

project(raycasting-project LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(raycasting-project Game.cpp)
target_link_libraries(raycasting-project PRIVATE sfml-graphics sfml-network sfml-audio)
target_compile_features(raycasting-project PRIVATE cxx_std_17)

install(TARGETS raycasting-project)