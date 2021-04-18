cmake_minimum_required(VERSION 3.17)
project(LearningMan)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(LearningMan main.cpp)
target_link_libraries(LearningMan sfml-system sfml-window sfml-graphics -static)