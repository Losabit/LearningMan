cmake_minimum_required(VERSION 3.17)
project(MapCreator)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(MapCreator main.cpp GUI/Button.cpp GUI/Button.hpp GUI/Container.cpp GUI/Container.hpp lib/jsoncpp.cpp lib/json/json.h lib/json/json-forwards.h define.hpp utils/MapManager.cpp utils/MapManager.hpp utils/HitboxManager.cpp utils/HitboxManager.h utils/MapModel.cpp utils/MapModel.hpp)
target_link_libraries(MapCreator sfml-system sfml-window sfml-graphics -static)